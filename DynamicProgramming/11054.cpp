#include <iostream>
#include <vector>
using namespace std;
int N;
vector<int> arr;
int lis_l[1001];
int lis_r[1001];
//양측으로 LIS 를 구하면 되지 않을까?
int main(){
    cin >> N;
    for(int i = 0; i < N; i++){
        int tmp;
        cin >> tmp;
        arr.push_back(tmp);
    }
    // 왼쪽부터 LIS의 길이를 구함
    for (int i = 1; i <= N; i++){
        for (int j = i-1; j >= 0; j--){
            if(arr[i-1] > arr[j-1]){
                lis_l[i] = max(lis_l[i], lis_l[j]+1);
            }
        }
        if(!lis_l[i]){lis_l[i] = 1;}
    }
    // 오른쪽부터 LIS의 길이를 구함
    for (int i = N; i >= 1; i--){
        for (int j = i+1; j <= N; j++){
            if(arr[i-1] > arr[j-1]){
                lis_r[i] = max(lis_r[i], lis_r[j]+1);
            }
        }
        if(!lis_r[i]){lis_r[i] = 1;}
    }
    // 전체중 왼쪽 오른쪽 LIS의 합 -1 의 최대값
    int res = 0;
    for (int i = 1; i <= N; i++){
        int tmp = lis_l[i] + lis_r[i] - 1;
        if(tmp > res){res = tmp;}
    }

    cout << res <<endl;

    return 0;
}