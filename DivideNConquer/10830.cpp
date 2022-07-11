#include <iostream>
#include <vector>
using namespace std;
int n;
vector<vector<int>> B;
vector<vector<int>> I;

vector<vector<int>> matMul (int n, vector<vector<int>> a, vector<vector<int>> b){
    vector<vector<int>> res(n,vector<int>(n,0));
    long long int tmp = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for (int k = 0; k < n; k++){
                tmp += a[i][k] * b[k][j];
            }
            tmp %= 1000;
            res[i][j] = tmp;
            tmp = 0;
        }
    }

    return res;
}

vector<vector<int>> matPow (long long int m){
    if (m == 0){return I;}
    if (m%2){return matMul(n, matPow(m-1), B);}
    
    vector<vector<int>> half = matPow(m/2);
    return matMul(n, half, half);
}

int main() {
    long long int m = 0;
    cin >> n;
    cin >> m;
    B.resize(n);
    I.resize(n);
    for (int i = 0; i < n; i++){
        B[i].resize(n);
        I[i].resize(n);
        for (int j = 0; j < n; j++){
            int tmp;
            cin >> tmp;
            B[i][j] = tmp;
            I[i][j] = 0;
        }
        I[i][i] = 1;
    }

    vector<vector<int>> res = matPow(m);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cout << res[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}