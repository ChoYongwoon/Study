#include <iostream>
#include <vector>
using namespace std;
int N;
int input[1001];
int cache[1001][2];
vector<int> res;
// cache[n][0] = n을 가장 큰 수로 갖는 Lis 길이
// cache[n][1] 해당 LIS에서 이 전의 수의 index

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    for (int i = 1; i <= N; i++){ // 길이는 1로 초기화 , index는 -1로 초기화
        int tmp;
        cin >> tmp;
        input[i] = tmp;
        cache[i][0] = 1;
        cache[i][1] = -1;
    }

    for (int i = 1; i <= N; i++){
        for (int j = i-1; j >= 1; j--){
            if (input[i] > input[j]){
                int tmp = cache[j][0] + 1;
                if (cache[i][0] <= tmp){ // tmp가 더 크면
                    cache[i][0] = tmp; // tmp를 i번째 lis값으로 저장하고
                    cache[i][1] = j; // j의 index를 저장
                }
            }
        }
    }

    int max_lis = 0; int idx = -1;
    for (int i = 1; i <=N; i++){
        if(cache[i][0] > max_lis){
           max_lis = max(max_lis, cache[i][0]);
           idx = i;
        }
    }

    cout << max_lis << endl;
    int cnt = 0;

    while (cache[idx][1] != 0){ // 순회하면서 res 벡터에 값을 push
        res.push_back(input[idx]);
        idx = cache[idx][1];
        cnt++;
    }

    for(int i = cnt-1; i >= 0; i--){ // 저장된 값 출력
        cout << res[i] << " ";
    }

    return 0;
}