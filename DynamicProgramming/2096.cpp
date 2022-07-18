#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int input[100000][3];
int N;
int cache[2][3];

int Big_solve(){
    for(int i = 0; i < 2 ; i++){
        for (int j = 0; j < 3; j++){
            cache[i][j] = 0;
        }
    }

    for (int i = 0; i < N; i++){
        cache[1][0] = max(cache[0][0], cache[0][1])+input[i][0];
        cache[1][1] = max({cache[0][0], cache[0][1], cache[0][2]})+input[i][1];
        cache[1][2] = max(cache[0][1], cache[0][2])+input[i][2];

        for (int j = 0; j < 3; j++){
            cache[0][j] = cache[1][j];
        }
    }
    int res = max({cache[1][0], cache[1][1], cache[1][2]});
    return res;
}

int Small_solve(){
    for(int i = 0; i < 2 ; i++){
        for (int j = 0; j < 3; j++){
            cache[i][j] = 0;
        }
    }

    for (int i = 0; i < N; i++){
        cache[1][0] = min(cache[0][0], cache[0][1])+input[i][0];
        cache[1][1] = min({cache[0][0], cache[0][1], cache[0][2]})+input[i][1];
        cache[1][2] = min(cache[0][1], cache[0][2])+input[i][2];

        for (int j = 0; j < 3; j++){
            cache[0][j] = cache[1][j];
        }
    }
    int res = min({cache[1][0], cache[1][1], cache[1][2]});
    return res;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < 3; j++){
            int tmp;
            cin >> tmp;
            input[i][j] = tmp;
        }
    }

    int max_result = Big_solve();
    int min_result = Small_solve();

    cout << max_result << " " << min_result << endl;
    return 0;
}