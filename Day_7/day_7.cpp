#include "../file_reader.h"
#include <queue>
using namespace std;

struct File{
    string name;
    int size;
    File* parent;
    File(string n, File* parent, int s=0){name = n; size = s; this->parent = parent;}
    File(const File& f){name = f.name; size = f.size; parent = f.parent;}
};

int find(vector<File*>& dirs, string& file_name, File* parent = nullptr){
    for (int i = 0; i < dirs.size(); i++){
        if (dirs[i]->name == file_name && dirs[i]->parent == parent){return i;}
    }
    return -1;
}

int i = 0;
int main(){
    bool test1 = false;
    bool test2 = false;
    vector<string> file = get_lines("input.txt");
    vector<string>::const_iterator data = file.begin(); 
    vector<File*> directory;
    directory.push_back(new File("/",nullptr));
    int total_size = 0;
    File* cur_dir = nullptr;
    int dir_size = 0;
    while (data != file.end()){

        if ((*data).find("$ cd ..") != string::npos){
            cur_dir = cur_dir->parent;
        }
        else if ((*data).find("$ cd ") != string::npos){
            string dir_name = (*data);
            dir_name.erase(0,5);
            int index = find(directory,dir_name,cur_dir);
            if (index != -1){
                cur_dir = (directory[index]);
                data++;
            }
        }
        else if ((*data).find("dir ") != string::npos){
            string dir_name = (*data);
            dir_name.erase(0,4);
            directory.push_back(new File(dir_name,cur_dir));
        }
        else{
            int sum = 0;
            for (int i = 0; i < (*data).length(); i++){
                if (isdigit((*data)[i])){
                    sum = sum*10 + (*data)[i] - '0';
                }
                else{break;}
            }
            cur_dir->size += sum;
        }

        data++;
    }

    for (int i = directory.size()-1; i > 0 ; i--){
        if (directory[i]->parent != nullptr){directory[i]->parent->size += directory[i]->size;}
    }
    for (int i = 0; i < directory.size(); i++){
        if (directory[i]->size <= 100000){
            total_size += directory[i]->size;
        }
    }

    cout << total_size << endl; // Part 1

    int disk_size = 0;

    int free_up_size = 30000000 - (70000000 - directory[0]->size);
    long int min = INT32_MAX;

    for (int i = 0; i < directory.size(); i++){
        if (directory[i]->size > free_up_size){
            if (directory[i]->size < min){
                min = directory[i]->size;
            }
        }
    }

    cout << min << endl; //Part 2
    for (int i = 0; i < directory.size(); i++){
        delete directory[i];
        directory[i] = nullptr;
    }
}
