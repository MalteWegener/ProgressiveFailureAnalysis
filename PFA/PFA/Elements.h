class Material {
public:
	Material(double nrho, double Emod, double poiss);
	double E;
	double rho;
	double v;
};

class Stringer {
public:
	Stringer(double nx, double nt, double nE);
	~Stringer();
	double x;//length of a leg of the stringer
	double t;//Thickness of a stringer
	Material mat;
	double I;//Inertia around Neutral Axis
	double A;
	double NA; //Neutral Axis

private:
	double Inertia();
	double Area();
	double Neutral();
};

class Skin {
public:
	Skin(double nt, Material);
	~Skin();
	double width = 0.4;
	double length = 0.5;
	double t;
	Material mat;
	double I1;
	double I2;

private:
	void Inertia();
};

