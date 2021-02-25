
#include "Utils.h"

vector<vector<double>> Utils::getGaussianFilter(int size) {
	const double sigma = (size - 1) / 6;
	vector<vector<double>> res;
	for (int i = 0; i < size; i++) {
		vector<double> temp;
		for (int j = 0; j < size; j++) {
			int x = i - size / 2;
			int y = j - size / 2;
			temp.push_back((1 / (2 * M_PI * sigma * sigma)) * exp(-(x * x + y * y) / (2 * sigma * sigma)));
		}
		res.push_back(temp);
	}
	return res;
}
