#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>
using namespace std;
#include "graph.h"

DisjointSet::DisjointSet(int numVertices){
    subsets.resize(numVertices);
    for(int i = 0; i<numVertices;++i){
        makeSet(i);
    }

}
    
void DisjointSet::makeSet(Vertex x){
    subsets[x].parent=x;

}
    
Vertex DisjointSet::findSet(Vertex x){
     Vertex & parent = subsets[x].parent;
    if (parent != x)
       parent = findSet(parent);
    return parent;
    }
    
void DisjointSet::unionSets(Vertex x, Vertex y){
    Vertex xroot = findSet(x);
    Vertex yroot = findSet(y);
    subsets[yroot].parent = xroot;

}



Graph Graph::sort_edges() const{
    Graph sortedGraph = *this;

    std::sort(sortedGraph.begin(), sortedGraph.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });

    return sortedGraph;

}

VertexList Graph::edges_from(Vertex vertex) const{
    VertexList Vertexes;
    for(const Edge& e:*this){
        if(e.u == vertex)
            Vertexes.push_back(e.v);
        else if(e.v == vertex)
            Vertexes.push_back(e.u);
    }
    return Vertexes;


}

EdgeList Kruskals(const Graph& G){
    EdgeList elist;
    size_t siz = G.numVertices-1;
    const Graph& sortedge = G.sort_edges();
    DisjointSet DS{G.numVertices};
    for (const Edge& e : sortedge){
        Vertex U = DS.findSet(e.u);
        Vertex V = DS.findSet(e.v);

        if(U != V){
            DS.unionSets(U, V);
            elist.push_back(e);
            if(elist.size() >= siz) 
                break;
        }
    }
    return elist;
}

void error(string msg) {
    cout<< msg << endl;
}

int sum_weights(EdgeList const& L){
    int sum = 0;
    for(const Edge& e:L){
        sum+=e.weight;
    }
    return sum;
}

void file_to_graph(string filename, Graph & G){
    ifstream in(filename);
    in>>G;
    in.close();
}

VertexList bfs(const Graph& graph, Vertex startVertex){
  queue<Vertex> que;
  VertexList v;

  v.push_back(startVertex);
  que.push(startVertex);

  for(;!que.empty();)
  {
    VertexList x = graph.edges_from(que.front());
    for(Vertex e: x){
        if(find(v.begin(),v.end(),e)==v.end())
            {
            v.push_back(e);
            que.push(e);
            }

    }
    que.pop();

  }
  return v;
}

VertexList dfs(const Graph& graph, Vertex startVertex){

    VertexList  result;
    vector<bool> visited(graph.size(), false);
    queue<Vertex> queue;
    visited[startVertex] = true;
    queue.push(startVertex);

    while (!queue.empty()) {
        Vertex vertex = queue.front();
        queue.pop();
        result.push_back(vertex);
        for (Vertex v : graph.edges_from(vertex))
            if (!visited[v]) {
                visited[v] = true;
                queue.push(v);
            }
    }
    return result;

}

string get_arg(int argc, char *argv[], string def){
    if (argc == 2)
        return string(argv[1]);
    else
        return def;

}
