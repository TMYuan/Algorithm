#include <iostream>
#include <fstream>
#include<utility>
#include <vector>
#include <ctime>

using namespace std;
class node{
public:
    int i, j, dir;
    node(){
        i=0;
        j=0;
        dir=0;
    }
    node(int _i, int _j, int _dir){
        i = _i;
        j = _j;
        dir = _dir;
    }
};

int main(int argc, char* argv[]) {
    clock_t start,stop;
    start=clock();

    /*File I/O*/
    ifstream input(argv[1]);
    ofstream output(argv[2], ios::trunc|ios::out);

    /*Generate Map*/
    int column, row;
    int blue = 0, yellow = 0;
    char **map;
    bool **mark_b, **mark_y;
    input>>column;
    input>>row;
    map = new char*[row+2];
    mark_b = new bool*[row+2];
    mark_y = new bool*[row+2];
    for (int k = 0; k < column + 2; ++k) {
        map[k] = new char[column + 2];
        mark_b[k] = new bool[column + 2];
        mark_y[k] = new bool[column + 2];
    }
    for (int l = 0; l < column + 2; ++l) {
        map[0][l] = 'n';
        mark_b[0][l] = true;
        mark_y[0][l] = true;
        map[row+1][l] = 'n';
        mark_b[row+1][l] = true;
        mark_y[row+1][l] = true;
    }
    for (int m = 0; m < row + 2; ++m) {
        map[m][0] = 'n';
        mark_b[m][0] = true;
        mark_y[m][0] = true;
        map[m][column + 1] = 'n';
        mark_b[m][column + 1] = true;
        mark_y[m][column + 1] =true;
    }
    for (int i = 1; i < row + 1; ++i) {
        for (int j = 1; j < column + 1; ++j) {
            input>>map[i][j];
            mark_b[i][j] = false;
            mark_y[i][j] = false;
            if(map[i][j] == '0'){
                ++yellow;
            }
            else if(map[i][j] == '1'){
                ++blue;
            }
        }
    }

    //cout<<"yellow:"<<yellow<<endl;
    //cout<<"blue:"<<blue<<endl;
    /*for (int i1 = 0; i1 < row+2; ++i1) {
        for (int i = 0; i < column+2; ++i) {
            cout<<map[i1][i]<<" ";
        }
        cout<<endl;
    }
    for (int i2 = 0; i2 < row+2; ++i2) {
        for (int i = 0; i < column+2; ++i) {
            cout<<mark_b[i2][i]<<" ";
        }
        cout<<endl;
    }*/

    /*Begin to find path*/
    node current_node, next_node;
    vector<node> stack_b, stack_y;
    vector<vector<node>> answer;
    vector<int> color;
    bool finish_b, finish_y;
    int valid_b, valid_y;
    //stack_b.push_back(node(0, column, 0));
    //stack_y.push_back(node(0, column, 0));

    while(yellow > 0 || blue > 0){
        stack_b.push_back(node(1, column, 0));
        finish_b = false;
        mark_b[1][column] = true;
        valid_b = 0;
        while(blue > 0&& !stack_b.empty() && !finish_b){
            current_node = stack_b.back();
            //cout<<"At the End "<<current_node.i<<" and "<<current_node.j<<" and dir: "<<current_node.dir<<endl;
            if(map[current_node.i][current_node.j] == '1'){
                --valid_b;
            }
            stack_b.pop_back();
            while(current_node.dir < 4){
                if(current_node.dir == 0){
                    next_node.i = current_node.i;
                    next_node.j = current_node.j + 1;
                    ++current_node.dir;
                }
                else if(current_node.dir == 1){
                    next_node.i = current_node.i + 1;
                    next_node.j = current_node.j;
                    ++current_node.dir;
                }
                else if(current_node.dir == 2){
                    next_node.i = current_node.i - 1;
                    next_node.j = current_node.j;
                    ++current_node.dir;
                }
                else if(current_node.dir == 3){
                    next_node.i = current_node.i;
                    next_node.j = current_node.j - 1;
                    ++current_node.dir;
                }
                if(next_node.i == row && next_node.j == 1){
                    finish_b = true;
                    stack_b.push_back(current_node);
                    if(map[current_node.i][current_node.j] == '1'){
                        ++valid_b;
                    }
                    break;
                }
                if(!mark_b[next_node.i][next_node.j] && (map[next_node.i][next_node.j] == '1' || map[next_node.i][next_node.j] == 'x')){
                    if(map[current_node.i][current_node.j] == '1'){
                        ++valid_b;
                    }
                    mark_b[next_node.i][next_node.j] = true;
                    stack_b.push_back(current_node);
                    current_node = next_node;
                    //cout<<"current_node : "<<current_node.i<<" and "<<current_node.j<<endl;
                }
            }
        }
        //cout<<"finish blue color"<<endl;

        stack_y.push_back(node(1, column, 0));
        finish_y = false;
        mark_y[1][column] = true;
        valid_y = 0;
        while(yellow > 0 && !stack_y.empty() && !finish_y){
            current_node = stack_y.back();
            //cout<<"At the End "<<current_node.i<<" and "<<current_node.j<<" and dir: "<<current_node.dir<<endl;
            if(map[current_node.i][current_node.j] == '0'){
                --valid_y;
            }
            stack_y.pop_back();
            while(current_node.dir < 4){
                if(current_node.dir == 0){
                    next_node.i = current_node.i;
                    next_node.j = current_node.j + 1;
                    ++current_node.dir;
                }
                else if(current_node.dir == 1){
                    next_node.i = current_node.i + 1;
                    next_node.j = current_node.j;
                    ++current_node.dir;
                }
                else if(current_node.dir == 2){
                    next_node.i = current_node.i - 1;
                    next_node.j = current_node.j;
                    ++current_node.dir;
                }
                else if(current_node.dir == 3){
                    next_node.i = current_node.i;
                    next_node.j = current_node.j - 1;
                    ++current_node.dir;
                }
                if(next_node.i == row && next_node.j == 1){
                    finish_y = true;
                    stack_y.push_back(current_node);
                    if(map[current_node.i][current_node.j] == '0'){
                        ++valid_y;
                    }
                    break;
                }
                if(!mark_y[next_node.i][next_node.j] && (map[next_node.i][next_node.j] == '0' || map[next_node.i][next_node.j] == 'x')){
                    if(map[current_node.i][current_node.j] == '0'){
                        ++valid_y;
                    }
                    mark_y[next_node.i][next_node.j] = true;
                    stack_y.push_back(current_node);
                    current_node = next_node;
                    //cout<<"current_node : "<<current_node.i<<" and "<<current_node.j<<endl;
                }
            }
        }

        //cout<<"finish yellow color"<<endl;
        //cout<<"valid_b: "<<valid_b<<"  valid_y: "<<valid_y<<endl;
        /*valid_b = 0;
        valid_y = 0;
        for (int k = 0; k < stack_b.size(); ++k) {
            if(map[stack_b[k].i][stack_b[k].j] == '1'){
                ++valid_b;
            }
        }
        for (int l = 0; l < stack_y.size(); ++l) {
            if(map[stack_y[l].i][stack_y[l].j] == '0'){
                ++valid_y;
            }
        }*/
        //cout<<"valid_b: "<<valid_b<<"  valid_y: "<<valid_y<<endl;
        if(valid_b >= valid_y){
            answer.push_back(stack_b);
            color.push_back(1);
            /*for (int i = 0; i < stack_b.size(); ++i) {
                //cout<<"position i: "<<answer[n][i].i<<"  position j:  "<<answer[n][i].j<<"  ";
                cout<<column*stack_b[i].i-(stack_b[i].j-1)<<" ";
            }
            cout<<endl;*/
            while(!stack_b.empty()){
                if(map[stack_b.back().i][stack_b.back().j] == '1'){
                    --blue;
                    map[stack_b.back().i][stack_b.back().j] = 'x';
                    //cout<<"i: "<<stack_b.back().i<<", j: "<<stack_b.back().j<<endl;
                }
                stack_b.pop_back();
            }
            //cout<<"color now (b/y): "<<blue<<" and "<<yellow<<endl;
            stack_y.resize(0);
        }
        else{
            answer.push_back(stack_y);
            color.push_back(0);
            /*for (int i = 0; i < stack_y.size(); ++i) {
                //cout<<"position i: "<<answer[n][i].i<<"  position j:  "<<answer[n][i].j<<"  ";
                cout<<column*stack_y[i].i-(stack_y[i].j-1)<<" ";
            }
            cout<<endl;*/
            while(!stack_y.empty()){
                if(map[stack_y.back().i][stack_y.back().j] == '0'){
                    --yellow;
                    map[stack_y.back().i][stack_y.back().j] = 'x';
                }
                stack_y.pop_back();
            }
            //cout<<"color now (b/y): "<<blue<<" and "<<yellow<<endl;
            stack_b.resize(0);
        }
        for (int i = 1; i < row + 1; ++i) {
            for (int j = 1; j < column + 1; ++j) {
                mark_b[i][j] = false;
                mark_y[i][j] = false;
            }
        }
        /*for (int i1 = 0; i1 < row+2; ++i1) {
            for (int i = 0; i < column+2; ++i) {
                cout<<map[i1][i]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;*/

    }
    output<<answer.size()<<endl;
    for (int n = answer.size()-1; n >= 0; --n) {
        output<<color[n]<<" ";
        for (int i = 0; i < answer[n].size(); ++i) {
            //cout<<"position i: "<<answer[n][i].i<<"  position j:  "<<answer[n][i].j<<"  ";
            output<<column*answer[n][i].i-(answer[n][i].j-1)<<" ";
        }
        output<<column*row<<endl;
    }

    for (int j1 = 0; j1 < column + 2; ++j1) {
        delete [] map[j1];
        delete [] mark_b[j1];
        delete [] mark_y[j1];
    }

    stop=clock();
    cout<<"consume "<<double(stop-start)/CLOCKS_PER_SEC<<" second"<<endl;

    return 0;
}