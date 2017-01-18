#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;
void iSort(vector<int>*,int, int);

void mSort(vector<int>*,int, int);
void merge(vector<int>*,int, int, int);

void hSort(vector<int>*);
void maxHeap(vector<int>*, int, int);
void buildHeap(vector<int>*);

void qSort(vector<int>*,int, int);

int main(int argc, char* argv[]) {
    /*check numbers of argument*/
    if(argc!=4){
        cout<<"Some arguments are missed!"<<endl;
        return -1;
    }
    /*Create fstream for file I/O*/
    ifstream input(argv[2]);

    /*Read value in vector*/
    vector<int> arr;
    if(input){
        int value;
        while (input>>value){
            arr.push_back(value);
        }
    }
    unsigned seed;
    seed = (unsigned)time(NULL);
    srand(seed);
    /*Create clock to calculate time*/
    /*clock_t start,stop;
    start=clock();*/
    /*Run Sorting depend on argument*/
    switch (atoi(argv[1])){
        case 1:
            iSort(&arr,0,arr.size()-1);
            break;
        case 2:
            mSort(&arr,0,arr.size()-1);
            break;
        case 3:
            hSort(&arr);
            break;
        case 4:
            qSort(&arr,0,arr.size()-1);
            break;
        default:
            break;
    }
    /*stop=clock();
    cout<<"consume "<<double(stop-start)/CLOCKS_PER_SEC<<" second"<<endl;*/

    /*Write data on file*/
    ofstream output(argv[3],ios::trunc|ios::out);
    for (int i = 0; i < arr.size(); ++i) {
        output<<arr.at(i)<<" ";
    }
    return 0;
}

void iSort(vector<int>* arr, int left, int right){
    int key;
    for (int j = left + 1; j < right + 1; ++j) {
        key = arr->at(j);
        int i = j-1;
        while(i>-1 && arr->at(i)>key){
            arr->at(i+1) = arr->at(i);
            --i;
        }
        arr->at(i+1) = key;
    }
}
void mSort(vector<int>* arr, int p, int r){
    int q;
    if(p<r){
        q = p+(r-p)/2;
        mSort(arr,p,q);
        mSort(arr,q+1,r);
        merge(arr,p,q,r);
    }
}
void merge(vector<int>* arr, int p, int q, int r){
    int n1 = q-p+1;
    int n2 = r-q;
    int i=0, j=0;
    vector<int> left(n1+1), right(n2+1);

    for (i = 0; i < n1; ++i) {
        left[i] = (*arr)[p+i];
    }
    for (j = 0; j < n2; ++j) {
        right[j] = (*arr)[q+j+1];
    }
    left[n1]=numeric_limits<int>::max();
    right[n2]=numeric_limits<int>::max();
    i=0;
    j=0;
    for(int k=p;k<(r+1);++k){
	    if(left[i]<=right[j]){
	        (*arr)[k]=left[i];
	        ++i;
	    }
	    else{
            (*arr)[k]=right[j];
	        ++j;
	    }
    }
}
void hSort(vector<int>* arr){
    buildHeap(arr);
    int size = arr->size();
    for (int i = arr->size()-1; i > 0 ; --i) {
        int temp = arr->at(0);
        arr->at(0) = arr->at(i);
        arr->at(i) = temp;
        --size;
        maxHeap(arr, 0, size);
    }
}
void maxHeap(vector<int>* arr, int i, int size){
    int left, right, large;
    if(i==0){
        left=1;
        right=2;
    }
    else{
        left=2*i+1;
        right=2*i+2;
    }
    if(left < size&& arr->at(left)>arr->at(i)){
        large = left;
    }
    else{
        large = i;
    }
    if(right < size&&arr->at(right)>arr->at(large)){
        large = right;
    }
    if(large != i){
        int temp = arr->at(i);
        arr->at(i) = arr->at(large);
        arr->at(large) = temp;
        maxHeap(arr,large,size);
    }
}
void buildHeap(vector<int>* arr){
    for (int i = arr->size()/2-1; i >=0 ; --i) {
        maxHeap(arr,i,arr->size());
    }
}
void qSort(vector<int>* arr,const int left, const int right){
    if(left<right){
        int i = left, j = right+1;
        int number=right-left+1;
	    int target = left+(rand()%number);
        int temp1 = arr->at(target);
        arr->at(target) = arr->at(left);
        arr->at(left) = temp1;
        int pivot = arr->at(left);

        do{
            do i++; while (i<j && arr->at(i) < pivot);
            do j--; while (i<=j && arr->at(j) > pivot);
            if(i<j) {
                int temp2 = arr->at(i);
                arr->at(i) = arr->at(j);
                arr->at(j) = temp2;
            }
        } while (i<j);

        int temp = arr->at(left);
        arr->at(left) = arr->at(j);
        arr->at(j) = temp;

        qSort(arr, left, j-1);
        qSort(arr, j+1, right);
    }
    /*if(left<right){
        int i,j;
        int key=arr->at(left);
        i=left;
        j=right;
        while (i<j){
            while(arr->at(j)>=key&&i<j){
                j--;
            }
            arr->at(i)=arr->at(j);
            while(arr->at(i)<=key&&i<j){
                i++;
            }
            arr->at(j)=arr->at(i);
        }
        arr->at(i)=key;
        qSort(arr, left, j-1);
        qSort(arr, j+1, right);
    }*/
    else{
        return;
    }
}
