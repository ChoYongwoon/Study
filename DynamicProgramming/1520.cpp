#include <iostream>
#include <vector>
using namespace std;
int map[501][501];
int count[501][501];
int row; int col;

int solve(int n, int m){
    if(n == 1 && m == 1){
        return 1;
    }

    int& res = count[n][m];
    if(res != (-1)){return res;}

    res = 0;
    if(map[n][m] < map[n-1][m]){
        res += solve(n-1, m);
    }
    if(map[n][m] < map[n][m-1]){
        res += solve(n, m-1);
    }
    if(map[n][m] < map[n+1][m]){
        res += solve(n+1, m);
    }
    if(map[n][m] < map[n][m+1]){
        res += solve(n, m+1);
    }
    return res;
}

int main(){
    ios_base::sync_with_stdio(false); 
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> row >> col;
    // 입력 받지 않은 범위는 갈 수 없게 0으로 초기화
    // 시행착오 : 단순히 생각하고 10001로 초기화했을 때 답이 틀렸음
    fill(&map[0][0], &map[500][501], 0); 
    for(int i = 1; i <= row; i++){
        for(int j = 1; j <= col; j++){
            int tmp;
            cin >> tmp;
            map[i][j] = tmp;
        }
    }
    // dp는 -1로 초기화
    fill(&count[0][0], &count[500][501], -1);

    int res = solve(row, col);
    cout << res << endl;
    return 0;
}