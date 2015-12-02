#include "parser.h"
using namespace std;

map<string, TableData*> table_map;

//
ParserResult Parser::Parse(string query) {
	ParserResult result;

	// read query into segments
	istringstream iss(query);
	string tmp;
	vector<string> s_list;
	int i = 0;
	while (iss >> tmp) {
		s_list.push_back(tmp);
		cout << i << " " << tmp << endl;
		i++;
	}

	// get query type
	string type = s_list[0];
	transform(type.begin(), type.end(), type.begin(), ::tolower); // lowercase
	result.query_type = type;
	
	if (type == "drop") {
		result.table_name = s_list[2];
	}
	else if (type == "create") {
		result.table_name = s_list[2];
	}
	else if (type == "insert") {
		result.table_name = s_list[2];
		
	}
	// 	case DROP: {
	// 		drop_table(s_list[1]);
	// 		break;
	// 	}
	// 	case INSERT: {
	// 		s_list[5].erase(s_list[5].end()-1);
	// 		s_list[7].erase(s_list[7].end()-1);
	// 		s_list[9].erase(s_list[9].end()-1);
	// 		s_list[11].erase(s_list[11].end()-1);
	// 		s_list[15].erase(s_list[15].end()-2, s_list[11].end());
	// 		s_list[15].erase(s_list[15].begin());

	// 		Polygon p;
	// 		p.push_back(Point(stod(s_list[4]), stod(s_list[5])));
	// 		p.push_back(Point(stod(s_list[6]), stod(s_list[7])));
	// 		p.push_back(Point(stod(s_list[8]), stod(s_list[9])));
	// 		p.push_back(Point(stod(s_list[10]), stod(s_list[11])));

	// 		insert_query(s_list[1], p, s_list[15]);
			
	// 		break;
	// 	}
	// 	case SELECT: {
			
	// 	}

	// 	case DELETE:
	// 		break;
			


		
	// }


	
	return result;











}

int main() {


	

    string table_name = "gis";
    TableData* tb_data;
    if (table_map.find() == table_map.end()){
        table_map[table_name] = new TableData(table_name);
    }
    tb_data = table_map[table_name];

    string attr_name = "blue";
    if (tb_data->string_map_.find(attr_name) == tb_data->string_map_.end()){
        tb_data->string_map_[attr_name] = (tb_data->string_counter_)++;
    }
    double attr_number = tb_data->string_map_[attr_name];


	Parser parser;

	parser.Parse("INSERT INTO gis1 VALUES (PolygonFromText('POLYGON(( 45800.8 12860.7, 45845.4 12860.7, 45845.4 12905.4, 45800.8 12860.7 ))'), 'red');");


	// parser("CREATE TABLE gis1 (g GEOMETRY NOT NULL, color VARCHAR(12), SPATIAL INDEX(g)) ENGINE=MyISAM;");

	// parser("CREATE TABLE gis (g GEOMETRY NOT NULL, color VARCHAR(12), SPATIAL INDEX(g)) ENGINE=MyISAM;\n");
	// parser("INSERT INTO gis VALUES\n(PolygonFromText('POLYGON(( 10 10, 20 10, 20 20, 10 20, 10 10 ))'), 'red')\n");

// 	parser("SELECT COUNT(*) FROM gis1 WHERE ST_CONTAINS(PolygonFromText('POLYGON((";
// 		for (int j = 0; j <= 3; j++) {
// 			fs1 << p[j].first << " " << p[j].second << ", ";
// 		}
// 		fs1 << p[0].first << " " << p[0].second << "))'), g) AND ";
// 		fs1 << "color='red';\n";
// }
}
