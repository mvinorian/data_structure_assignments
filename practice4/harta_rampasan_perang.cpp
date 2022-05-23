#include <bits/stdc++.h>
using namespace std;

void dfs(vector<vector<int>> arr, vector<vector<bool>> visited, int r, int c, int n, bool& res){
    if(r < 0 || r >= n) return;
    if(c < 0 || c >= n) return;
    if(visited[r][c]) return;
    if(arr[r][c] == 1) return;
    if(arr[r][c] == 3){
        res = true;
        return;
    }

    visited[r][c] = true;
    dfs(arr, visited, r+1, c, n, res);
    dfs(arr, visited, r, c+1, n, res);
    dfs(arr, visited, r-1, c, n, res);
    dfs(arr, visited, r, c-1, n, res);
}

int main(){
    int n;
    cin >> n;

    int sr, sc;
    vector<vector<int>> arr(n, vector<int> (n));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> arr[i][j];
            if(arr[i][j] == 2){
                sr = i;
                sc = j;
            }
        }
    }

    bool res = false;
    vector<vector<bool>> visited(n, vector<bool> (n, 0));
    dfs(arr, visited, sr, sc, n, res);

    cout << (res ? "yey\n" : "yah\n");

    return 0;
}