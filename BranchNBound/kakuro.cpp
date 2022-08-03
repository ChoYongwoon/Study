// 비트마스크 이용
#include <iostream>
#include <string.h>
#include <vector>
using namespace std;
int C; int N; int Q;
int color[21][21]; int value[21][21]; int hint[21][21][2];
int sum[20*20]; int length[20*20]; int known[20*20];
int candidates[10][46][1024]; // [len][sum][known]

// mask에 속한 원소들의 개수를 반환 (책에 X)
int getSize(int mask){
    int cnt = 0;
    for (int k = 1; k <= 9; k++){
        if (mask & (1<<k)){
            cnt ++;
        }
    }
    return cnt;
}

// mask에 속한 원소들의 합을 반환 (책에 X)
int getSum(int mask){
    int sum = 0;
    for (int k = 1; k <= 9; k++){
        if (mask & (1<<k)){
            sum += k;
        }
    }
    return sum;
}

// len칸의 합이 sum이고, 이 칸에 이미 쓰인 수의 집합이 known일 때
// 나머지 칸에 들어갈 수 있는 숫자의 집합을 반환.
int getCandidates(int len, int sum, int known){
    int allSets = 0;
    // 1~9의 부분집합을 생성하고, 그 중
    for (int set = 0; set < 1024; set+=2){
        // known을 포함하고, 크기가 len이며, 합이 sum인 집합을 모두 찾는다.
        if((set & known) == known && getSize(set) == len && getSum(set) == sum){
            allSets |= set;
        }
    }
    // known에 이미 속한 숫자들을 답에서 제외
    return allSets & ~known;
}

void generateCandidates(){
    memset(candidates, 0, sizeof(candidates)); //전부 0으로 초기화
    for (int set = 0; set < 1024; set += 2){ // 1 ~ 9의 부분집합을 전부 생성한다.
        int l = getSize(set); int s = getSum(set); // 집합의 크기와 원소를 미리 계산
        int subset = set; // set의 부분집합에 대해 candidates[][][]을 갱신한다.
        while(true){
            candidates[l][s][subset] |= (set & ~subset);
            if(subset == 0) break;
            subset = (subset -1) & set; 
        }
    }
}

void put(int y, int x, int val){
    for(int h = 0; h < 2; h++){
        known[hint[y][x][h]] += (1<<val);
    }
    value[y][x] = val;
}

void remove(int y, int x, int val){
    for(int h = 0; h < 2; h++){
        known[hint[y][x][h]] -= (1<<val);
    }
    value[y][x] = 0;
}

int getCandHint(int hint){
    return candidates[length[hint]][sum[hint]][known[hint]];
}

int getCandCoord(int y, int x){
    return getCandHint(hint[y][x][0]) & getCandHint(hint[y][x][1]);
}

void printSolution(){
    for (int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << value[i][j] << " ";
        }
        cout << endl;
    }
}

bool search(){
    int y = -1; int x = -1; int minCands = 1023;
    for(int i = 0; i < N; i++){ // 아직 숫자를 쓰지 않은 흰 칸 중 후보의 수가 최소인 칸을 찾는다.
        for(int j = 0; j < N; j++){
            if(color[i][j] && value[i][j] == 0){
                int cands = getCandCoord(i,j);
                if(getSize(minCands) > getSize(cands)){
                    minCands = cands;
                    y = i; x = j;
                }
            }
        }
    }
    if(minCands == 0) return false;
    if(y == -1){
        printSolution();
        return true;
    }
    for(int val = 1; val <= 9; val++){
        if(minCands & (1<<val)){ // dfs
            put(y,x,val);
            if(search()) return true;
            remove(y,x,val);
        }
    }
    return false;
}

int main() {
    cin >> C;
    for (int k = 0; k < C; k++){
        cin >> N;
        for (int i = 0; i < N; i++){
            for (int j = 0; j < N; j++){
                cin >> color[i][j];
            }
        }
        memset(value, 0, sizeof(value));
        cin >> Q;
        for (int i = 0; i < Q; i++){ //  (책에 X)
            int y; int x; int dir;
            cin >> y >> x >> dir >> sum[i];
            hint[y-1][x-1][dir] = i;
            int cnt = 0;
            if(dir == 0){
                int tmp_y=y-1; int tmp_x = x;
                while(color[tmp_y][tmp_x]){
                    hint[tmp_y][tmp_x][dir] = i;
                    tmp_x++; cnt++;
                }
            }
            else if(dir){
                int tmp_y = y; int tmp_x = x-1;
                while(color[tmp_y][tmp_x]){
                    hint[tmp_y][tmp_x][dir] = i;
                    cnt++; tmp_y++;
                }
            }
            length[i] = cnt;
        }

        memset(known,0,sizeof(known));
        generateCandidates();
        search();
    }
    return 0;
}