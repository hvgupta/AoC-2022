#include "../file_reader.h"
#include <array>
using namespace std;

typedef vector<string> vec;

vec split_along_comma(string line){
    vec splitted_line;
    int start = 1; int end = 1;
    int count = 0;
    if (line.find(",") != string::npos){
        for (int index = 1; index < line.length()-1; index++, end++){
            if (line[index] == '['){count++;}
            else if (line[index] == ']'){count--;}
            else if (!count && line[index] == ','){
                string substr = line.substr(start,end-start);
                start = end+1;
                splitted_line.push_back(substr);
            }
        }
        splitted_line.push_back(line.substr(start,end-start));
    }
    else{
        if (isdigit(line[0])){splitted_line.push_back(line);}
        else if (line != "[]" && line.find("[") != string::npos && line.find("]") != string::npos){
            splitted_line.push_back(line.substr(1,line.size()-2));
        }
    }
    return splitted_line;
}

int compare(const vec& left,const vec& right){

    int minimum = min(left.size(),right.size());
    for (int index = 0; index < minimum; index++){
        if (left[index][0] != '['  && right[index][0] != '['){
            int intL = stoi(left[index]);
            int intR = stoi(right[index]);
            if (intL < intR){return 1;}
            else if (intL > intR){return -1;}
        }
        else{
            int state =  compare(split_along_comma(left[index]), split_along_comma(right[index]));
            if (state != 0){return state;}
        }
    }
    if (left.size() < right.size()){return 1;}
    else if (left.size() > right.size()){return -1;}
    return 0;
}

int firstNum_get(string line){
    for (int i = 0; i < line.length(); i++){
        if (line[i] == ']'){break;}
        if (line[i] == '1' && line[i+1] == '0'){return 10;}
        else if (isdigit(line[i])){return line[i]-'0';}
    }
    return -1;
}

int main(){
    array<int,12> first_num_count;
    first_num_count.fill(0);
    vec file = get_lines("input.txt");
    vec::const_iterator data = file.begin();
    int index = 1;
    int count = 0;

    while(data != file.end()){
        vec left = split_along_comma(*data);
        data++;
        vec right = split_along_comma(*data);
        if (compare(left,right) == 1){count+= index;}
        index++;
        if (data+1 == file.end()){break;}
        ++++data;
    }

    data = file.begin();
    while (data != file.end())
    {
        if ((*data) == ""){data++;}
        first_num_count[firstNum_get(*data)+1]++;
        data++;
    }
    int multiply = 1;
    index = 1;
    for (int i = 0; i < 12; i++){
        if (i != 3 && i != 7){index+= first_num_count[i];}
        else{
            multiply*=index;
            index+= first_num_count[i]+1;
        }
    }

    cout << count << endl; //Part 1
    cout << multiply << endl; // Part 2
    
}
