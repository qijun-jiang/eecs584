#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <unordered_map>
#include "table_data.h"

using namespace std;

// typedef pair<double, double> Point;
// typedef vector<Point> Polygon;

struct ParserResult {
	string query_type;
	string table_name;
	Rect rect;
	char spatial_type;
	char cmp_op;
	double attr_value;

	ParserResult() {}
};

class Parser {

public:
	ParserResult Parse(string query);

};


#endif



