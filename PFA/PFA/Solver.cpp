#include "stdafx.h"
#include "Solver.h"

Result Solver(Panel * pnl, double Force)
{
	//critical Forces
	double skcr1 = 4 * pow(PI, 2)*pnl->sk.I1 *pnl->sk.mat.E/ pow(pnl->sk.length, 2)*pnl->sk.A1;
	double skcr2 = 4 * pow(PI, 2)*pnl->sk.I2*pnl->sk.mat.E / pow(0.4 / (pnl->stringers.size() - 1), 2)*pnl->sk.A1;
	std::vector<double> strcr;
	strcr.resize(pnl->stringers.size());
	for (unsigned int i = 0; i < strcr.size(); i++)
	{
		strcr[i] = 4 * pow(PI, 2)*pnl->stringers[i].I*pnl->stringers[i].mat.E / pow(pnl->sk.length, 2)*pnl->stringers[i].A;
	}

	//first assume nothing buckles

	std::vector<bool> strbckl;
	std::vector<double> strsig;
	strsig.resize(pnl->stringers.size(), 0);
	strbckl.resize(pnl->stringers.size(), false);
	bool skbckl1 = false;
	bool skbckl2 = false;
	double sksig1 = 0;
	double sksig2 = 0;
	double del = 0;

	//run a solver 10 times
	for (int i = 0; i < 1; i++)
	{
		double totstiff = 0;
		double totarea = 0;
		if (!skbckl1)
		{
			totstiff += !skbckl2 ? pnl->sk.A1*pnl->sk.mat.E / (1 - pow(pnl->sk.mat.v, 2)) : pnl->sk.A1*pnl->sk.mat.E;
			totarea += pnl->sk.A2;
		}

		for (int i = 0; i < pnl->stringers.size(); i++)
		{
			if (!strbckl[i])
			{
				totstiff += pnl->stringers[i].mat.E *pnl->stringers[i].A;
				totarea += pnl->stringers[i].A;
			}
		}
		double avgstiffness = totstiff / totarea;

		del = Force / avgstiffness;
		for (int i = 0; i < pnl->stringers.size(); i++)
		{
			if (!strbckl[i]) strbckl[i] = (del*pnl->stringers[i].mat.E >= strcr[i]);
		}
		
		if (!skbckl1) skbckl1 = (!skbckl2 ? del * pnl->sk.mat.E / (1 - pow(pnl->sk.mat.v, 2)) : del * pnl->sk.mat.E >= skcr1);
		if (!skbckl2) skbckl2 = (!skbckl2 ? del * pnl->sk.mat.E / (1 - pow(pnl->sk.mat.v, 2))*pnl->sk.mat.v : del * pnl->sk.mat.E*pnl->sk.mat.v >= skcr2);
	}

	Result res = Result();

	res.del = del;
	res.skbckl1 = skbckl1;
	res.skbckl2 = skbckl2;
	res.strbckl = strbckl;
	return res;
}
