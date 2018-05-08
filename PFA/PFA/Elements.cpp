#include "stdafx.h"
#include "Elements.h"
#include <math.h>

Stringer::Stringer(double nx, double nt, double nE)
{
	x = nx;
	t = nt;
	E = nE;

	A = Area();
	NA = Neutral();
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

Skin::Skin(double nt)
{
}

Material::Material(double nrho, double Emod, double poiss)
{
	rho = nrho;
	E = Emod;
	v = poiss;
}
