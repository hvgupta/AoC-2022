#include "../file_reader.h"
#include <queue>
#include <array>
#include <algorithm>
using namespace std;

const int Part = 2; // change the part here
const int rounds = 10000; // the number of rounds
int product = 1;

struct Monkey{
    deque<long long> items;
    array<int, 5> condition_information;
    int (*pass_to_monkey)(long long&, array<int,5> condition_information, const int Part, const int product);

    Monkey(const Monkey& monkey){
        items = monkey.items;
        condition_information = monkey.condition_information;
        pass_to_monkey = [](long long& worry, array<int,5> condition_information, const int Part, const int product){
            if (condition_information[0] == '*'){
                if (condition_information[1] == '^'){worry *= worry;}
                else{worry *= condition_information[1];}
            }
            else{
                if (condition_information[1] == '^'){worry += worry;}
                else{worry += condition_information[1];}
            }

            if (Part == 1){worry /= 3;}
            else{worry %= product;}

            if (worry%condition_information[2] == 0){return condition_information[3];}
            else{return condition_information[4];}
        };
    }
    Monkey(){}
};

vector<Monkey*> monkeys;

void monkey_data(vector<string>::const_iterator data, vector<string>::const_iterator file_end){
    int i = 0;
    while(data != file_end){
        if ((*data).find("Monkey ") != string::npos){
            data++;
            string line = (*data);
            line.erase(0,18);
            Monkey monkey;
            monkey.items = int_return<deque<long long>>(line);
            data++;
            char condition = ((*data).find("*") != string::npos)?'*':'+';
            vector<int> num_array = int_return<vector<int>>(*data);
            int num = (num_array.size() == 1) ? num_array[0]: '^';
            int test_num = int_return<vector<int>>(*(++data))[0];
            int true_monkey = int_return<vector<int>>(*(++data))[0];
            int false_monkey = int_return<vector<int>>(*(++data))[0];
            monkey.condition_information = {condition,num,test_num,true_monkey,false_monkey};
            monkeys.push_back(new Monkey(monkey));
            data++;
        }
        if (data == file_end){return;}
        data++;
        i++;
    }
}

int main(){
    vector<string> file = get_lines("input.txt");
    vector<string>::const_iterator data = file.begin();

    monkey_data(data,file.end());
    for (int i = 0; i < monkeys.size(); i++){
        product *= monkeys[i]->condition_information[2]; 
    }

    array<long long, 8> counter = {0,0,0,0,0,0,0,0};
    for (int round = 0; round < rounds; round++){
        for (int monkey_num = 0; monkey_num < monkeys.size(); monkey_num++){
            const int size = monkeys[monkey_num]->items.size();
            counter[monkey_num]+=size;
            for (int item_num = 0; item_num < size; item_num++){
                long long worry = 0;
                worry  = monkeys[monkey_num]->items.front();
                monkeys[monkey_num]->items.pop_front();
                int monkey_pos = monkeys[monkey_num]->pass_to_monkey(worry,monkeys[monkey_num]->condition_information, Part, product);
                monkeys[monkey_pos]->items.push_back(worry);
            }
        }
    }
    sort(counter.begin(),counter.end());
    cout << counter[counter.size()-1]*counter[counter.size()-2] << endl; // Part 1 and 2
    for (int i = 0; i < monkeys.size(); i++){delete monkeys[i];}
}
