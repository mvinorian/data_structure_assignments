// https://www.baeldung.com/cs/graph-number-of-shortest-paths
#include <bits/stdc++.h>
#define INF (int)(2e+9)
using namespace std;

void bfs(vector<int>* adj, bool* visited, vector<int>& dst, vector<int>& cnt, int node){
    queue<int> q;
    q.push(node);

    visited[node] = true;
    dst[node] = 0;
    cnt[node] = 1;

    while(!q.empty()){
        int cur = q.front();
        q.pop();
        
        for(int i : adj[cur]){
            if(!visited[i]){
                q.push(i);
                visited[i] = true;
            }
            if(dst[cur]+1 < dst[i]){
                dst[i] = dst[cur]+1;
                cnt[i] = cnt[cur];
            }else if(dst[cur]+1 == dst[i]) cnt[i] += cnt[cur];
        }
    }
}

int main(){
    int n, e, ns, nd;
    cin >> n >> e >> ns >> nd;

    int s, d, c;
    vector<int> adj[n+1];
    while(e--){
        cin >> s >> d >> c;
        adj[s].push_back(d);
        adj[d].push_back(s);
    }

    bool svisited[n+1], dvisited[n+1];
    memset(svisited, 0, sizeof(svisited));
    memset(dvisited, 0, sizeof(dvisited));
    vector<int> sdst(n+1, INF), ddst(n+1, INF),
                scnt(n+1, 0), dcnt(n+1, 0);
    bfs(adj, svisited, sdst, scnt, ns);
    bfs(adj, dvisited, ddst, dcnt, nd);

    for(int i = 1; i <= n; i++){
        double res;
        if(sdst[i]+ddst[i] != sdst[nd]) res = 0;
        else res = 2*(double)(scnt[i]*dcnt[i])/(double)scnt[nd];
        printf("%0.8lf\n", res);
    }

    return 0;
}