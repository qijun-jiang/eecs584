#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>

using namespace std;

unsigned seed = chrono::system_clock::now().time_since_epoch().count();
default_random_engine gen(seed);
uniform_real_distribution<double> unif_size(0.0, 100000.0);
uniform_real_distribution<double> unif_side(0.0, 100.0);
uniform_real_distribution<double> unif_0_1(0.0, 1.0);

typedef pair<double, double> Point;
typedef vector<Point> Polygon;

Polygon randPolygon() {
	Polygon p;
	double x = unif_size(gen);
	double y = unif_size(gen);
	double side = unif_side(gen);
	p.push_back(Point(x-side, y-side));
	p.push_back(Point(x+side, y-side));
	p.push_back(Point(x+side, y+side));
	p.push_back(Point(x-side, y+side));
	return p;
}

Polygon randSearchBox(double side) {
	Polygon p;
	double x = unif_size(gen);
	double y = unif_size(gen);
	p.push_back(Point(x-side/20, y-side/20));
	p.push_back(Point(x+side/20, y-side/20));
	p.push_back(Point(x+side/20, y+side/20));
	p.push_back(Point(x-side/20, y+side/20));
	return p;
}


int main(int argc, char** argv) {
	
	vector<Polygon> poly_list;
	int n_insert = 10000000;
	int n_step = 200000;
	int num_query = n_insert / n_step;

	string filename = "load.sql";
	ofstream fs(filename);
	fs << "DROP TABLE gis;\n";
	fs << "CREATE TABLE gis (g GEOMETRY NOT NULL, color VARCHAR(12) ) ENGINE=MyISAM;\n";

	for (int k = 0; k < num_query; k++) {
		fs << "INSERT INTO gis VALUES\n";
		for (int i = 0; i < n_step; i++) {
			Polygon p = randPolygon();
			fs << "(PolygonFromText('POLYGON((";
			for (int j = 0; j < 3; j++) {
				fs << p[j].first << " " << p[j].second << ", ";
			}
			fs << p[0].first << " " << p[0].second << "))'),";
			
			if (unif_0_1(gen) > 0.5) {
				fs << "'red')";
			}
			else {
				fs << "'blue')";
			}
			if (i != n_step-1) {
				fs << ",\n";
			}
		}
		fs << ";\n";
	}
	fs.close();

	int n_search = 100;
	ofstream fs1("search.sql");
	for (int i = 0; i < n_search; i++) {
		Polygon p = randSearchBox(100000.0);
		fs1 << "SELECT COUNT(*) FROM gis WHERE ST_CONTAINS(";
		fs1 << "PolygonFromText('POLYGON((";
		for (int j = 0; j < 3; j++) {
			fs1 << p[j].first << " " << p[j].second << ", ";
		}
		fs1 << p[0].first << " " << p[0].second << "))'), g) AND ";
		fs1 << "color='red';\n";
	}

	return 0;
}