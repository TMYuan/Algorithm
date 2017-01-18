#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;
int main(int argc, char* argv[]) {
    int row, column;
    char arr[1000][1000];
    ofstream output("map.txt", ios::trunc|ios::out);
    row = atoi(argv[1]);
    column = atoi(argv[2]);
    srand( (unsigned)time(NULL) );
    for (int i = 0; i < column; ++i) {
        arr[0][i] = 'x';
    }
    for (int j = 0; j < row; ++j) {
        arr[j][0] = 'x';
    }
    for (int k = 1; k < row; ++k) {
        for (int i = 1; i < column; ++i) {
            //arr[k][i] = rand()%2;
            if(rand()%2 == 1){
                arr[k][i] = '1';
            }
            else{
                arr[k][i] = '0';
            }
        }
    }
    output<<column<<" "<<row<<endl;
    for (int l = 0; l < row; ++l) {
        for (int i = 0; i < column; ++i) {
            output<<arr[l][i];
        }
        output<<endl;
    }
    return 0;
}