#pragma once
#include <vector>

class Cauchy
{
public:
	std::vector<std::vector<double>> data;
	double getData(int row, int col);
};