#include <stdio.h>
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define MAX_INT 10000

int main(){
    int n, q, c, x, y, h = 1;
    scanf("%d", &n);
    while(1<<h++ < n);
    
    int t[h][1<<(h-1)];
    for(int i = 0; i < n; i++) scanf("%d", &t[h-1][i]);
    for(int i = n; i < 1<<(h-1); i++) t[h-1][i] = MAX_INT;
    for(int i = h-2; i >= 0; i--){
        for(int j = 0; j < 1<<i; j++){
            t[i][j] = min(t[i+1][2*j], t[i+1][2*j+1]);
        }
    }
    
    scanf("%d", &q);
    while(q--){
        scanf("%d %d %d", &c, &x, &y);
        if(c == 1){
            int j = x/2;
            t[h-1][x] = y;
            for(int i = h-2; i >= 0; i--){
                t[i][j] = min(t[i+1][2*j], t[i+1][2*j+1]);
                j /= 2;
            }
        }
        else if(c == 2){
            int i = h-1, m = MAX_INT;
            while(x < y){
                if(x % 2 == 1){
                    m = min(m, t[i][x]);
                    x++;
                }
                if(y % 2 == 0){
                    m = min(m, t[i][y]);
                    y--;
                }
                x /= 2;
                y /= 2;
                i--;
            }
            if(x == y) printf("%d\n", min(m, t[i][x]));
            else printf("%d\n", m);
        }
    }
    
    return 0;
}