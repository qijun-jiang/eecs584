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
	// int n = 1000000;
	int n_insert = 200000;

	

	// fs << "(PolygonFromText('POLYGON((10 10, 20 10, 20 20, 10 20, 10 10))'))";
	// fs << ",\n";
	// fs << "(PolygonFromText('POLYGON((0 0, 30 0, 30 5, 0 5, 0 0))'))";
	// fs << ";";

	for (int k = 0; k < 5; k++) {
		string filename = "load" + to_string(k) + ".sql";
		ofstream fs(filename);
		// fs << "DROP TABLE gis;\n";
		// fs << "CREATE TABLE gis (g GEOMETRY NOT NULL, color VARCHAR(12), SPATIAL INDEX(g)) ENGINE=MyISAM;\n";
		fs << "INSERT INTO gis VALUES\n";
		for (int i = 0; i < n_insert; i++) {
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
			if (i != n_insert-1) {
				fs << ",\n";
			}
		}
		fs << ";";
		fs.close();
	}
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


	// select count(*) from gis where ST_CONTAINS(PolygonFromText('polygon((0 0, 100000 0, 100000 100000, 0 100000, 0 0))'), g);



	// Polygon a = randPolygon();
	// for (int i = 0; i < a.size(); i++) {
	// 	cout << a[i].first << endl;
	// 	cout << a[i].second << endl;
	// }
	return 0;
}