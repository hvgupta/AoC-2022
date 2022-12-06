#include "../file_reader.h"
#include <list>
using namespace std;

int main(){
    vector<string> file = get_lines("input.txt");
    vector<string>::const_iterator data = file.begin();
    int length = 0;
    int message_len = 0;
    bool package_found = false;
    bool message_found = false;
    for (int i = 0; i < (*data).length(); i++){
        list<char> packages;
        list<char> message;
        for (int j = 0; j < 4; j++){
            packages.push_back((*data)[i+j]);
        }
        for (int j = 0; j < 14; j++){
            message.push_back((*data)[i+j]);
        }
        packages.sort();
        packages.unique();
        message.sort();
        message.unique();
        if (packages.size() == 4 && !package_found){
            length = i + 4;
            package_found = true;
        }
        if (message.size() == 14 && !message_found){
            message_len = i+14;
            message_found = true;
        }

        if (message_found && package_found){break;}
    }
    cout << length << endl; //Part 1
    cout << message_len << endl; // Part 2
}
