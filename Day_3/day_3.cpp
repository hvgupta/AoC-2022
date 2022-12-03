#include "../file_reader.h"
using namespace std;

template <typename Iterator, typename T>
Iterator find( Iterator begin, Iterator end,T p){
    Iterator node = begin;
    while (node != end){
        if (*node == p){return node;}
        node++;
    }
    return end;
}

int main(){
    int sum = 0;
    vector<string> file = get_lines("input.txt");
    vector<string>::const_iterator data = file.begin();
    while(data != file.end()){

        vector<char> item_list;

        for (int i = 0; i < ((*data).length()); i++){
            vector<char>::const_iterator pos = find(item_list.begin(),item_list.end(),(*data)[i]);
            if (i < (*data).length()/2){
                if (pos == item_list.end()){
                    item_list.push_back((*data)[i]);
                }
            }

            else{
                if (pos != item_list.end()){
                    int diff = (*pos) - '`';
                    if (diff < 0){
                        diff += 58;
                    }
                    sum += diff;
                    break;
                }
            }

        }

        item_list.clear();
        data++;
    }
    cout << sum << endl;

    data = file.begin();
    int j = 0;
    vector<char> filter1;
    vector<char> filter2;
    int new_sum = 0;
    while (data != file.end()){
        if (j%3 == 0){
            for (int i = 0; i < (*data).length(); i++){
                vector<char>::const_iterator pos = find(filter1.begin(),filter1.end(),(*data)[i]);
                if (pos == filter1.end()){
                    filter1.push_back((*data)[i]);
                }
            }
        }
        else if (j%3 == 1){
            for (int i = 0; i < (*data).length(); i++){
                vector<char>::const_iterator pos = find(filter1.begin(),filter1.end(),(*data)[i]);
                if (pos != filter1.end()){
                    vector<char>::const_iterator pos2 = find(filter2.begin(),filter2.end(),(*data)[i]);
                    if (pos2 == filter2.end()){
                        filter2.push_back((*data)[i]);
                    }
                }
            }
        }
        else if (j%3 == 2){
            for (int i = 0; i < (*data).length(); i++){
                vector<char>::const_iterator pos = find(filter2.begin(),filter2.end(),(*data)[i]);
                if (pos != filter2.end()){
                    int diff = (*data)[i] - '`';
                    if (diff < 0){
                        diff += 58;
                    }
                    new_sum += diff;
                    break;
                }
            }
            filter1.clear();
            filter2.clear();
        }
        j++;
        data++;
    }

    cout << new_sum << endl;
}
