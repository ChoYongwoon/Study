// Idea - 가능한 최대값에 도킹
// 1. 가장 숫자가 큰 게이트부터 채운다.
// 2. 해당 숫자가 비어있지 않다면, 한 칸씩 내려가면서 빈 자리에 채운다.

// 탐욕적 선택 속성 : 
// 게이트의 도킹될 수 있는 최대값 보다 더 작은 게이트에 비행기가 도킹 되어있다고 하자. (ex. 들어갈 수 있는 최대 게이트 = 4, 현재 게이트 = 3)
// 4번 게이트에 있는 비행기는 4번 게이트와 도킹이 되어 있는 상태이기 때문에 g_i >= 4임을 알 수 있다.
// 따라서 해당 비행기는 3번 게이트와 도킹이 가능하다. Idea와 다르게 도킹이 되어 있는 비행기도
// 4번 게이트에 도킹이 가능하므로 서로 위치를 바꿀 수 있고, 이 때 결과값은 달라지지 않는다.
// 따라서 Idea의 조건을 만족시키는 최적해가 존재한다.
// Q.E.D.
// 최적 부분 구조 : 앞의 비행기를 도킹 시킨 상태로 변화한 상태에서의 최대 도킹 수를
// 찾아야 하기 때문에 최적 부분 구조가 존재하는 것은 자명하다.

#include <iostream>
#include <set>
#include <algorithm>
using namespace std;
int P; int G;
set <int> gate;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> G >> P;
    for(int i = 0; i <= G; i++){ // 존재하는 게이트를 set으로 관리
        gate.insert(i);
    }

    int res = 0;
    bool dk = true;
    
    // 똑같은 알고리즘이나, 이진탐색으로 구현해서 해결.
    for (int i = 0; i < P; i++){
        int g_i;
        cin >> g_i;
        if(dk){
            // iter = g_i보다 큰 수 중 가장 작은 수
            auto iter = gate.upper_bound(g_i);
            iter--; // iter - 1이 도킹할 게이트
            if (iter == gate.begin()){ // 도킹할 게이트가 없다면
                dk = false;
            }
            else { // 있다면, 결과값++, 게이트 제거
                res++;
                gate.erase(iter);
            }
        }
    }

    cout << res << endl;
    return 0;
}