#include <iostream>
#include <vector>
using namespace std;
int n; int m;
vector<vector<char>> lab; // 방의 정보를 담을 2차원 동적배열
vector<int> loc_row; // 2번 방의 위치 (행)
vector<int> loc_col; // 2번 방의 위치 (열)
vector<int> delx = {0,1,0,-1}; // 움직일 수 있는 경우의 수
vector<int> dely = {1,0,-1,0}; // 움직일 수 있는 경우의 수

// lab에서 바이러스를 확산시키고, 이 때 0인 방의 수를 리턴
int spread(vector<vector<char>> arr, vector<int> loc_row, vector<int> loc_col, int n, int m){
    while(!loc_row.empty()){
        int row = loc_row.back(); loc_row.pop_back(); // 2번 방의 행의 마지막 값
        int col = loc_col.back(); loc_col.pop_back(); // 2번 방의 열의 마지막 값
        for (int i = 0; i<4; i++){
            int new_row = row+dely[i]; int new_col = col+delx[i]; // 주변 방의 인덱스
            if (new_row >= n || new_row <0 || new_col >= m || new_col < 0)
            {continue;} // 범위 벗어나면 다른 값으로 반복문 재개
            if (arr[new_row][new_col] == '0'){ // 주변 방이 0이면
                arr[new_row][new_col] = '2'; // 2로 전이
                //2가 되었으므로 행, 열 정보에 추가
                loc_row.push_back(new_row);
                loc_col.push_back(new_col);
            }
        }
    }
    // 전체 방에서 0의 수를 센다.
    int ret = 0;
    for (int i = 0; i<n; i++){
        for (int j = 0; j<m; j++){
            if (arr[i][j] == '0'){
                ret++;
            }
        }
    }
    return ret; // 이를 리턴
}

//lastrow 값 없이도 돌아가지만, 시간초과..
int safeArea(vector<vector<char>> arr, int n, int m, int toChange, int lastrow)
{
    // 세울 수 있는 벽이 0이면 안전한 방의 수를 세서 리턴
    if (toChange == 0) {
        return spread(arr, loc_row, loc_col, n, m); // 이를 return
    }

    int res = 0;
    for (int i =lastrow; i<n; i++){
        for(int j = 0; j<m; j++){
            if (arr[i][j] == '0'){ // 앞의 cell부터 확인하면서, 방이 비어있다면
                arr[i][j] = '1'; // 벽으로 세움
                res = max(res, safeArea(arr, n, m, toChange-1, i)); // 재귀호출 값들 중 최댓값이 res
                arr[i][j] = '0'; // 다시 벽을 없애줌
            }
        }
    }
    return res;
}

int main()
{
    cin >> n >> m;
    lab.resize(n);
    for (int i = 0; i<n; i++){
        lab[i].resize(m);
        for (int j = 0; j<m; j++){
            cin >> lab[i][j];
            if (lab[i][j] == '2')
            {
                loc_row.push_back(i);
                loc_col.push_back(j);
            }
        }
    }

    int res = safeArea(lab, n, m, 3, 0);
    cout << res << endl;
    return 0;
}
