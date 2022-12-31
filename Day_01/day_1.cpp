#include "../file_reader.h"
using namespace std;

int main(){
    vector<string> file = get_lines("input.txt");
    vector<string>::const_iterator data = file.begin();
    int max1 = 0, max2 = 0, max3 = 0;
    int cmp = 0;
    vector<string>::iterator it = file.end();
    while (data != file.end()){
        if (*data != ""){
            string val = *data;
            int sum = 0;
            vector<int> number = int_return<vector<int>>(*data);
            cmp += number[0];
        }
        else{
            if (cmp > max1){max3 = max2; max2 = max1; max1 = cmp;}
            else if (cmp > max2 && cmp < max1){max3 = max2; max2 = cmp;}
            else if (cmp > max3 && cmp < max2 && cmp < max1){max3 = cmp;}
            cmp = 0;
        }
        data++;
    }
    cout << max1 << endl; // Part 1
    cout << max1+max2+max3 << endl; // Part 2
}
