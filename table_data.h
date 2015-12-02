#ifndef TABLE_DATA_H
#define TABLE_DATA_H

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include "RTree.h"

typedef int ValueType;
typedef RTree<ValueType, double, 2, double> MyTree;

struct Rect {
    double min[2];
    double max[2];

    Rect() {}

    Rect(double a_minX, double a_minY, double a_maxX, double a_maxY) {
        min[0] = a_minX;
        min[1] = a_minY;
        max[0] = a_maxX;
        max[1] = a_maxY;
    }  
};

/*
    row contains(rectangle and attribute)
    row_id counter
    rtree index
    string map maps string to double( string counter)

example usage:

    extern map<string, TableData*> table_map;

    string table_name;
    TableData* tb_data;
    if (table_map.find() == table_map.end()){
        table_map[table_name] = new TableData(table_name);
    }
    tb_data = table_map[table_name];

    string attr_name;
    if (tb_data->string_map_.find(attr_name) == tb_data->string_map_.end()){
        tb_data->string_map_[attr_name] = (tb_data->string_counter_)++;
    }
    double attr_number = tb_data->string_map_[attr_name];

*/

class TableData{
    TableData(string input_table_name_){
        table_name_ = input_table_name_;
        row_id_ = 0;
        string_counter_ = 0;
    }

  public:
    string table_name_;
    vector<Rect> rect_in_row_;
    vector<double> attribute_in_row_;
    int row_id_;
    MyTree rtree_;
    int string_counter_;
    map <string, int> string_map_;
};

#endif