#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

typedef pair<double, double> Point;
typedef vector<Point> Polygon;

double area_side = 100000.0;
unsigned seed = chrono::system_clock::now().time_since_epoch().count();
default_random_engine gen(seed);
uniform_real_distribution<double> unif_size(0.0, area_side);

Polygon randSearchBox(double p) {
	Polygon poly;
	double l = sqrt(p/100.0) * area_side;
	double x = unif_size(gen);
	double y = unif_size(gen);
	poly.push_back(Point(x-l/2, y-l/2));
	poly.push_back(Point(x+l/2, y-l/2));
	poly.push_back(Point(x+l/2, y+l/2));
	poly.push_back(Point(x-l/2, y+l/2));
	return poly;
}

int main(int argc, char** argv) {
	int n_search = stoi(argv[1]);
	double p = stod(argv[2]);
	double s = stod(argv[3]);
	stringstream str;
	string file_qs;
	str << "_p" << fixed << setprecision(1) << p << "_s" << s << ".sql";
	string filename = "sql/search_N10M_Q" + to_string(n_search) + file_qs;
	ofstream fs(filename);
	for (int i = 0; i < n_search; i++) {
		Polygon poly = randSearchBox(p);
		fs << "SELECT COUNT(*) FROM gis WHERE ST_CONTAINS (";
		fs << "PolygonFromText('POLYGON(( ";
		for (int j = 0; j < 4; j++) {
			fs << poly[j].first << " " << poly[j].second << ", ";
		}
		fs << poly[0].first << " " << poly[0].second << " ))'), g) AND ";
		fs << "val < '" << s << "';";
		if (i != n_search-1) fs << "\n";
	}
	return 0;
}
