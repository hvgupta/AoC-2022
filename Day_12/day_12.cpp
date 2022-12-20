#include "../file_reader.h"
#include <algorithm>
#include <queue>
using namespace std;

const int PART = 1; //to change the Part, change this number

struct Cell{
    int x;
    int y;
    int elevation;
    bool visited = false;
    vector<Cell*> parent;
    Cell(int x,int y, int ele):x(x), y(y), elevation(ele), parent({}){}
    bool operator==(const Cell& point){
        if (this == nullptr){return false;}
        return (x == point.x && y == point.y);}
};
vector<vector<Cell*>> grid;

void reset(){
    for (int i = 0; i < grid.size(); i++){
        for (int j = 0; j < grid[i].size(); j++){
            grid[i][j]->visited = false;
            grid[i][j]->parent = {};
        }
    }
}

bool is_parent(const Cell& point,const Cell& parent){
    for (int i = 0; i < point.parent.size(); i++){
        if (*(point.parent[i]) == parent ){return true;}
    }
    return false;
}

bool is_there(deque<Cell*>& points, Cell& point){
    for (int i = 0; i < points.size(); i++){
        return (*(points[i]) == point);
    }
    return false;
}

bool is_there(vector<Cell*>& points, Cell& point){
    for (int i = 0; i <  points.size(); i++){
        return (*(points[i]) == point);
    }
    return false;
}

void point_set(Cell* new_point, Cell* old_point, deque<Cell*>& copy){
    if (!is_there(new_point->parent,*old_point)){new_point->parent.push_back(old_point);}
    new_point->visited = true;
    if (!is_there(copy,*new_point)){copy.push_back(new_point);}
}

vector<Cell*> start_vec;

int main(){
    vector<string> file = get_lines("input.txt");
    int len = INT16_MAX;
    int x_coord = 0;
    int y_coord = 0;
    int start_x = 0, start_y = 0;

    vector<string>::const_iterator iterator = file.begin();
    Cell* end;

    while (iterator != file.end())
    {
        x_coord = 0;
        vector<Cell*> line;
        for (char c: *iterator){
            line.push_back(new Cell(x_coord,y_coord, c-'a'));
            x_coord++;
            if (c == 'S'){
                Cell* start = line[line.size()-1];
                start->elevation = 0;
                start_vec.push_back(start);
            }
            else if (c == 'a' && PART == 2){
                start_vec.push_back(line[line.size()-1]);
            }
            else if (c == 'E'){
                end = line[line.size()-1];
                line[line.size()-1]->elevation = 'z'-'a';
            }
        }
        grid.push_back(line);
        iterator++;
        y_coord++;
    }

    for (Cell* start: start_vec){
        start->visited = true;
        deque<Cell*> considerCells;
        considerCells.push_back(start);
        bool reached = false;
        while (!reached){
            int i = 0;
            deque<Cell*> temp;
            for (Cell* cell: considerCells){
                    if (!cell->visited){cell->visited = true;}
                    if (cell == end){
                        reached = true; break;}
                    if (cell->x-1 >= 0 && grid[cell->y][cell->x-1]->elevation - cell->elevation <= 1 && !grid[cell->y][cell->x-1]->visited){
                        Cell* new_point = grid[cell->y][cell->x-1];
                        point_set(new_point,cell,temp);
                    }
                    if (cell->x+1 < grid[cell->y].size() && grid[cell->y][cell->x+1]->elevation - cell->elevation <=1 && !grid[cell->y][cell->x+1]->visited){
                        Cell* new_point = grid[cell->y][cell->x+1];
                        point_set(new_point,cell,temp);
                    }
                    if (cell->y-1 >= 0 && grid[cell->y-1][cell->x]->elevation - cell->elevation <= 1 && !grid[cell->y-1][cell->x]->visited){
                        Cell* new_point = grid[cell->y-1][cell->x];
                        point_set(new_point,cell,temp);
                    }
                    if (cell->y+1 < grid.size() && grid[cell->y+1][cell->x]->elevation - cell->elevation <= 1 && !grid[cell->y+1][cell->x]->visited){
                        Cell* new_point = grid[cell->y+1][cell->x];
                        point_set(new_point,cell,temp);
                    }
                i++;
            }
            if (considerCells.size() == 0){break;}
            considerCells.clear();
            considerCells = temp;
        }  

        Cell* cur_cel = end;
        int temp_len = 0;
        if (end->parent.size() != 0){
            while(true){
                if (cur_cel == start){break;}
                cur_cel = cur_cel->parent[0];
                temp_len++;
            }
        }
        else{temp_len = INT16_MAX;}
        reset();
        if (temp_len < len){len = temp_len;}
    }

    cout << len << endl;

    for (int i = 0; i < grid.size(); i++){
        for (int j = 0; j < grid[i].size(); j++){
            delete grid[i][j];
            grid[i][j] = nullptr;
        }
    }
}
