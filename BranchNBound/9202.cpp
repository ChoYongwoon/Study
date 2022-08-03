#include <iostream>
#include <vector>
#include <set>
#include <string>
using namespace std;
int W; int B; 
set<string> words;
vector<int> score = {0,0,0,1,1,2,3,5,11}; // 단어 길이 별 점수
set<string> finded; // 찾은 문자열 (사전순 조건을 충족시키기 위해서 set을 사용)
char boggle[6][6]; // 문자가 들어갈 배열
bool isVisited[6][6]; // 밟았던 칸인지 확인할 배열 => edge case
int dx[8] = {-1,-1,-1,1,1,1,0,0};
int dy[8] = {-1,0,1,-1,0,1,-1,1};

bool hasWord(int row, int col, const string& word){
    if (boggle[row][col] == '0') return false; // range를 벗어났을 경우 false
    if (boggle[row][col] != word[0]) return false; // 첫 단어가 다를 경우 false
    if (word.size() == 1) return true; // 성공한 case
    for (int direction = 0; direction < 8; direction++){
        int nextY = row + dy[direction];
        int nextX = col + dx[direction];
        if(!isVisited[nextY][nextX]){
            isVisited[nextY][nextX] = true;
            bool isIN = hasWord(nextY, nextX, word.substr(1)); // 각 방향에 대해 확인
            isVisited[nextY][nextX] = false;
            if(isIN){
                return true;
            }
        }
    }
    return false;
}

int solve(set<string> words){
    int res = 0;
    // 각 단어에 대해
    for(set<string>::iterator it = words.begin(); it != words.end(); it++){
        bool check = false; // 찾았을 때 반복문을 종료시키기 위한 변수
        string word = *it;
        // 모든 칸에서 시작하는 경우가 있는지 check
        for (int i = 1; i <= 4; i++){
            for (int j = 1; j <= 4; j++){
                isVisited[i][j] = true;
                check = hasWord(i, j, word); // i, j 로 시작하는 word가 가능한지 check
                isVisited[i][j] = false;
                if(check){
                    break;
                }
            }
            if(check){break;}
        }
        if(check){ // 해당 단어가 존재할 수 있으면
            finded.insert(word); // finded에 원소를 추가
            res += score[word.length()]; // 총 score 합산
        }
    }
    return res;
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> W;
    for (int i = 0; i < W; i++){ // 길이 3이상인 단어만 저장
        string tmp;
        cin >> tmp;
        words.insert(tmp);
    }

    fill(&boggle[0][0], &boggle[6][6], '0');
    fill(&isVisited[0][0], &isVisited[5][6], false);
    cin >> B;

    for(int i = 0; i < B; i++){
        for (int j = 1; j < 5; j++){ // Boggle 채우기, 겉에 한칸씩 몰딩
            for(int k = 1; k < 5; k++){
                cin >> boggle[j][k];
            }
        }
        finded.clear();
        int res = solve(words);
        string Longest = ""; int longest_size = 0;
        for(set<string>::iterator it = finded.begin(); it!=finded.end(); it++){
            string tmp = *it;
            if(longest_size < tmp.length()){
                Longest = tmp;
                longest_size = tmp.length();
            }
        }
        cout << res << " " << Longest << " " << finded.size() << endl;
    }
    return 0;
}