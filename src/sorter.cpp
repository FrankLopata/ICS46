#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
#include "sorter.h"
#include "timer.h"



void Sorter::fill(int count, string file_name){
    vec.reserve(count);
    vec.clear();
    ifstream in(file_name);
    int i = 0;
    for(string word;(in>>word)&&i<count;i++){
        vec.push_back(word);
    }
    in.close();
}

void Sorter::print(ostream & out){
    for(auto word:vec){
        out<<word<<" ";
    }
}


bool Sorter::verify_sorted(){
    int size = vec.size()-1;
    for(int i = 0;i<size;i++){
        if(vec[i]>vec[i+1])
            return false;
    }
    return true;

}





void InsertionSorter::insertionsort(vector<string>& vec, int low, int high){
    for (int index=1; index<vec.size(); index++) {
        string currentvalue = vec[index];
        int position = index;
        while (position>0 && vec[position-1]>currentvalue) {
            vec[position] = vec[position-1];
            position--;
        }

        vec[position] = currentvalue;
    }

}

void InsertionSorter::sort(){
    insertionsort(vec,0,vec.size()-1);

}




string QuickSorter::select_pivot(vector<string>& vec, int low, int high){
    int mid = (low + high) / 2;
    if ( vec[mid] < vec[low] ) 
        swap( vec[low], vec[mid] );
    if ( vec[high] < vec[low] ) 
        swap( vec[low], vec[high] );
    if ( vec[mid] < vec[high] ) 
        swap( vec[mid], vec [high] );
    return vec[high];

}

int QuickSorter::partition(vector<string>& vec, int low, int high)
{
    string pivot = select_pivot(vec, low, high);

    for (int j = low; j < high; j++) {
        if (vec[j] <= pivot) {
            swap(vec[low], vec[j]);
            ++low;
        }
    }

    swap(vec[low], vec[high]);
    return low;
}




void QuickSorter::quicksort(vector<string>& vec, int low, int high){
        if ( low < high ){
         int pivot_index = partition( vec, low, high );
         quicksort( vec, low, pivot_index-1 );
         quicksort( vec, pivot_index+1, high );
    }
}
void QuickSorter::sort() {
    quicksort(vec,0,vec.size()-1);

}



void IntroSorter::introsort_util(vector<string>& arr, int low, int high, int depth_limit) {
    if (high - low < 11) {
        InsertionSorter::insertionsort(arr, low, high);
        return;
    }
    if (depth_limit == 0) {
        HeapSorter::heapsort(arr, low, high);
 return;
    }
    int p = QuickSorter::partition(arr, low, high);
    introsort_util(arr, low, p - 1, depth_limit - 1);
    introsort_util(arr, p + 1, high, depth_limit - 1);
}

void IntroSorter::introsort(vector<string>& avec, int low, int high){
    int depth_limit = 2 * log(high - low);
    introsort_util(avec, low, high, depth_limit);
}
void IntroSorter::sort(){
    introsort(vec,0,vec.size()-1);
}


void STLSorter::sort(){
    std::ranges::sort(vec);
}

void StableSorter::sort(){
    std::stable_sort(vec.begin(),vec.end());
}

void ShellSorter::gapInsertionSort(vector<string> & avector, int start, int gap){
    for (unsigned int i = start + gap; i < avector.size(); i += gap) {
        string currentvalue = avector[i];
        int position = i;

        while (position >= gap && avector[position - gap] > currentvalue) {
            avector[position] = avector[position - gap];
            position -= gap;
        }
        avector[position] = currentvalue;
    }


}
void ShellSorter::shellSort(vector<string> & avector){
   int subvectorcount = avector.size() / 2;
    while (subvectorcount > 0) {
        for (int startposition = 0; startposition < subvectorcount;
             startposition++) {
            gapInsertionSort(avector, startposition, subvectorcount);

        subvectorcount = subvectorcount / 2; 
        }
    }

}
void ShellSorter::sort(){
    shellSort(vec);

}

void HeapSorter::heapify(vector<string>& vec, int high, int root){
    int largest = root;
    int left = 2 * root + 1; 
    int right = 2 * root + 2;  
    if (left <= high && vec[left] > vec[largest])
        largest = left;
    if (right <= high && vec[right] > vec[largest])
        largest = right;
    if (largest != root) {
        swap(vec[root], vec[largest]);
        heapify(vec, high, largest);
    }


}

void HeapSorter::heapsort(vector<string>& vec, int low, int high){
    for(int i = low + (high-low)/2 - 1;i>=low;i--)
        heapify(vec,high,i);
    for(int i = high - 1; i >=low;i--){
        swap(vec[low],vec[i]);
        heapify(vec,i,low);
    }
}

void HeapSorter::sort(){
    heapsort(vec,0,vec.size()-1);
}
void error(string word, string msg) {
    cout << word << msg << endl;
}
ostream & operator << (ostream & out, Sorter & L)
{
    L.print(out);
    return out;
}
void measure_partition(int k, string file_name, Sorter & L)
{
    Timer t;
    double eTime;
    ifstream in(file_name);
    L.fill(k * NWORDS/10, file_name);
    t.start();
    L.sort();
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tI = " << eTime << endl;
    if(!L.verify_sorted())
    {
        error(L.name, "is not fully sorted");
    }
}
void measure_partitions(string file_name, Sorter & L)
{
    cout << L.name << endl;;
    for(int k = 1; k <= 10; ++k)
    {
        measure_partition(k, file_name, L);
        // cout << L;
        // cout << endl;
    }
}
void measure_sorters(string input_file)
{
    //InsertionSorter insert_sort;
    //measure_partitions(input_file, insert_sort);

    //QuickSorter quick_sort;
   // measure_partitions(input_file, quick_sort);

    HeapSorter heap_sort;
    measure_partitions(input_file, heap_sort);

    // IntroSorter intro_sort;
    // measure_partitions(input_file, intro_sort);

    STLSorter stl_sort;
    measure_partitions(input_file, stl_sort);

    StableSorter stable_sort;
    measure_partitions(input_file, stable_sort);

    //ShellSorter shell_sort;
    //measure_partitions(input_file, shell_sort);
}
