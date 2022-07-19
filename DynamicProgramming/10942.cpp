#include <iostream>
#include <algorithm>
using namespace std;
int arr[2001];
int cache[2001][2001];
int N; int M;

int pelindrom(int n, int m){
    if (m == n){return 1;}
    if (m-n == 1){
        if (arr[n] == arr[m]){return 1;}
        return 0;
    }
    int &res = cache[n][m];
    if (res != -1){return res;}

    res = 0;
    if (arr[n] == arr[m]){
        res = pelindrom(n+1, m-1);
    }
    return res;
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> N;
    for (int i = 1; i <= N; i++){
        cin >> arr[i];
    }
    fill(&cache[0][0], &cache[2000][2001], -1);

    cin >> M;
    for (int i = 0; i < M; i++){
        int start; int end;
        cin >> start >> end;
        int res = pelindrom(start, end);
        cout << res << '\n';
    }
    return 0;
}