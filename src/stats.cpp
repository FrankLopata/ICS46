
#include <cmath>
using namespace std;
#include "stats.h"


void Stats::set_all_numerics(const vector<int> v){
    for(int i = 0;i<v.size();i++){
        if(v[i]>max)
            max = v[i];
        if(v[i]<min)
            min = v[i];
        entries += v[i];
        chains++;
    }
    span = max - min;
    mean = entries / chains;
    load_factor = chains / entries;
    stddev = sqrt(pow(entries-mean,2)/chains);
}

