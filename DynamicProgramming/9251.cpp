#include <iostream>
#include <algorithm>
using namespace std;
string A; string B;
int cache[1001][1001];

int LCS(int n, int m){
    bool same = A[n-1] == B[m-1];
    
    if (n==1){
        for (int i = 0; i < m; i ++){
            if(A[0] == B[i]){
                return 1;
        }}
        return 0;
    }
    if (m==1){
        for (int i = 0; i < n; i ++){
            if(A[i] == B[0]){
                return 1;
            }}
        return 0;
    }

    int &ret = cache[n][m];

    if(ret != (-1)){return ret;}
    
    if (same) {
        ret = 1 + LCS(n-1, m-1);
    }
    else{
        ret = max(LCS(n-1, m), LCS(n, m-1));
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> A >> B;
    fill(&cache[0][0], &cache[1000][1001], -1);
    int ans = LCS(A.size(), B.size());
    cout << ans << endl;
    return 0;
}