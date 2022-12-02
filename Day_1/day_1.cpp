#include "../file_reader.h"

vector<string> get_lines(){
    ifstream fin("input.txt");
    string line;

    vector<string> file_content;
    while (getline(fin,line)){
        file_content.push_back(line);
    }

    return file_content;
}

int main(){
    vector<string> file = get_lines();
    vector<string>::iterator data = file.begin();
    int max1 = 0, max2 = 0, max3 = 0;
    int cmp = 0;
    vector<string>::iterator it = file.end();
    while (data != file.end()){
        if (*data != ""){
            string val = *data;
            int sum = 0;
            for (int i = 0; i < val.length(); i++){
                char num = val[i];
                sum = sum*10 + (num-'0');
            }
            cmp += sum;
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
    cout << max1+max2+max3 << endl; //Part 2
}
