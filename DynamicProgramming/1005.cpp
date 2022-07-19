#include <iostream>
#include <vector>
#include <list>
using namespace std;
int iter;
int N; int K; int W;
vector<vector<int>> building;
vector<int> consumed_time;
vector<int> chain_time;

void input(){ // input 받는 함수
    cin >> N >> K;
    consumed_time.clear();
    building.clear();
    chain_time.clear();

    consumed_time.resize(N+1);
    building.resize(N+1);
    chain_time.resize(N+1);
    chain_time[0] = -1;
    for (int i = 1; i <= N; i++){
        int tmp;
        cin >> tmp;
        consumed_time[i] = tmp;
        chain_time[i] = -1;
    }

    for (int i = 0; i < K; i++){
        int in; int out;
        cin >> in >> out;
        building[out].push_back(in);
    }
    cin >> W;
}

int solve(int w){ // 지으려는 집 solve, 뒤에서부터 생각하면 쉬움.
    if (building[w].empty()){
        return consumed_time[w];
    }

    int &res = chain_time[w];
    if(res != -1){
        return res;
    }

    res = 0;
    for(int i = 0; i < building[w].size(); i++){
        res = max(res, solve(building[w][i]));
    }
    res += consumed_time[w];
    return res;
}

int main(){
    ios_base::sync_with_stdio(false);

    cin >> iter;

    for (int it = 0; it < iter; it++){
        input();
        int res = solve(W);
        cout << res << endl;
    }
    return 0;
}