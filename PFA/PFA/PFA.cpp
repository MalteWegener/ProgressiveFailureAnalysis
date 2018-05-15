// PFA.cpp: Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "Solver.h"
#include <iostream>
#include <fstream>

int main()
{
	std::vector<Stringer> PresetStrigners;
	std::vector<Skin> PresetSkins;

	Material Al = Material(2.78, 72400000000, 0.33);
	Material St = Material(7.8, 210000000000, 0.3);

	//Ugly Hardcoding
	PresetStrigners.push_back(Stringer(0.02, 0.0015, Al));
	PresetStrigners.push_back(Stringer(0.02, 0.002, Al));
	PresetStrigners.push_back(Stringer(0.015, 0.001, Al));
	PresetStrigners.push_back(Stringer(0.015, 0.0015, Al));
	PresetStrigners.push_back(Stringer(0.015, 0.0015, St));
	PresetStrigners.push_back(Stringer(0.015, 0.002, St));

	//More of that
	PresetSkins.push_back(Skin(0.0008, Al));
	PresetSkins.push_back(Skin(0.001, Al));
	PresetSkins.push_back(Skin(0.0012, Al));



	auto pnl = Panel();
	pnl.rivets = 10;
	pnl.sk = PresetSkins[0];
	for (int i = 0; i < 2; i++) pnl.stringers.push_back(PresetStrigners[0]);
	std::vector<double> Dels;
	for (int i = 0; i < 30000; i+=10) Dels.push_back(Solverv2(&pnl, (double)i).skbckl2);
	

	std::ofstream myfile;
	myfile.open("Results.csv");

	for (int i = 0; i < Dels.size(); i++) myfile << Dels[i] << std::endl;
	myfile.close();
}

