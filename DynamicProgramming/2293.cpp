#include <iostream>
#include <vector>
using namespace std;
int cache[10001]; 
vector<int> coin;
int n; int k;

// a , b, c, d 원의 동전이 있다고 할 때
// res(k) = res(k-a)+ res(k-b)+ res(k-c)+ res(k-d)
// 중복이 매우 많이 생김

/* 실패한 코드
int count(int v){
    if (v == 0){return 1;}
    if (v < 0){return 0;}

    int &res = cache[v];
    if(res != (-1)){return res;}
    res = 0;
    for(int i = 0; i < n; i++){
        res += count(v-coin[i]);
    }
    return res;
}*/

int main(){
    ios_base::sync_with_stdio(false); 
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> k;
    for (int i = 0; i < n; i++){
        int tmp;
        cin >> tmp;
        coin.push_back(tmp);
    }

    cache[0] = 1;
    for (int i = 0; i < n ; i++){
        for(int j = coin[i]; j <= k; j++){
            cache[j] += cache[j-coin[i]];
        }
    }
    cout << cache[k] << endl;
    return 0;
}