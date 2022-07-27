// 구상한 알고리즘
// 1-1. 가치 순으로 보석 내림차순 정렬
// 1-2. 가방은 무게 기준 오름차순 정렬
// 2. 가장 가치가 높은 보석부터 들어갈 수 있는 가장 작은 가방에 넣는다.

// 탐욕적 선택 속성 : 
// 가장 가치가 큰 보석이 가방에 들어있지 않다고 하자.
// 해당 보석을 넣을 수 있는 들어갈 수 있는 가장 작은 가방에 찾아서 넣는다. => 기존의 해보다 크거나 같다.
// 설계한 논리에 따라서 바꾼 상태가 최적해가 된다.
// 가장 가치가 큰 보석이 가장 space 차이가 크지 않은
// 다른 가방에 들어있는 최적해가 존재한다고 하자. A가 있는 space가 알고리즘에 따라 위치할 space보다 크다.
// 가장 가치가 큰 보석 A를 알고리즘에 따라 들어가야 할 자리에 기존에 있는 보석 B와
// 자리를 바꾸어도 값은 변하지 않으므로, 위에서 언급한 조건을 만족하는 최적해가 존재한다.
// Q.E.D.
// 최적 부분 구조 : 가장 가치가 높은 보석을 넣게 되면 N-1개의 보석을 K-1개의 가방에
// 담을 수 있는 가장 큰 가치를 구해야 하기 때문에 최적 부분 구조가 존재한다.
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
int N; int K;
vector <pair<int, int>> jewelry;
multiset <int> bag;

bool jew_srt(pair<int, int> &a, pair<int, int> &b){
    if (a.second > b.second){ //조건문에 등호를 넣으면 런타임에러
        return true;
    }
    return false;
}

/* 시간 초과
long long solve(){
    long long res = 0;
    for (int i = 0; i < N; i++){
        bool isIn = false;
        if (bag.empty()) {break;}
        int j = 0;
        while(j < bag.size()){
            if(jewelry[i].first <= bag[j]){
                res += jewelry[i].second;
                isIn = true;
                break;
            }
            j++;
        }
        if(isIn){
            bag.erase(bag.begin() + j);
        }
    }
    return res;
}*/

/* 시간 초과
long long solve(){
    long long res = 0;
    for (int i = 0; i < N; i++){
        if (bag.empty()) {break;}
        vector<int> :: iterator tmp;
        tmp = lower_bound(bag.begin(), bag.end(), jewelry[i].first);
        if (tmp == bag.end()){continue;}
        else{
            int idx = tmp - bag.begin();
            res += jewelry[i].second;
            bag.erase(bag.begin() + idx);
        }
    }
    return res;
}*/

// multiset의 lower_bound를 사용함으로써 해결
long long solve(){
    long long res = 0;
    for (int i = 0; i < N; i++){
        if (bag.empty()) {break;}
        multiset<int> ::iterator tmp;
        tmp = bag.lower_bound(jewelry[i].first);
        if (tmp == bag.end()){continue;}
        else{
            res += jewelry[i].second;
            bag.erase(tmp);
        }
    }
    return res;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> K;
    for (int i = 0; i < N; i++){
        int m; int v;
        cin >> m >> v;
        jewelry.push_back(make_pair(m, v));
    }

    for (int i = 0; i < K; i++){
        int k;
        cin >> k;
        bag.insert(k);
    }

    sort(jewelry.begin(), jewelry.end(), jew_srt);
    
    long long res = solve();
    cout << res << endl;;

    return 0;
}