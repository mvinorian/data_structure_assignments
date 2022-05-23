#include <bits/stdc++.h>
using namespace std;

void dfs(vector<int>* adj, bool* visited, int node){
    if(visited[node]) return;
    visited[node] = true;
    for(int i : adj[node]) dfs(adj, visited, i);
}

int main(){
    int n, e;
    cin >> n >> e;
    
    int s, d;
    vector<int> adj[n+1];
    while(e--){
        cin >> s >> d;
        adj[s].push_back(d);
        adj[d].push_back(s);
    }
    
    bool visited[n+1];
    memset(visited, 0, sizeof(visited));
    
    int sum = 0;
    for(int i = 1; i <= n; i++){
        if(visited[i]) continue;
        dfs(adj, visited, i);
        sum++;
    }
    
    cout << sum-1 << '\n';
    
    return 0;
}