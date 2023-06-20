#include "../file_reader.h"
using namespace std;

struct pos{
    int x;
    int y;
    pos(int x, int y):x(x),y(y){}
    pos(const pos& p){x=p.x;y=p.y;}
    bool operator==(const pos& p)const {return (x == p.x)&&(y == p.y);}
    bool operator!=(const pos& p)const {return !(*this == p);}
    pos operator-(const pos& p)const {return pos(x-p.x,y-p.y);}
    pos operator+(const pos& p)const {return pos(x+p.x,y+p.y);}
    int numGet()const{
        if (!x && y){return y;}
        else if (!y && x){return x;}
        return 0;
    }
    bool operator>(const pos& otherPos)const {
        pos diff = *(this) - otherPos;
        return diff.numGet() > 0;
    }

    bool operator>=(const pos& otherPos)const {
        pos diff = *(this) - otherPos;
        return diff.numGet() >= 0;
    }
};

pos dir(const pos& p1, const pos& p2){
    pos diff = p1 - p2;
    return diff.x? pos{1,0}:pos{0,1};
}

vector<pos> RockSandPos;

void add_rock(vector<pos>& rock_vec, string substr){
    if (substr != "->"){
        int div = substr.find(",");
        pos rock = {stoi(substr.substr(0,div)), stoi(substr.substr(div+1,substr.size()-div))};  
        rock_vec.push_back(rock);              
    }
}

vector<int> getY(const vector<pos> Pos){
    vector<int> Yvals;
    for (vector<pos>::const_iterator pos = Pos.begin(); pos != Pos.end(); pos++){
        Yvals.push_back(pos->y);
    }
    return Yvals;
}

vector<pos> getCoord(string line){
    vector<pos> edge_coord;
    int prev = -1;
    for (int i = 0; i < line.length(); i++){
        if (line[i] == ' '){
            string substr = line.substr(prev+1,i-prev-1);
            add_rock(edge_coord,substr);
            prev = i;
        }
    }
    add_rock(edge_coord,line.substr(prev+1,line.length()-prev));
    return edge_coord;
}

bool in(const pos& p, const vector<pos>& pos_vec){
    for (const pos& pos: pos_vec){
        if (pos == p){return true;}
    }
    return false;
}

void all_coords(string line){
    vector<pos> edge_coord = getCoord(line);
    int coord1 = 0, coord2 = 1;
    while (coord2 < edge_coord.size())
    {
        const pos& edge1 = edge_coord[coord1];
        const pos& edge2 = edge_coord[coord2];
        pos start = (edge2 > edge1)? edge1:edge2;
        pos end = (start == edge2)? edge1:edge2;
        pos direction = dir(edge1, edge2);

        for (pos curPos = start; end >= curPos; curPos = curPos+direction){
            if (!in(curPos,RockSandPos)){RockSandPos.push_back(curPos);}
        }
        coord1++;coord2++;
    }
}

pos getSandNewPos(const vector<pos>& combinedPos, const pos& sandPos, const int& max){
    if (sandPos.y == max){
        pos newSandpos = sandPos;
        newSandpos.y = max;
        return newSandpos;} // in the case that sand is infinitely falling 
    vector<pos> sameX; 
    for (vector<pos>::const_iterator pos = combinedPos.begin(); pos != combinedPos.end(); pos++){
        if (pos->x == sandPos.x && pos->y > sandPos.y){sameX.push_back(*pos);}// get all the positions with the same X coord
    }
    if (sameX.size() == 0){
        pos newSandpos = sandPos;
        newSandpos.y = max;
        return newSandpos;}
    vector<int> yvals = getY(sameX); // get all the Y coord vals, to find the top most value
    vector<int>::const_iterator minY = min_element(yvals.begin(), yvals.end());
    pos newSandPos = pos{sameX[0].x,*minY-1}; // set the initial position of the sand as 1 above the top most rock in that x axis 

    pos val = pos{-1,-1}; // initialise to fail case
    pos leftTest = newSandPos + pos{-1,1}; // position to check if the sand can fall to the left
    pos rightTest = newSandPos + pos{1,1};// position to check if the sand can fall to the right

    if (!in(leftTest,combinedPos)){val = getSandNewPos(combinedPos, leftTest, max);} // if the left position is empty, run the function recursively 
    else if (!in(rightTest,combinedPos)){val = getSandNewPos(combinedPos,rightTest, max);} // else if the right position is empty, run the function recursively 

    if (val == pos{-1,-1}){return newSandPos;} // if it is the fil case then return the sand position calulated
    return val; //  otherwise get the value of the calculated position
}

// pos isStablised(const vector<pos>& combinedPos, const pos& SandPos, const int& max){
//     int newMax = max+2;

// }

int main(){
    vector<string> file = get_lines("input.txt");
    vector<string>::iterator data = file.begin();

    while(data != file.end()){
        all_coords(*data);
        data++;
    }

    int initialSize = RockSandPos.size();
    vector<int> allY = getY(RockSandPos);
    vector<int>::const_iterator maxdepth = max_element(allY.begin(), allY.end());
    int maxDepth = *maxdepth;
    bool Falling = false;

    while (!Falling){
        pos sand = {500,0};
        sand = getSandNewPos(RockSandPos,sand,maxDepth);
        if (sand.y == maxDepth){Falling = true;}
        RockSandPos.push_back(sand);
    }
    pos& last = RockSandPos[RockSandPos.size()-1];
    cout << RockSandPos.size() - initialSize - 1 << endl;

    Falling = false;
    maxDepth+=2;
    last.y = maxDepth-1;
    while (!Falling){
        pos sand = {500,0};
        sand = getSandNewPos(RockSandPos,sand,maxDepth);
        if (sand == pos{500,0}){Falling = true;}
        if (sand.y == maxDepth){sand.y--;}
        RockSandPos.push_back(sand);
    }
    cout << RockSandPos.size() - initialSize << endl;

}