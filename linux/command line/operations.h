#ifndef _OPERATIONS_H_
#define _OPERATIONS_H_

// Main operations are written here.
// Copy, Delete, Search e.t.c
#include <string.h>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#define MAX_SIZE 2000

using namespace std;

struct args
{
    bool keep_file = false, overwrite = true, prompt_overwrite = true;
    bool move_into = false;
    std::string source = "Hello", destination = "";
};

bool is_directory(string name);

bool copyFile(args *p_ar);

pair<string, string> split(string str);

bool copyEntity(args *p_ar);

#endif