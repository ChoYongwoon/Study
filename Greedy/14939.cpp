// 해답 참조.. 핵심 아이디어 -> 윗 줄부터 해결 (greedy..)
// 똑같은 전구를 2번 누르면 의미가 없음.
// 따라서 경우의 수 => 2^100
#include <iostream>
using namespace std;
bool space[10][10]; // 주변 스위치가 눌릴 때마다 바뀜.
bool space_cache[10][10];
int range_x[5] = {0,-1,0,1,0};
int range_y[5] = {1,0,0,0,-1};
int answer = 200;

void on_off(int y, int x){ // y, x의 스위치를 누르는 코드
    for (int i = 0; i < 5; i++){
        int tmp_y = y+range_y[i];
        int tmp_x = x+range_x[i];
        if(tmp_y < 10 && tmp_y >= 0 && tmp_x < 10 && tmp_x >= 0){
            space_cache[tmp_y][tmp_x] = !space_cache[tmp_y][tmp_x];
        }
    }
}

int check(){
    int res = 0;
    for (int y = 1; y < 10; y++){ // 윗줄부터 내려가면서 전구가 꺼진 상태로
        for(int x = 0; x < 10; x++){
            if(space_cache[y-1][x]){
                on_off(y, x);
                res++;
            }
        }
    }
    for(int c = 0; c < 10; c++){ // 맨 밑줄에 켜진 전구가 남아있다면 -1
        if(space_cache[9][c]){return 200;}
    }
    return res;
}

void solve(){
    for(int k = 0; k <1024; k++){ // 2^10 => 1024가지 경우
        for(int y = 0; y < 10; y++){
            for(int x = 0; x < 10; x++){
                space_cache[y][x] = space[y][x];
            }
        }
        int tmp = 0;
        for(int x = 0; x < 10; x++){
            if(k & (1 << x)){ // 1024개의 모든 경우를 만드는 부분(미트마스크)
                tmp++;
                on_off(0,x);
            }
        }
        tmp+=check();
        if(tmp < answer){answer = tmp;}
    }
    return;
}


int main(){
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            char tmp;
            cin >> tmp;
            space[i][j] = tmp == '#'? false : true; // #이면 0, O면 1
        }
    }
    solve();
    answer = answer >= 200? -1: answer;
    cout << answer << endl;
    return 0;
}