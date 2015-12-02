#include <iostream>
#include "executor.h"
using namespace std;

struct CompareInfo{
    CompareInfo(string table_name_, double attr_value_){
        table_name = table_name_;
        attr_value = attr_value_;
    }
    string table_name;
    double attr_value;
};

bool NoCompareCallback(ValueType id, void* arg)
{
    CompareInfo* compare_info = (struct CompareInfo *)arg;
    cout << "Hit data rect [" << id << "] in" << compare_info->table_name << ":";
    TableData& tb_data = *(table_map[compare_info->table_name]);
    cout<< " " << tb_data.rect_in_row_[id].min[0] << " " << tb_data.rect_in_row_[id].min[1] << " "
        << tb_data.rect_in_row_[id].max[0] << " "<< tb_data.rect_in_row_[id].max[1] <<endl;
    return true; // keep going
}

bool GreaterCallback(ValueType id, void* arg)
{
    CompareInfo* compare_info = (struct CompareInfo *)arg;
    cout << "Hit data rect [" << id << "] in" << compare_info->table_name << ":";
    TableData& tb_data = *(table_map[compare_info->table_name]);
    cout<< " " << tb_data.rect_in_row_[id].min[0] << " " << tb_data.rect_in_row_[id].min[1] << " "
        << tb_data.rect_in_row_[id].max[0] << " "<< tb_data.rect_in_row_[id].max[1] <<endl;

    // Check greater than
    if (compare_info->attr_value > tb_data.attribute_in_row_[id]) {
        return true;
    } else {
        return false;
    }
}

bool LessCallback(ValueType id, void* arg)
{
    CompareInfo* compare_info = (struct CompareInfo *)arg;
    cout << "Hit data rect [" << id << "] in" << compare_info->table_name << ":";
    TableData& tb_data = *(table_map[compare_info->table_name]);
    cout<< " " << tb_data.rect_in_row_[id].min[0] << " " << tb_data.rect_in_row_[id].min[1] << " "
        << tb_data.rect_in_row_[id].max[0] << " "<< tb_data.rect_in_row_[id].max[1] <<endl;

    // Check less than
    if (compare_info->attr_value < tb_data.attribute_in_row_[id]) {
        return true;
    } else {
        return false;
    }
}

bool EqualCallback(ValueType id, void* arg)
{
    CompareInfo* compare_info = (struct CompareInfo *)arg;
    cout << "Hit data rect [" << id << "] in" << compare_info->table_name << ":";
    TableData& tb_data = *(table_map[compare_info->table_name]);
    cout<< " " << tb_data.rect_in_row_[id].min[0] << " " << tb_data.rect_in_row_[id].min[1] << " "
        << tb_data.rect_in_row_[id].max[0] << " "<< tb_data.rect_in_row_[id].max[1] <<endl;

    // Check equal
    if (compare_info->attr_value == tb_data.attribute_in_row_[id]) {
        return true;
    } else {
        return false;
    }
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
        rtree.Insert(parsed_query.rect.min, parsed_query.rect.max, row_id);
    }

    if (parsed_query.query_type == "select"){
        CompareInfo compare_info(table_name, parsed_query.attr_value);
        void *vp = static_cast<void*>(&compare_info);
        int nhits;
        if (parsed_query->cmp_op == '?'){
            nhits = rtree.Search(parsed_query.rect.min, parsed_query.rect.max, NoCompareCallback, vp);
        }
        if (parsed_query->cmp_op == '='){
            nhits = rtree.Search(parsed_query.rect.min, parsed_query.rect.max, EqualCallback, vp);
        }
        if (parsed_query->cmp_op == '>'){
            nhits = rtree.Search(parsed_query.rect.min, parsed_query.rect.max, GreaterCallback, vp);
        }
        if (parsed_query->cmp_op == '<'){
            nhits = rtree.Search(parsed_query.rect.min, parsed_query.rect.max, LessCallback, vp);
        }
        cout << "Search resulted in " << nhits << " hits\n";
        return nhits;
    }

    if (parsed_query.query_type == "drop table"){
        
    }


    return 0;
}