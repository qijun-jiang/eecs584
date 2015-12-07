#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>

using namespace std;

typedef pair<double, double> Point;
typedef vector<Point> Polygon;

int n_rect = 100;
double area_side = 100000.0;
double rec_side_mean = 30.0;
double rec_side_sigma = 5.0;
unsigned seed = chrono::system_clock::now().time_since_epoch().count();
default_random_engine gen(seed);
uniform_real_distribution<double> unif_size(0.0, area_side);
normal_distribution<double> norm_side(rec_side_mean, rec_side_sigma);
uniform_real_distribution<double> unif_0_100(0.0, 100.0);

Polygon randPolygon() {
	Polygon p;
	double x = unif_size(gen);
	double y = unif_size(gen);
	double side_x = norm_side(gen);
	double side_y = norm_side(gen);
	p.push_back(Point(x-side_x/2, y-side_y/2));
	p.push_back(Point(x+side_x/2, y-side_y/2));
	p.push_back(Point(x+side_x/2, y+side_y/2));
	p.push_back(Point(x-side_x/2, y+side_y/2));
	return p;
}

int main(int argc, char** argv) {
	string filename = "sql/load_N10M.sql";
	ofstream fs(filename);
	fs << "DROP TABLE gis;\n";
	fs << "CREATE TABLE gis (g GEOMETRY NOT NULL, val DOUBLE, SPATIAL INDEX(g)) ENGINE=MyISAM;\n";

	for (int i = 0; i < n_rect; i++) {
		fs << "INSERT INTO gis VALUES ";
		Polygon p = randPolygon();
		fs << "(PolygonFromText('POLYGON(( ";
		for (int j = 0; j < 4; j++) {
			fs << p[j].first << " " << p[j].second << ", ";
		}
		fs << p[0].first << " " << p[0].second << " ))'), ";
		
		fs << "'" << unif_0_100(gen) << "');\n";
	}
	fs.close();

	return 0;
}
