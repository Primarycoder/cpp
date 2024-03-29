//#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;
struct Interval {
	int start;
	int end;
	Interval(int start, int end) {
		this->start = start;
		this->end = end;
	}
};

bool compare(Interval inter1, Interval inter2) {
	return inter1.start < inter2.start;
}

void parseInputStr(string input, vector<Interval>& vec) {
	// replace '[' and ',' with blank, cause stringstream is
	// break by blank and stringstream format output to integer
	// will be 0 if the first char is not digit.
	for (auto& c : input) {
		if (c == '[' || c == ',') {
			c = ' ';
		}
	}
	string left, right;
	int start, end;
	stringstream ss(input);
	while (!ss.eof()) {
		ss >> left;
		ss >> right;
		if (left.compare("") == 0 || right.compare("") == 0) {
			break;
		}
		stringstream(left) >> start;
		stringstream(right) >> end;
		vec.push_back(Interval(start, end));
	}
}

vector<Interval> result;

void mergeInterval(vector<Interval>& vec) {
	if (vec.empty()) {
		return;
	}

	sort(vec.begin(), vec.end(), compare)
	Interval inter = vec.at(0);
	result.push_back(inter);
	for (auto i = vec.begin() + 1; i != vec.end(); i++) {
		// in case of intervals can be merged e.g. [2, 5] [4, 6] => [2, 6]
		if (inter.end + 1 >= i->start) {
			result.back().end = (inter.end < i->end) ? i->end : inter.end;
		} else {
			inter = *i;
			result.push_back(inter);
		}
	}
}

void fullInterval() {
	if (result.size() <= 1) {
		cout << "[]" << endl;
		return;
	}
	for (auto i = result.begin(); i + 1 != result.end(); i++) {
		cout << "[" << i->end + 1 << "," << (i + 1)->start - 1 << "] ";
	}
	cout << endl;
}


/**
 * Input a string contains multi intervals, output intervals make intervals one whole interval.
 * e.g. [1,4] [2,5] [8,9] => [6,7]
 *      [-2,3] [1,4] [8,9] => [5,7]
 *      [8,9] [2,3] [1,4] [6,9] => [5,5]
 *      [1,4] [12,14] [2,5] [8,9] => [6,7] [10,11]
 *      [1,4] [2,5] => []
 **/
int main()
{
	string input;
	vector<Interval> vec;

	while (getline(cin, input)) {
		vec.clear();
		result.clear();
		parseInputStr(input, vec);
		mergeInterval(vec);
		fullInterval();
	}
	
    return 0;
}

