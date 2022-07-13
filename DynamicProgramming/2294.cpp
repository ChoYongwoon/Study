#include <iostream>
#include <vector>
using namespace std;
int cache[10001]; 
vector<int> coin;
int n; int k;

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
    fill(&cache[0], &cache[0]+10001, 10001);
    cache[0] = 0;

    for (int i = 0; i < n ; i++){
        for(int j = coin[i]; j <= k; j++){
            // i번째 동전을 사용한 경우와 그렇지 않은 경우 중 최소 값
            cache[j] = min(cache[j], cache[j-coin[i]] + 1);
        }
    }
    if (cache[k] != 10001){
        cout << cache[k] << endl;
    }
    else{
        cout << -1 << endl;
    }
    return 0;
}