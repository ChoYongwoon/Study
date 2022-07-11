#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int n;
int res;
vector<int> chess;

bool isOK(int i){
    for (int k = 0; k < i; k++){
        if(chess[k] == chess[i] || abs(chess[i]-chess[k])==i-k){
            return false;
        }
    }
    return true;
}


void check(int i){
    if(i == n){
        res++;
        return;
    }

    for (int j = 0 ; j < n ; j++){

        chess[i] = j;
        if(isOK(i)){
            check(i+1);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for(int i = 0; i < n; i++){
        chess.push_back(-1);
    }

    check(0);

    cout << res << endl;
    return 0;
}