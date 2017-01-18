#include <iostream>
#include <fstream>
using namespace std;
int max(int a, int b) { return (a > b)? a: b; }
long long phoneDropTimeRe(int n, long long k){
    if(k  == 0 ){
        return 0;
    }
    if(k == 1  ){
        return 1;
    }
    if(n == 1){
        return k;
    }
    return 1 + phoneDropTimeRe(n-1, k-1) + phoneDropTimeRe(n, k-1);
}
void createDpArray(long long (&arr)[101][64]){
    arr[0][0] = 0;
    for (int i = 1; i < 64; ++i) {
        arr[0][i] = 0;
        arr[1][i] = i;
    }
    for (int j = 1; j < 101; ++j) {
        arr[j][0] = 0;
        arr[j][1] = 1;
    }
    for (int k = 2; k < 101; ++k) {
        for (int i = 2; i < 64; ++i) {
            arr[k][i] = 1 + arr[k-1][i-1] + arr[k][i-1];
        }
    }
}


int main(int argc, char* argv[]) {
    /*check numbers of argument*/
    if(argc!=4){
        cout<<"Some arguments are missed!"<<endl;
        return -1;
    }
    /*Create fstream for file I/O*/
    ifstream input(argv[2]);
    ofstream output(argv[3],ios::trunc|ios::out);

    if(atoi(argv[1])){
        int phoneVal;
        long long floorVal, drop, floorCount;
        while (input>>phoneVal && input>>floorVal){
            if(phoneVal==0 && floorVal==0){
                break;
            }
            floorCount = 0;
            for ( drop = 1; drop < 64; ++drop) {
                if(phoneDropTimeRe(phoneVal, drop)>=floorVal){
                    break;
                }
            }
            if(drop>63){
                output<<"More than 63 times needed."<<endl;
                continue;
            }
            else{
                output<<drop<<endl;
            }
            long long i = drop -1;
            do{
                floorCount += 1 + phoneDropTimeRe(phoneVal - 1, i);
                output<<floorCount<<" ";
                --i;
            }while (i>=0);
            output<<endl;
        }
    }
    else{
        long long dp[101][64];
        createDpArray(dp);
        int phoneVal;
        long long floorVal, drop, floorCount;
        while (input>>phoneVal && input>>floorVal){
            if(phoneVal==0 && floorVal==0){
                break;
            }
            floorCount = 0;
            for ( drop = 1; drop < 64; ++drop) {
                if(dp[phoneVal][drop] >= floorVal){
                    break;
                }
            }
            if(drop>63){
                output<<"More than 63 times needed."<<endl;
                continue;
            }
            else{
                output<<drop<<endl;
            }
            long long i = drop -1;
            do{
                floorCount += 1 + dp[phoneVal-1][i];
                output<<floorCount<<" ";
                --i;
            }while (i>=0);
            output<<endl;
        }
    }

    return 0;
}