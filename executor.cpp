#include <iostream>
#include "executor.h"
using namespace std;

bool MySearchCallback(ValueType id, void* arg)
{
    std::string *table_name = static_cast<std::string*>(arg);
    cout << "Hit data rect [" << id << "] in" << *table_name << ":";
    TableData& tb_data = *(table_map[table_name]);
    cout<< " " << tb_data.rect_in_row_[id].min[0] << " " << tb_data.rect_in_row_[id].min[1] << " "
        << tb_data.rect_in_row_[id].max[0] << " "<< tb_data.rect_in_row_[id].min[1] <<endl;
  return true; // keep going
}


int Executor::execute(string query_string){
// create table
// insert
// query
// drop table
    ParserResult parsed_query = query_parser_.Parse(query_string);
    string table_name = parsed_query.table_name;
    if (table_map.find(table_name) == table_map.end()){
        table_map[table_name] = new TableData(table_name);
    }
    TableData& tb_data = *(table_map[table_name]);
    MyTree& rtree = tb_data.rtree_;

    cout<< "[exe log:] query_type:" << parsed_query.query_type <<endl;

    if (parsed_query.query_type == "insert"){
        int row_id = tb_data.row_id_++;
        tb_data.rect_in_row_.push_back(parsed_query.rect);
        tb_data.attribute_in_row_.push_back(parsed_query.attr_value);
        cout<<"[exe log:] tb-name:" << table_name;
        cout<< parsed_query.rect.min[0] << " " << parsed_query.rect.min[1] << " "
            << parsed_query.rect.max[0] << " "<< parsed_query.rect.min[1] <<endl;
        rtree.Insert(parsed_query.rect.min, parsed_query.rect.max, row_id);
    }

    if (parsed_query.query_type == "query"){
        void *void_table_name = static_cast<void*>(&table_name);
        int nhits = rtree.Search(parsed_query.rect.min, parsed_query.rect.min, MySearchCallback, void_table_name);
        cout << "Search resulted in " << nhits << " hits\n";
        return nhits;
    }

    if (parsed_query.query_type == "drop table"){
        
    }


    return 0;
}