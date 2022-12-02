#ifndef FILE_READER
#define FILE_READER
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

vector<string> get_lines(string file){
    ifstream fin(file);
    string line;

    vector<string> file_content;
    while (getline(fin,line)){
        file_content.push_back(line);
    }

    return file_content;
}

#endif
