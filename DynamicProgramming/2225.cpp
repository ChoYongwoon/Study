#include <iostream>
using namespace std;
int N; int K;
long long ans[201][201];

// 시간초과
/*
long long count(int n, int k){ // n : 만드려는 정수, k: 이용할 정수의 수
    if(n == 0 && k == 0){
        return 1;
    }
    if(k == 0 || n == 0){
        return 0;
    }

    long long &res = ans[n];
    res = 0;
    for (int i = 1; i <= n; i++){
        res += count(n-i, k-1);
    }
    res %= 1000000000;
    return res;
}*/

int main(){
    ios_base::sync_with_stdio(false); 
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> K;
    fill(&ans[1][0],&ans[1][0]+201, 1);

    for (int i = 2; i <= K; i++){ // 사용할 정수의 개수
        for (int j = 0; j <= N; j++){ // n
            for (int num = 0; num <= j; num++){ // 채울 정수
              ans[i][j] += ans[i-1][j-num];
              ans[i][j] %= 1000000000;
            }
        }
    }
    cout << ans[K][N]<<endl;
    return 0;
}