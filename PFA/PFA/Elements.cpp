#include "stdafx.h"
#include "Elements.h"
#include <math.h>
#include <iostream>

Stringer::Stringer()
{
}

Stringer::Stringer(double nx, double nt, Material nmat)
{
	x = nx;
	t = nt;
	mat = nmat;

	A = Area();
	NA = Neutral();
	I = Inertia();
}

Stringer::~Stringer()
{
}

double Stringer::Inertia()
{
	return 1/12*(x*t*(x*x+t*t)-t*t*t*t)+pow(x/2-NA,2)*x*t+pow(NA-t/2,2)*x*t-pow(NA-t/2,2)*t*t;
}

double Stringer::Area()
{
	return 2 * x*t - t * t;
}

double Stringer::Neutral()
{
	return 0.5*(x*t*(x+t)-pow(t,3))/A;
}

Skin::Skin(double nt, Material nmat)
{
	t = nt;
	mat = nmat;

	A1 = width * t;
	A2 = length * t;
	I1 = pow(t, 3) / 12 * width;
	I2 = pow(t, 3) / 12 * length;
}

Skin::Skin()
{
}

Skin::~Skin()
{
}

Material::Material()
{
}

Material::Material(double nrho, double Emod, double poiss)
{
	rho = nrho;
	E = Emod;
	v = poiss;
}

Panel::Panel()
{
}

Panel::~Panel()
{
}

void Panel::RunProg()
{
}

/*void Panel::solveState(double Force)
{
	double remForce = Force;

	for (int i = 0; i < stringerbckl.size(); i++)
	{
		if (stringerbckl[i])
		{
			remForce -= 4 * pow(PI, 2)*stringers[i].mat.E*stringers[i].I / pow(0.5, 2);
		}
	}

	if (skbckl)
	{
		remForce -= 4 * pow(PI, 2)*sk.mat.E*sk.I2 / pow(0.4 / (stringers.size() - 1), 2) / sk.A2 / sk.mat.v*sk.A1;
	}

	double remarea = 0;
	if (!skbckl) remarea += sk.A1;

	for (int i = 0; i < stringerbckl.size(); i++)
	{
		if (!stringerbckl[i])
		{
			remarea += stringers[i].A;
		}
	}
	double avgstress = remForce / remarea;

	double totstiff = 0;
	if (skbckl) totstiff += sk.mat.E;
	else totstiff += sk.mat.E / (1 - pow(sk.mat.v, 2));
	totstiff *= sk.A1;


	for (int i = 0; i < stringers.size(); i++)
	{
		if (!stringerbckl[i]) totstiff += stringers[i].mat.E * stringers[i].A;
	}

	totstiff /= remarea;

	double del = avgstress / totstiff;

	double sigmask;
	if (skbckl) sigmask = del * sk.mat.E;
	else sigmask = del * sk.mat.E / (1 - pow(sk.mat.v, 2));

	if (sigmask*sk.A2 > 4 * pow(PI, 2)*sk.mat.E*sk.A2 / (pow(0.4 / (stringers.size() - 1), 2)))
	{
		skbckl = true;
	}
}*/

