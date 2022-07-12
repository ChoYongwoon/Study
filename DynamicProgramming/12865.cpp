#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct thing
{
    int weight;
    int value;
};

vector<thing> bag;
vector<vector<int>> cache; // cache[i][j] : 0 ~ i번째 물건까지 담고, j만큼의 무게를 쓸 때 최대 가치
int N; int K;


int main(){
    ios_base::sync_with_stdio(false); 
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> K;
    bag.resize(N); cache.resize(N+1);

    for(auto it = bag.begin(); it != bag.end(); it++){
        cin >> it->weight >> it->value;
    }
    
    for(int i = 0; i < N+1 ; i++){
        cache[i].resize(K+1, 0);
    }

    for(int i = 1; i < N+1; i ++){
        int w = bag[i-1].weight;
        int v = bag[i-1].value;
        for (int j = 1; j < K+1; j++){
            if (j < w) {cache[i][j] += cache[i-1][j];}
            else{
                cache[i][j] = max(cache[i-1][j], cache[i-1][j-w] + v);
            }
        }
    }

    cout << cache[N][K] << endl;

    return 0;
}