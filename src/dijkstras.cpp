#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>
#include "dijkstras.h"
using namespace std;




vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous){
    int numV=G.size();
    vector<int> distance(numV,INF);     /*LOOK HERE*/
    vector<bool> visited(numV,false);
    distance[source]=0;
    previous[source]=-1;
    priority_queue<pair<int,int>> minHeap;
    minHeap.push({source,0});
    while(!minHeap.empty()){
        int u= minHeap.top().second;
        if(visited[u]){continue;}
        visited[u]=true;
        for(Edge edge:G[u]){
            int v = edge.dst;
            int weight = edge.weight;
            if(!visited[u]&&distance[u]+weight<distance[v]){
                distance[v]=distance[u]+weight;
                previous[v]= u;
                minHeap.push({v,distance[v]});
    }
    }
    }
    return distance;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination){
    vector<int> shortest_path;
    if(distances[destination]==INF)
        return shortest_path;
    if(destination!=-1)
        shortest_path.push_back(destination);
    reverse(shortest_path.begin(),shortest_path.end());
    return shortest_path;

}


void print_path(const vector<int>& v, int total){
    for(int i =0;i<v.size();i++)
        cout<<v[i]<<" ";
    cout<<endl;
    cout<<"Total cost is "<<total<<endl;



}
