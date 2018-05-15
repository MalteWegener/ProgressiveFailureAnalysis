#include <vector>
#define PI 3.14159265359

class Material {
public:
	Material();
	Material(double nrho, double Emod, double poiss);
	double E;
	double rho;
	double v;
};

class Stringer {
public:
	Stringer();
	Stringer(double nx, double nt, Material nmat);
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
	Skin(double nt, Material nmat);
	Skin();
	~Skin();
	double width = 0.4;
	double length = 0.5;
	double t;
	Material mat;
	double I1;
	double I2;
	double A1;
	double A2;
};

class Panel {
public:
	Panel();
	~Panel();
	Skin sk;
	std::vector<Stringer> stringers;
	int rivets;
	/*bool skbckl1, skbckl2;
	bool irbckl;*/
	//std::vector<bool> stringerbckl;

	void RunProg();
};

struct Result {
public:
	std::vector<double> sigmastr;
	double sigmask;
	double del;
	std::vector<bool> strbckl;
	bool skbckl1;
	bool skbckl2;
};

struct Resultv2 {
public:
	double irbckl;
	double coulumn;
	double lateral;
	double mass;
	bool works;
	std::vector<double> seed;
};
