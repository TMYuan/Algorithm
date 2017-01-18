#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;
int main(int argc, char* argv[]){
	int number = atoi(argv[1]);
	unsigned seed;
	seed = (unsigned)time(NULL);
	srand(seed);
	ofstream output("testcase");
	for(int i=0;i<number;++i){
		output<<rand()<<" ";
	}
	return 0;
} 
