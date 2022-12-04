#include "../file_reader.h"
using namespace std;

int main(){
    vector<string> file = get_lines("input.txt");
    vector<string>::const_iterator data = file.begin();
    vector<int> array;
    int count = 0;
    int all_count = 0;
    while(data != file.end()){
        int num = 0;
        for (int i = 0; i < (*data).length(); i++){
            if ((*data)[i] != '-' && (*data)[i] != ','){
                num = num*10 + (*data)[i] - '0';
            }
            else{
                array.push_back(num);
                num = 0;
            }
        }
        array.push_back(num);
        num = 0;
        if (array[0] <= array[2] && array[1] >= array[3]){count++;}
        else if (array[0] >= array[2] && array[1] <= array[3]){count++;}

        if (array[1] >= array[2] && array[0] <= array[3]){all_count++;}
        else if (array[1] <= array[2] && array[0] >= array[3]){all_count++;}
        array.clear();
        data++;
    }
    cout << count << endl; //Part 1
    cout << all_count << endl; //Part 2
}
