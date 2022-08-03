#include <iostream>
#include <vector>
using namespace std;
int n;
vector<vector<int>> town;
vector<vector<int>> dist;
vector<vector<int>> chicken;


int main() {
    cin >> n;
    town.resize(n);
    dist.resize(n);

    for (int i = 0; i < n; i++){
        town[i].resize(n);
        dist[i].resize(n);
        for(int j = 0; j < n; j++){
            int tmp;
            cin >> tmp;
            town[i][j] = tmp;
            if(tmp == 2){
                chicken.push_back({i,j});
                dist[i][j] = 0;
            }
            if(tmp == 0){
                dist[i][j] = 0;
            }
            if(tmp == 1){
                dist[i][j] = 10000;
            }
        }
    }


    return 0;
}