#include "../file_reader.h"

int main(){
    vector<string> file = get_lines("input.txt");

    int points = 0;
    int opponent_move = 0, strat_move = 0;
    vector<string>::iterator data = file.begin();
    while(data != file.end()){
        opponent_move = (*data)[0] - 'A';
        strat_move = (*data)[2] - 'X';
        if (opponent_move == strat_move){points += strat_move+4;}
        else if ((opponent_move+1)%3 == strat_move){points += strat_move+7;}
        else {points += strat_move+1;}
        data++;
    }
    cout << points << endl;

    int new_points = 0;
    data = file.begin();
    while (data != file.end()){
        opponent_move = (*data)[0] - 'A';
        strat_move = (*data)[2] - 'X';
        strat_move *= 3;
        if (strat_move == 0){                
            int move = abs(opponent_move+2)%3;
            new_points += move+1;
        }
        else if (strat_move == 3){new_points += opponent_move+strat_move+1;}
        else if (strat_move == 6){                
            int move = (opponent_move+1)%3;
            new_points+= move+strat_move+1;
        }
        data++;
    }
    cout << new_points << endl;
}
