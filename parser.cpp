#include "parser.h"
using namespace std;

map<string, TableData*> table_map;


double get_double(string table_name, string attr_name) {
    stringstream ss;
    ss << attr_name;
    double value;
    if (ss >> value) {
        return value;
    }
    else {
        TableData* tb_data;
        if (table_map.find(table_name) == table_map.end()) {
            table_map[table_name] = new TableData(table_name);
        }
        tb_data = table_map[table_name];

        if (tb_data->string_map_.find(attr_name) == tb_data->string_map_.end()){
            tb_data->string_map_[attr_name] = (tb_data->string_counter_)++;
        }
        return tb_data->string_map_[attr_name];
    }
}

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
        // cout << i << " " << tmp << endl;
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
        s_list[6].erase(s_list[6].end()-1);
        s_list[10].erase(s_list[10].end()-1);
        result.rect = Rect(stod(s_list[5]), stod(s_list[6]), stod(s_list[9]), stod(s_list[10]));

        // attribute value
        s_list[16].erase(s_list[16].end()-3, s_list[16].end());
        s_list[16].erase(s_list[16].begin());
        result.attr_value = get_double(result.table_name, s_list[16]);
    }
    else if (type == "select") {
        result.table_name = s_list[3];
        if (s_list[5] == "ST_CONTAINS") {
            result.spatial_type = 'C';
        }
        else if (s_list[5] == "ST_INTERSECTS") {
            result.spatial_type = 'I';
        }
        s_list[8].erase(s_list[8].end()-1);
        s_list[12].erase(s_list[12].end()-1);
        result.rect = Rect(stod(s_list[7]), stod(s_list[8]), stod(s_list[11]), stod(s_list[12]));
        result.cmp_op = s_list[21][0];

        // attribute value
        s_list[22].erase(s_list[22].end()-2, s_list[22].end());
        s_list[22].erase(s_list[22].begin());
        result.attr_value = get_double(result.table_name, s_list[22]);
    }
    return result;
}

int main() {
    Parser parser;
    parser.Parse("SELECT COUNT(*) FROM gis1 WHERE ST_CONTAINS (PolygonFromText('POLYGON(( 24585.6 8324.77, 34585.6 8324.77, 34585.6 18324.8, 24585.6 18324.8, 24585.6 8324.77 ))'), g) AND color = 'red';");
    parser.Parse("INSERT INTO gis1 VALUES (PolygonFromText('POLYGON(( 89031.9 55459.7, 89147.3 55459.7, 89147.3 55575.1, 89031.9 55575.1, 89031.9 55459.7 ))'), 'blue');");

    // for (auto it = table_map["gis1"]->string_map_.begin(); it != table_map["gis1"]->string_map_.end(); it++) {
    //  cout << it->first << " " << it->second << endl;
    // }
}








