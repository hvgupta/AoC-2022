#include "../file_reader.h"
#include <sstream>
#include <map>
using namespace std;

#define key first 
#define value second

map<char,int> cycle_vals {{'n',1},{'a',2}};
const int breakpoints[6] = {20,60,100,140,180,220};

int main(){
    vector<string> file = get_lines("input.txt");
    vector<string>::const_iterator data = file.begin();

    int pos = 0;
    string display[6] = {""};
    int xVal = 1;
    int breakPointNum = 0;
    int num_cycles = 1;
    int sum = 0;

    while (data != file.end()){
        map<char,int>::iterator cycles = cycle_vals.find((*data)[0]);
        if (num_cycles == breakpoints[breakPointNum] || num_cycles + cycles->value > breakpoints[breakPointNum]){
            sum += xVal*breakpoints[breakPointNum];
            breakPointNum++;
        }
        for (int x = 0; x < cycles->value; x++){
            int index = pos/40;
            if (abs(xVal - (pos%40)) <= 1){
                display[index] += "#";
                }
            else{display[index] += ".";}
            pos++;
            num_cycles++;
        }
        if (cycles->value == 2){
            string line = (*data);
            line.erase(0,5);
            int value_added;
            stringstream(line) >> value_added;
            xVal += value_added;
        } 

        data++;
    }
    cout << sum << endl; //Part 1

    for (int i = 0; i < 6; i++){
        cout << display[i] << endl; //Part 2
    }
}
