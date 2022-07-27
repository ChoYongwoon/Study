// Idea : 뽑는게 중요.
// 멀티탭에 꽂혀 있는 전자제품 중 가장 나중에 쓰일 전자제품을 제거
#include <iostream>
#include <set>
#include <vector>
int N; int K;
using namespace std;
set <int> multi;
vector <int> order;

int solve(){
    int res = 0;
    int idx = 0;
    while(multi.size() < N && idx < K){ // 콘센트가 다 꼽혀있을 떄 까지
        multi.insert(order[idx]);
        idx++;
    }


    for (int i = idx; i < K; i++){
        bool isIn = false;
        for(auto it = multi.begin(); it != multi.end(); it++){ // 사용하려는 제품이 꽂혀있으면 continue;
            if(*it == order[i]){
                isIn = true;
                break;
            }
        }
        if(isIn){
            continue;
        }

        set <int> tmp(multi); // multi 를 복사한 tmp 마지막 남는 원소를 찾기 위해 필요

        for (int j = i+1; j < K; j++){ // 현재 i 다음 원소부터 반복
            if (tmp.size() == 1){ // 제거되고 한 개의 원소만 남아있으면 이 것이 뽑을 콘센트
                break;
            }
            for(auto it = multi.begin(); it!=multi.end(); it++){ // multi에 같은 값이 있다면 이를 제거
                if (order[j] == *it){
                    tmp.erase(*it);
                    break;
                }
            }
        }

        multi.erase(*tmp.begin()); // tmp의 첫 값을 제거
        multi.insert(order[i]); // 현재 order을 추가

        res ++;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> K;
    
    for (int i = 0; i < K; i++){
        int tmp;
        cin >> tmp;
        order.push_back(tmp);
    }

    int res = solve();
    cout << res << endl;


    return 0;
}