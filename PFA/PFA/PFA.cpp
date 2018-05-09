// PFA.cpp: Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "Solver.h"
#include <iostream>

int main()
{
	std::vector<Stringer> PresetStrigners;



	Panel pnl = Panel();
	pnl.sk = Skin(0.001, Material(1, 72400000000, 0.34));
	Material Al = Material(1, 72400000000, 0.34);
	for (int i = 0; i < 4; i++)
	{
		pnl.stringers.push_back(Stringer(0.02, 0.001, Al));
	}

	auto res = Solver(&pnl, 20000);
	std::cout << res.skbckl2 << std::endl;
}

