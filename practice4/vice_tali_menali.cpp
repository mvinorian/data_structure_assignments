#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;

    unsigned long long arr[36];
    arr[0] = arr[1] = 1;
    for(int i = 2; i < 36; i++){
        arr[i] = 0;
        for(int j = 0; j < i; j++){
            arr[i] += arr[j]*arr[i-j-1];
        }
    }

    while(t--){
        int n;
        cin >> n;
        assert(n >= 0 && n <= 35);
        cout << (n == 0 ? 0 : arr[n]) << '\n';
    }

    return 0;
}