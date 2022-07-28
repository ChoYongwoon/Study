#include <iostream>
#include <algorithm>
using namespace std;
int N; int M; long long K;
long long INF = 1e9;
string answer;
long long combination[401][201];

// 문자열의 개수 = (N+M) C N
// 1번 째가 a로 시작하는 문자열 개수 = (N+M-1) C M
long long comb(int n , int r){
    if (n == r || r == 0){return 1;}
    if (n-r == 1){return n;}
    long long &res = combination[n][r];
    if(res != -1){return res;}
    res = comb(n-1, r-1) + comb(n-1, r);
    if(res > INF){res = INF;}
    return res;
}

void solve(int n, int m, long long k){
    long long cnt = comb(n + m - 1, m);
    if (n > 0 && cnt >= k){
        answer += 'a';
        solve(n-1, m, k);
    }
    else if (m > 0){
        k -= cnt;
        answer += 'z';
        solve(n, m-1, k);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> M >> K;
    fill(&combination[0][0], &combination[200][201], -1);
    
    if (comb(N+M, N) < K){
        cout << -1;
        return 0;
    }

    solve(N, M, K);
    cout << answer << endl;

    return 0;
}