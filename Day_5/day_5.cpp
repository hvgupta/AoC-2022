#include "../file_reader.h"
#include <deque>
#include <array>
#include <sstream>
using namespace std;

int main(){
    vector<string> file = get_lines("input.txt");
    vector<string>::const_iterator data = file.begin();
    array<deque<char>,9> stacks;
    while (*data != ""){
        for (int i = 1; i < (*data).length(); i+=4){
            if ( (*data)[i] != ' '){
                stacks[(i-1)/4].push_back((*data)[i]); 
            }
        }
        data++;
    }
    for (int i = 0; i < 9; i++){stacks[i].pop_back();}
    array<deque<char>,9>stack2 = stacks;
    data++;
    while (data != file.end()){

        stringstream s_stream;
        s_stream << *data;
        int temp_int;
        vector<int> num_data;
        while (!s_stream.eof()){
            string temp;
            s_stream >> temp;
            if (stringstream(temp) >> temp_int){
                num_data.push_back(temp_int);
            }
        }
        vector<char> temp;

        for (int i = 0; i < num_data[0]; i++){
            stacks[num_data[2]-1].push_front(stacks[num_data[1]-1][0]);
            stacks[num_data[1]-1].pop_front();

            temp.push_back(stack2[num_data[1]-1][0]);
            stack2[num_data[1]-1].pop_front();
        }
        for (int i = 0; i < num_data[0]; i++){

            stack2[num_data[2]-1].push_front(temp[temp.size()-1]);
            temp.pop_back();
        }

        data++;
    }
    for (int i = 0; i < 9; i++){
        cout << stacks[i][0]; // Part 1
    }
    cout << "\n";

    for (int i = 0; i < 9; i++){
        cout << stack2[i][0]; //Part 2
    }
    cout << "\n";
}
