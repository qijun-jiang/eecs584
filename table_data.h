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