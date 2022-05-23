#include <bits/stdc++.h>
using namespace std;

vector<string> neighbour(string str){
    vector<string> res;
    string tmp = str;
    int nr = 0, nc = 0;
    for(int i = 0; i < 9; i++){
        if(str[i] == '0'){
            nr = i/3;
            nc = i-3*(i/3);
        }
    }
    if(nr-1 >= 0){
        swap(tmp[3*nr+nc], tmp[3*(nr-1)+nc]);
        res.push_back(tmp);
        swap(tmp[3*nr+nc], tmp[3*(nr-1)+nc]);
    }
    if(nr+1 < 3){
        swap(tmp[3*nr+nc], tmp[3*(nr+1)+nc]);
        res.push_back(tmp);
        swap(tmp[3*nr+nc], tmp[3*(nr+1)+nc]);
    }
    if(nc+1 < 3){
        swap(tmp[3*nr+nc], tmp[3*nr+(nc+1)]);
        res.push_back(tmp);
        swap(tmp[3*nr+nc], tmp[3*nr+(nc+1)]);
    }
    if(nc-1 >= 0){
        swap(tmp[3*nr+nc], tmp[3*nr+(nc-1)]);
        res.push_back(tmp);
        swap(tmp[3*nr+nc], tmp[3*nr+(nc-1)]);
    }

    return res;
}

int manhattan(string str){
    int res = 0;
    vector<vector<int>> pos = {
        {0, 0}, {0, 1}, {0, 2},
        {1, 0}, {1, 1}, {1, 2},
        {2, 0}, {2, 1}
    };
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; i++){
            res += abs(pos[str[3*i+j]-'0'-1][0]-i) + abs(pos[str[3*i+j]-'0'-1][1]-j);
        }
    }
    return res;
}

void print(map<string, string> prev, string cur){
    if(cur == prev[cur]) return;
    print(prev, prev[cur]);
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++) cout << cur[3*i+j];
        cout << '\n';
    }
    if(cur != "123456780") cout << '\n';
}

bool solve(){
    string str = "";
    for(int i = 0; i < 3; i++){
        char tmp[4];
        if(i == 0 && scanf("%s", tmp) == EOF) return false;
        if(i != 0) scanf("%s", tmp);
        str += tmp;
    }

    int inversion = 0;
    for(int i = 1; i < 9; i++){
        if(str[i] == '0') continue;
        for(int j = i-1; j >= 0; j--){
            if(str[j] == '0') continue;
            if(str[i] < str[j]) inversion++;
        }
    }
    if(inversion & 1){
        cout << "Kerjain dl aja kerjaannya\n";
        return true;
    }

    map<string, int> move;
    map<string, string> prev;
    map<string, bool> visited;
    priority_queue<pair<int, string>> pq;
    pq.push(make_pair(-manhattan(str), str));
    move[str] = 0;
    prev[str] = str;
    visited[str] = true;

    string goal = "123456780";
    while(!pq.empty()){
        pair<int, string> cur = pq.top();
        pq.pop();

        if(cur.second == goal) break;
        for(string next : neighbour(cur.second)){
            if(visited[next]) continue;
            if(next == prev[cur.second]) continue;
            visited[next] = true;
            prev[next] = cur.second;
            move[next] = move[cur.second]+1;
            pq.push(make_pair(-(manhattan(next)+move[next]), next));
        }
    }

    cout << "Langkah minimum = " << move[goal] << '\n';
    print(prev, goal);

    return true;
}

int main(){
    while(solve());

    return 0;
}