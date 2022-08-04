// 비트마스크 이용
#include <iostream>
#include <string.h>
#include <vector>
using namespace std;
int C; int N; int Q; // C:반복횟수, N:보드판의 크기, Q:힌트의 수
int color[21][21]; // Block이 hint가 들어갈 cell인지 value가 들어갈 cell인지 저장하는 2중 배열
int value[21][21]; // value가 들어갈 cell에 들어갈 값을 저장할 배열
int hint[21][21][2]; // 각 cell에 해당하는 힌트의 번호를 저장할 배열 [y][x][0] : 가로힌트 번호 [y][x][1] : 세로힌트 번호
int sum[20*20]; // i:힌트 번호, sum[i]:i번째 힌트의 합
int length[20*20]; // i:힌트 번호, length[i]:i번째 힌트가 해당되는 cell의 수
int known[20*20]; // i:힌트 번호, known[i]:i번째 힌트에 이미 속한 원소의 부분집합(비트마스크)
int candidates[10][46][1024]; // [len][sum][known] 미리 len, sum, known에 대한 정보를 알 때 후보군이 담긴 배열(비트마스크)

// mask에 속한 원소들의 개수를 반환 (책에 X)
int getSize(int mask){
    int cnt = 0;
    for (int k = 1; k <= 9; k++){
        if (mask & (1<<k)){ // 원소 k가 있는지 확인
            cnt ++;
        }
    }
    return cnt;
}

// mask에 속한 원소들의 합을 반환 (책에 X)
int getSum(int mask){
    int sum = 0;
    for (int k = 1; k <= 9; k++){
        if (mask & (1<<k)){ // 원소 k가 있는지 확인
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

// 모든 경우에 대한 후보군을 candidates 배열에 저장(dp)
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

// y,x에 value 값을  넣어주는 메소드 (for dfs)
void put(int y, int x, int val){
    for(int h = 0; h < 2; h++){
        known[hint[y][x][h]] += (1<<val);
    }
    value[y][x] = val;
}

// y,x에 value 값을 삭제하는 메소드 (for dfs)
void remove(int y, int x, int val){
    for(int h = 0; h < 2; h++){
        known[hint[y][x][h]] -= (1<<val);
    }
    value[y][x] = 0;
}

// hint 번호에 대한 후보군을 비트마스크로 리턴하는 메소드
int getCandHint(int hint){
    return candidates[length[hint]][sum[hint]][known[hint]];
}

// 가로, 세로 힌트의 후보군의 교집합을 비트마스크로 리턴
int getCandCoord(int y, int x){
    return getCandHint(hint[y][x][0]) & getCandHint(hint[y][x][1]);
}

// 정답(value 배열)을 print 하는 메소드
void printSolution(){
    for (int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << value[i][j] << " ";
        }
        cout << endl;
    }
}

// 최종 동작시키는 메소드
bool search(){
    int y = -1; int x = -1; int minCands = 1023;
    for(int i = 0; i < N; i++){ // 아직 숫자를 쓰지 않은 흰 칸 중 후보의 수가 최소인 칸을 찾는다.
        for(int j = 0; j < N; j++){
            if(color[i][j] && value[i][j] == 0){
                int cands = getCandCoord(i,j); // i,j의 가능한 후보군
                if(getSize(minCands) > getSize(cands)){ // 가능한 후보의 개수가 기존의 개수보다 더 작다면
                    minCands = cands; // 최소 후보의 개수 저장
                    y = i; x = j; // 좌표 저장
                }
            }
        }
    }
    if(minCands == 0) return false; // 들어갈 수 있는 후보가 없다면, false를 리턴
    if(y == -1){ // 번호가 쓰이지 않은 cell이 없다면 => solution을 찾음!
        printSolution(); // solution print
        return true; // true를 리턴
    }
    for(int val = 1; val <= 9; val++){
        if(minCands & (1<<val)){ // dfs
            put(y,x,val); // 최소 후보군 수의 좌표에 val을 넣어보고
            if(search()) return true; // 재귀적으로 수행
            remove(y,x,val); // val을 제거후 반복문 다시 수행
        }
    }
    return false;
}

int main() {
    cin >> C;
    for (int k = 0; k < C; k++){ 
        cin >> N;
        for (int i = 0; i < N; i++){ // color 배열에 input
            for (int j = 0; j < N; j++){
                cin >> color[i][j];
            }
        }
        memset(value, 0, sizeof(value)); // value 배열을 0으로 초기화
        cin >> Q;
        for (int i = 0; i < Q; i++){ //  (책에 X)
            int y; int x; int dir;
            cin >> y >> x >> dir >> sum[i]; // y, x, 방향, sum값을 input
            hint[y-1][x-1][dir] = i; // 해당 cell의 힌트 번호를 저장
            int cnt = 0; 
            if(dir == 0){ // 가로 방향일 경우
                int tmp_y=y-1; int tmp_x = x; // 인덱싱 용도의 변수
                while(color[tmp_y][tmp_x]){ // value가 들어갈 수 있는 cell인 경우
                    hint[tmp_y][tmp_x][dir] = i; // hint가 유호한 cell에 번호 모두 기입
                    tmp_x++; cnt++; // 한칸씩 오른쪽으로 이동, 개수++
                }
            }
            else if(dir){ // 세로 방향일 경우
                int tmp_y = y; int tmp_x = x-1; // 인덱싱 용도의 변수
                while(color[tmp_y][tmp_x]){ // value가 들어갈 수 있는 cell인 경우
                    hint[tmp_y][tmp_x][dir] = i; // hint가 유효한 cell에 번호 모두 기입
                    cnt++; tmp_y++; // 한칸씩 아래로 이동, 개수++
                }
            }
            length[i] = cnt; // length 배열에 개수 기입
        }

        memset(known,0,sizeof(known));
        generateCandidates(); // dp 배열 미리 생성
        search(); // solve
    }
    return 0;
}