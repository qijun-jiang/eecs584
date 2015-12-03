#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>

using namespace std;

unsigned seed = chrono::system_clock::now().time_since_epoch().count();
default_random_engine gen(seed);
uniform_real_distribution<double> unif_size(0.0, 100000.0);
uniform_real_distribution<double> unif_side(3.0, 100.0);
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
	

	string filename = "sql/load.sql";
	ofstream fs(filename);
	fs << "DROP TABLE gis1;\n";
	fs << "CREATE TABLE gis1 (g GEOMETRY NOT NULL, color VARCHAR(12), SPATIAL INDEX(g)) ENGINE=MyISAM;\n";

	for (int i = 0; i < n_insert; i++) {
		fs << "INSERT INTO gis1 VALUES ";
		Polygon p = randPolygon();
		fs << "(PolygonFromText('POLYGON(( ";
		for (int j = 0; j < 4; j++) {
			fs << p[j].first << " " << p[j].second << ", ";
		}
		fs << p[0].first << " " << p[0].second << " ))'), ";
		
		if (unif_0_1(gen) > 0.5) {
			fs << "'red')";
		}
		else {
			fs << "'blue')";
		}
		fs << ";\n";
	}
	fs.close();

	int n_search = 100;
	ofstream fs1("sql/search.sql");
	for (int i = 0; i < n_search; i++) {
		Polygon p = randSearchBox(100000.0);
		fs1 << "SELECT COUNT(*) FROM gis1 WHERE ST_CONTAINS (";
		fs1 << "PolygonFromText('POLYGON(( ";
		for (int j = 0; j < 4; j++) {
			fs1 << p[j].first << " " << p[j].second << ", ";
		}
		fs1 << p[0].first << " " << p[0].second << " ))'), g) AND ";
		fs1 << "color = 'red';";
		if (i != n_search-1) fs1 << "\n";
	}

	return 0;
}
