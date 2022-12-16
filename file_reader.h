#ifndef FILE_READER
#define FILE_READER
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>


std::vector<std::string> get_lines(std::string file){
    std::ifstream fin(file);
    std::string line;

    std::vector<std::string> file_content;
    while (getline(fin,line)){
        file_content.push_back(line);
    }

    return file_content;
}

template <typename T>
T int_return(std::string line){
    int split_pos;
    std::stringstream num_convert;
    num_convert << line;
    std::string temp;
    int num;
    T array;
    while (!num_convert.eof()){
        num_convert >> temp;
        if (std::stringstream(temp) >> num){
            array.push_back(num);
        }
        temp = "";
    }
    return array;
}

#endif
