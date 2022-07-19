#include <iostream>
#include <algorithm>
using namespace std;
int N;
int bamboo[502][502]; // 대나무 개수를 저장할 배열
int cache[502][502]; // dp
int delx[4] = {0, 1, 0, -1}; // 이동 방향
int dely[4] = {1, 0, -1, 0};

int count_max(int n, int m){
    int &res = cache[n][m];
    if (res != -1){return res;} // 이미 값이 구해졌다면 이를 리턴
    res = 1;
    for(int i = 0; i < 4; i++){ // 네 방향 중 max(대나무가 더 많은 곳 + 1)
        if (bamboo[n][m] < bamboo[n+dely[i]][m+delx[i]]){
            res = max(res, count_max(n+dely[i], m+delx[i])+1);
        }
    }

    return res;
};

int main(){
    ios_base::sync_with_stdio(false);

    fill(&bamboo[0][0], &bamboo[501][502], -1);

    cin >> N;
    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= N; j++){
            cin >> bamboo[i][j];
        }
    }
    fill(&cache[0][0], &cache[501][502], -1);

    int res = 0;
    for (int i = 1; i<= N; i++){
        for (int j = 1; j<=N; j++){
            res = max(res, count_max(i, j)); 
        }
    }
    cout << res << endl;
}