#include "../file_reader.h"
#include <array>
#include <list>
using namespace std;

#define LEN 1 // change this number for parts

#define x first
#define y second
#define head 0
typedef typename std::pair<int,int> position;
position operator-(position pos1, position pos2){return position{pos2.x-pos1.x,pos2.y-pos1.y};}

vector<position> past_coord;
array<position,LEN+1> all_cord;

bool move(position pos){
    if (abs(pos.x) > 1 || abs(pos.y) > 1){
        return true;
    }
    return false;
}

void add_if(position coord){
    for (int i = 0; i < past_coord.size(); i++){
        position pos = past_coord.at(i);
        if (pos.x == coord.x && pos.y == coord.y){return;}
    }
    past_coord.push_back(coord);
}

void knot_update(int update_index, int head_index){
    position pos_dif = all_cord[update_index] - all_cord[head_index];
    if (move(pos_dif)){
        if (abs(pos_dif.x) > 0 && abs(pos_dif.y) > 0){
            all_cord[update_index].x += (pos_dif.x > 0) ? 1:-1;
            all_cord[update_index].y += (pos_dif.y > 0) ? 1:-1;
        }
        else if (abs(pos_dif.x) > 1){all_cord[update_index].x += (pos_dif.x > 0)? 1:-1;}
        else if (abs(pos_dif.y) > 1){all_cord[update_index].y += (pos_dif.y > 0)? 1:-1;}

        if (update_index == LEN){
            
            add_if(all_cord[update_index]);
            }
        if (update_index+1 <= LEN){knot_update(update_index+1,update_index);}
    }

    else{return;}

}

int main(){
    past_coord.push_back({0,0});
    vector<string> file = get_lines("input.txt");
    vector<string>::const_iterator data = file.begin();
    while (data != file.end()){
        char dir = (*data)[0];
        string strNum = (*data);
        strNum.erase(0,2);
        int num = stoi(strNum);
        
        for (int i = 0; i < num; i++){
            switch (dir){
                case 'U':   all_cord[head].y += 1;
                    break;
                case 'D':   all_cord[head].y -= 1;
                    break;
                case 'L':   all_cord[head].x -= 1;
                    break;
                case 'R':   all_cord[head].x += 1;
                    break;
            }
            knot_update(head+1,head);
        }

        data++;
    }

    cout << past_coord.size() << endl; //Part 1 abd Part 2
}
