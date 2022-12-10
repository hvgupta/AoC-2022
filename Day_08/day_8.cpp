#include "../file_reader.h"
using namespace std;

int main(){
    vector<string> file = get_lines("input.txt");
    vector<string>::const_iterator data = file.begin();   
    int trees_visible = 2*(*data).length();
    int cur_max = 0;
    while(data+2 != file.end()){
        data++;
        for (int i = 1; i < (*data).length()-1; i++){
            int tree_height = (*data)[i];
            int tracker = (*data)[i] - '0';
            bool visible = false;
            int j = 1;
            bool north = true, south = true, east = true, west = true;
            int max = 1;
            while (true){
                if (i-j < 0 && west){west = false; visible = true; max *= (j-1);}
                if (i+j == (*data).length() && east){east = false; visible = true; max *= (j-1);}
                if ((data-j+1) == file.begin() && north){north = false; visible = true; max *= (j-1);}
                if ((data+j) == file.end() && south){south = false; visible = true; max *= (j-1);}

                if (west){
                    if ((*data)[i-j] >= tree_height){
                        west = false;
                        max *= j;
                    }
                }
                if (south){
                    if ((*(data+j))[i] >= tree_height){
                        south = false;
                        max *= j;
                    }
                }
                if (east){
                    if ((*data)[i+j] >= tree_height){
                        east = false;
                        max *= j;
                    }
                }
                if (north){
                    if ((*(data-j))[i] >= tree_height){
                        north = false;
                        max *= j;
                    }
                }
                if (!north && !east && !south && !west){
                    if (visible){trees_visible+=1;}
                    break;
                }
                j++;
            }
            if (cur_max < max){
                cur_max = max;
            }
        }
        trees_visible+=2;
    } 
    cout << trees_visible << endl; //Part 1
    cout << cur_max << endl; // Part 2

}
