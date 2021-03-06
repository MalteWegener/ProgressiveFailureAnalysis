#include "stdafx.h"
#include "Solver.h"
#include <iostream>
#define PI2 pow(3.14156,2)
#define COEFF 4
#define BCKL 15000
#define FAILURE 30000 //Define what other groups couldnt

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
		
		if (!skbckl1) {
			if (!skbckl2) skbckl1 = (del * pnl->sk.mat.E / (1 - pow(pnl->sk.mat.v, 2)) >= skcr1);
			else skbckl1 = (del * pnl->sk.mat.E >= skcr1);
		}
		if (!skbckl2) skbckl2 = del * pnl->sk.mat.E / (1 - pow(pnl->sk.mat.v, 2))*pnl->sk.mat.v;
	}

	Result res = Result();

	res.del = del;
	res.skbckl1 = skbckl1;
	res.skbckl2 = skbckl2;
	res.strbckl = strbckl;
	return res;
}

Result Solverv2(Panel * pnl, double Force)
{
	std::cout << 0.9 * 2.1*pnl->sk.mat.E*pow(pnl->sk.t, 2) / pow(pnl->sk.length / pnl->rivets, 2) << std::endl;
	/**

	xDirection1
	->Direction2

	|L_____|L____|L_____|L
	*/

	std::vector<double> stressstr;
	stressstr.resize(pnl->stringers.size());
	double stressSkin1;
	double stressSkin2;
	double strain;

	std::vector<bool> strbckl;
	strbckl.resize(pnl->stringers.size(), false);
	bool skin1bckl = false;
	bool skin2bckl = false;

	//critical stress
	double skcr1 = 0.9 * 2.1*pnl->sk.mat.E*pow(pnl->sk.t, 2) / pow(pnl->sk.length / pnl->rivets, 2);/*4 * pow(PI, 2)*pnl->sk.I1 *pnl->sk.mat.E / pow(pnl->sk.length/(pnl->rivets-1), 2)/pnl->sk.A1;*/
	double skcr1b = 0.9 * 2.1*pnl->sk.mat.E*pow(pnl->sk.t, 2) / pow(pnl->sk.length / pnl->rivets, 2);/*4 * pow(PI, 2)*pnl->sk.I1 * pnl->sk.mat.E / (1 - pow(pnl->sk.mat.v, 2)) / pow(pnl->sk.length / (pnl->rivets - 1), 2) / pnl->sk.A1;*/
	double skcr2 = 1 * pow(PI, 2)*pnl->sk.I2*pnl->sk.mat.E / pow(0.4 / (pnl->stringers.size() - 1), 2)/pnl->sk.A2;
	//Deflection of the skin: if buckling in direction 2: sig /E*(1-v^2) else sig/E
	//Stress in direction 2 = sig1*v
	//Deflection of a stringer = sig/E
	// define stiffnes ass deflection per unit stress
	//average stiffnes is just an area weigthed average

	//run a solver as many times as we have components +2
	for (int i = 0; i < strbckl.size() + 3; i++)
	{
		double totstiff = 0;
		double totarea = 0;

		stressSkin1 = 0;
		stressSkin2 = 0;
		stressstr.resize(pnl->stringers.size(), 0);

		//do skin
		if (skin1bckl) totstiff = totstiff;
		else if (!skin2bckl)
		{
			totstiff += pnl->sk.mat.E / (1 - pow(pnl->sk.mat.v, 2));
			totarea += pnl->sk.A1;
		}
		else
		{
			totstiff += pnl->sk.mat.E;
			totarea += pnl->sk.A1;
		}

		//do strigners;
		for (int i = 0; i < strbckl.size(); i++)
		{
			if(!strbckl[i])
			{
				totstiff += pnl->stringers[i].mat.E;
				totarea += pnl->stringers[i].A;
			}
		}
		double avgstiff = totstiff / totarea;
		strain = Force / totarea / totstiff;

		//solve for the stress states

		if (!skin2bckl && !skin1bckl)
		{
			stressSkin1 = strain * pnl->sk.mat.E / (1 - pow(pnl->sk.mat.v, 2));
			stressSkin2 = pnl->sk.mat.v * stressSkin1;
		}
		else if(skin2bckl && !skin1bckl)
		{
			stressSkin1 = strain * pnl->sk.mat.E;
			stressSkin2 = skcr2;
		}
		else
		{
			stressSkin1 = 0;
			stressSkin2 = 0;
		}

		for (int i = 0; i < strbckl.size(); i++)
		{
			if (!strbckl[i])
			{
				stressstr[i] = strain * pnl->stringers[i].mat.E;
			}
		}

		// for that we calculate the critical stress and compare it to the actual stress because that nigger some retard
		double actcr1 = skin2bckl ? skcr1b : skcr1;
		if (!skin1bckl && (stressSkin1 >= actcr1)) skin1bckl = true;
		if (!skin2bckl && (stressSkin2 >= skcr2)) skin2bckl = true;

		//go through all stringers
		for (int i = 0; i < strbckl.size(); i++)
		{
			if (!strbckl[i] && (stressstr[i] >= COEFF * PI2*pnl->stringers[i].mat.E*pnl->stringers[i].I / pow(pnl->sk.length, 2) / pnl->stringers[i].A)) strbckl[i] = true;
		}

	}
	auto res = Result();
	res.del = strain*500;
	res.sigmask = stressSkin1;
	res.sigmastr = stressstr;
	res.skbckl1 = skin1bckl;
	res.skbckl2 = skin2bckl;
	res.strbckl = strbckl;
	return res;
}

Resultv2 Solverv3(Panel * pnl)
{
	//Some ugly temporary workaround
	double Area = 0;//pnl->sk.A1;
	for (int i = 0; i<pnl->stringers.size();i++)
	{
		Area += pnl->stringers[i].A;
	}

	double Q = 0; //#Thin walled assumption for the skin
	for (int i = 0; i<pnl->stringers.size(); i++)
	{
		Q += pnl->stringers[i].A*pnl->stringers[i].NA;
	}
	double NA = Q / Area;

	//Get like moment of Inertia for weird Euler Formula
	//Like srsly that fucking guy was a genius. Like did everything. Like jsut imagine him and Gauss
	//had a baby raised by Einstein and like Schrodinger. That boy would have discovered everything and
	//our study would be 70 times harder, Or our Robots overlords would have killed us
	double Iges = 0;// pnl->sk.I1 + pnl->sk.A1*pow(NA, 2);
	for (int i = 0; i<pnl->stringers.size(); i++)
	{
		Iges += pnl->stringers[i].A*pow(pnl->stringers[i].NA-NA,2)+pnl->stringers[i].I;
	}

	double Esum = 0;//pnl->sk.mat.E*pnl->sk.A1;
	for (int i = 0; i<pnl->stringers.size(); i++)
	{
		Esum += pnl->stringers[i].A*pnl->stringers[i].mat.E;
	}
	double Eav = Esum / Area;

	Resultv2 res = Resultv2();
	res.coulumn = pow(PI, 2) * 4 * Eav*Iges / pow(pnl->sk.length, 2);
	res.irbckl = 0.9 * 2.1*pnl->sk.mat.E*pow(pnl->sk.t, 2) / pow((pnl->sk.length - 0.06)/ (pnl->rivets-1), 2)*Area;
	res.lateral = Kc(pnl->sk.length / (pnl->sk.width / (pnl->stringers.size() - 1)))*pnl->sk.mat.E*pow(pnl->sk.t / (pnl->sk.width / (pnl->stringers.size() - 1)),2)*Area;
	
	//Lets do some quick maffs for mass
	res.mass = pnl->sk.A1*pnl->sk.mat.rho;
	for (int i = 0; i<pnl->stringers.size(); i++)
	{
		res.mass += pnl->stringers[i].A*pnl->stringers[i].mat.rho;
	}

	res.mass *= pnl->sk.length;

	//now for the fittness
	res.works = !(res.irbckl < 15000 | res.lateral < BCKL | res.coulumn < FAILURE);
	res.seed = {};
	res.seed.push_back(pnl->sk.t);
	for (int i = 0; i < pnl->stringers.size(); i++)
	{
		res.seed.push_back(pnl->stringers[i].x);
		res.seed.push_back(pnl->stringers[i].y);
		res.seed.push_back(pnl->stringers[i].t);
		res.seed.push_back(pnl->stringers[i].mat.rho);
	}

	return res;
}

double Kc(double nab)
{
	//Actually Copied from old code
	//Like no way i rewrite that even though the code ugly as hell
	//and inefficient. Has Like O(n^2) Complexity like wtf i can do better
	if (nab < 0.9) return 15;
	if (nab >= 5.4) return 3.6;

	std::vector<double> ab { 0.9, 1, 1.4, 2.1, 2.6, 3.4, 4, 5.4};
	std::vector<double> kc { 7, 6, 5, 4.2, 4, 3.8, 3.7, 3.6 };

	//first find the closest two values
	int indexsmalleras = ab.size() - 1;
	int indexbiggeras = 0;

	while (nab > ab[indexbiggeras]) indexbiggeras++;
	while (nab < ab[indexsmalleras]) indexsmalleras--;
	indexsmalleras++;
	indexbiggeras--;

	double slope = kc[indexsmalleras] - kc[indexbiggeras] / (ab[indexsmalleras] - ab[indexbiggeras]);
	double delta = nab - ab[indexbiggeras];
	return kc[indexbiggeras] + slope * delta;
}
