#include <bits/stdc++.h>
using namespace std;

void solve(){
    int n, m;
    cin >> n >> m;

    vector<string> arr(n);
    for(int i = 0; i < n; i++) cin >> arr[i];

    vector<vector<char>> res(n, vector<char> (m, '.'));
    for(int j = 0; j < m; j++){
        int count = 0;
        for(int i = 0; i < n; i++){
            if(arr[i][j] == '.') continue;
            if(arr[i][j] == '*') count++;
            else{
                res[i][j] = 'o';
                while(count--){
                    res[i-count-1][j] = '*';
                }
                count = 0;
            }
        }
        while(count--){
            res[n-count-1][j] = '*';
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++) cout << res[i][j];
        cout << '\n';
    }
}

int main(){
    int t;
    cin >> t;
    while(t--) solve();

    return 0;
}