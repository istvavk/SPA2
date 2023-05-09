#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <algorithm>
using namespace std;

class Graph
{
private:
    vector<vector<int>> AMatrix;

    int totalWeightOfGraph(vector<vector<int>> adjMatrix){
        int suma=0;
        for (int i = 0; i < adjMatrix.size(); i++) {
            for (int j = 0; j < adjMatrix.size(); j++) {
                if (AMatrix[i][j] !=0)
                    suma+=AMatrix[i][j];
            }
        }
        return suma/2;
    }

    void printGraph(vector<vector<int>> adjMatrix){

        for (int i = 0; i < adjMatrix.size(); i++) {
            for (int j = 0; j < i; j++) {
                if (AMatrix[i][j] !=0)
                    cout <<i<<" - "<<j<<" ("<<AMatrix[i][j]<<")"<<endl;
            }
        }
    }

    int find (vector<int>& parent, int u){
        if(parent[u] == -1){
            return u;
        }
        return find(parent, parent[u]);
    }

    void union_sets (vector<int>& parent, int u, int v){
        int root_u = find(parent, u);
        int root_v = find(parent, v);
        parent[root_u] = root_v;
    }

public:
    
    Graph(vector<vector<int>> adjMatrix){
            AMatrix=adjMatrix;
    }

    int GraphWeight(){
        return totalWeightOfGraph(AMatrix);
    }

    void print(){
        printGraph(AMatrix);
    }

    void primMST(Graph G){
        int V = AMatrix.size();
        vector<bool> inMST(V, false);
        vector<int> weights(V, INT_MAX);
        vector<int> parent(V, -1);

        auto cmp = [](pair<int, int>& a, pair<int, int>& b) -> bool {
            return a.second > b.second;
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);

        pq.push(make_pair(0, 0));
        weights[0] = 0;

        while (!pq.empty()) {
            int u = pq.top().first;
            pq.pop();

            inMST[u] = true;

            for (int v = 0; v < V; ++v) {
                if (AMatrix[u][v] != 0 && inMST[v] == false && AMatrix[u][v] < weights[v]) {
                    weights[v] = AMatrix[u][v];
                    pq.push(make_pair(v, weights[v]));
                    parent[v] = u;
                }
            }
        }

        int mst_weight = 0;

        for(int i = 1; i < V; i++){
            cout << parent[i] << " - " << i << " (" << AMatrix[i][parent[i]] << ")" << endl;
            mst_weight += AMatrix[i][parent[i]];
        }

        cout << "Tezina primMST-a: " << mst_weight << endl;
    }

  
    void kruskalMST(Graph G){
        int V = G.AMatrix.size();
        vector<int> parent(V, -1);
        vector<pair<int, pair<int, int>>> edges;

        // Stvaranje vektora bridova
        for(int i = 0; i < V; i++){
            for(int j = 0; j < V; j++){
                if(G.AMatrix[i][j] != 0){
                    edges.push_back(make_pair(G.AMatrix[i][j], make_pair(i, j)));
                }
            }
            
        sort(edges.begin(), edges.end());

        int mst_weight = 0;

        for(auto edge : edges){
            int weight = edge.first;
            int u = edge.second.first;
            int v = edge.second.second;

            int set_u = find(parent, u);
            int set_v = find(parent, v);

            if(set_u != set_v){
                cout << u << " - " << v << " (" << weight << ")" << endl;
                mst_weight += weight;
                union_sets(parent, set_u, set_v);
            }
        }

        cout << "Tezina kruskalMST-a: " << mst_weight << endl;
    }


};

int main(){
    ifstream input("inputgraph.txt");
    int cvorovi, bridovi;
    input >> cvorovi >> bridovi;
    vector<vector<int>> matrica(bridovi, vector<int>(3));
    for (int i = 0; i < bridovi; i++) {
        for (int j = 0; j < 3; j++) {
            input >> matrica[i][j];
        }
    }
    input.close();
    
    vector<vector<int>> adjMatrix (cvorovi,vector<int>((cvorovi),0));
    for (int i = 0; i < bridovi; i++) {
        adjMatrix[matrica[i][0]][matrica[i][1]] =matrica[i][2];
        adjMatrix[matrica[i][1]][matrica[i][0]] =matrica[i][2];
    }

    
    Graph grafit (adjMatrix);
    grafit.print();
    cout<<"Tezina grafa: "<<grafit.GraphWeight()<<endl;
    cout<<endl;


    grafit.primMST(grafit);
    cout<<endl;
    grafit.kruskalMST(grafit);

    return 0;
}

