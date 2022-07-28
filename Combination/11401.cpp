//11401 과 동일
#include <iostream>
using namespace std;
int N; int K;
long long MOD = 1e9+7;

long long exp_recursive(int x, int n){
    if (n == 0){return 1;}
    else if (n == 1){return x;}
    else if (n%2 == 0){
        long long res = exp_recursive(x, n/2) % MOD;
        return (res * res) % MOD;
    }
    if (n%2 == 1){
        long long res = exp_recursive(x, n-1) % MOD;
        return (res * x) % MOD;
    }
}

int main(){
    cin >> N >> K;
    long long a = 1; long long b = 1;
    for (int i = 1; i <= K; i++){
        b = b * i % MOD;
    }
    a = b;
    for (int i = K+1; i <= N; i++){
        a = a * i % MOD;
    }
    long long c = 1;
    for (int i = 1; i <= N-K; i++){
        c = c * i % MOD;
    }

    long long down = b * c % MOD;
    down = exp_recursive(down, MOD -2);
    long long res = a * down % MOD;

    cout << res << endl;
    return 0;
}