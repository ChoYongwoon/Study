#include <iostream>
#include <vector>
#include <algorithm>
#define INF 100000000
using namespace std;
int T; int N;
int file[501];
int sum[501];
int cache[501][501]; // n번째 부터 m 번째까지 더할 때 최소 비용

void input(){
    cin >> N;
    
    for(int i = 1; i <= N; i++){
        cin >> file[i];
        sum[i] = sum[i-1] + file[i];
    }
}

int min_cost(int n, int m){
    if (m==n){return 0;} // file[m]으로 리턴하게되면 안됨.
    // 2개와 1개를 더할 때 -> 2개의 min + 총합
    // file [m] 으로 하면 2개의 min + file[m] + 총합이 되서 답이 틀림.
    if ((m-n)==1){return file[m]+file[n];}
    
    int &res = cache[n][m];
    if (res != -1) {return res;}
    
    res = INF;
    for (int i = n; i < m; i++){
        int tmp = min_cost(n,i) + min_cost(i+1,m) + sum[m]-sum[n-1];
        res = min(res, tmp);
    }

    return res;
}


int main(){
    cin >> T;
    ios_base::sync_with_stdio(false);
    for (int it = 0; it<T; it++){
        input();
        fill(&cache[0][0], &cache[500][501], -1);

        int res = min_cost(1, N);
        cout << res << endl;
    }
    return 0;
}