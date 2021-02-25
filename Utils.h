#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <vector>

#define M_PI	3.1415926535F

using namespace std;

class Utils {
	vector<vector<double>> getGaussianFilter(int size);
};

#endif