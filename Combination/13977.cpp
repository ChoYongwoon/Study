// N combination K %= 1,000,000,007
// 소수로 준 이유 -> 페르마 소정리를 사용 
// (a/b)%M 에서 b와 M이 서로소일 때만 곱셈 역원이 존재
// (a/b)%M = (a/modInv(b,M))%M
// modInv(b,M) = b^(M-2)%M
// 알고리즘 해결전략 1권 514p 참조.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const long long MOD = 1000000007;
long long cache[4000001];
int M; 

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

	cache[0] = 1;
	for (int i = 1; i < 4000001; i++){
        cache[i] = cache[i-1] * i % MOD;
    }

    cin >> M;

    for (int i = 0; i < M; i++){
        long long N; long long K;
        cin >> N >> K;
        
        long long a = cache[N];
        long long b = (cache[K]*cache[N-K]) % MOD;
        b = exp_recursive(b, MOD-2) % MOD;
        cout << (a*b) % MOD << '\n';

    }

    return 0;
}