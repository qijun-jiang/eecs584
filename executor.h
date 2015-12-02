#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <parser.h>

using namespace std;


class Executor{
    Parser query_parser_;
  public:
    /* 
    return -1 for error,
            0 for success,
            other value for select result;
    */
    int execute(string query_string);

};

#endif