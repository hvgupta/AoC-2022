#ifndef FILE_READER
#define FILE_READER
#include <iostream>
#include <vector>
#include <fstream>

std::vector<std::string> get_lines(std::string file){
    std::ifstream fin(file);
    std::string line;

    std::vector<std::string> file_content;
    while (getline(fin,line)){
        file_content.push_back(line);
    }

    return file_content;
}

#endif
