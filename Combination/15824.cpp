// N개의 음식이 주어졌다.
// 가장 큰 음식이 더해지는 횟수 => (N-1) C 1 + (N-1) C 2 + (N-1) C 3 + ... + (N -1) C (N-1) = 2 ^ (N-1) -1
// 두 번째로 큰 음식이 더해지는 횟수 => (N-2) C 1 + (N-2) C 2 + ... + (N-2) C (N-2) = 2 ^ (N-2) -1
// 두 번째로 큰 음식이 빼지는 횟수 =>  1 C 1 = 2 ^ 1 - 1
// 세 번째로 큰 음식이 더해지는 횟수 => 2 ^ (N-3) - 1
// 세 번째로 큰 음식이 빼지는 횟수 => 2 ^ 2 -1

// i 번째로 큰 음식이 더해지는 횟수 => 2 ^ (N-i) -1
// i 번째로 큰 음식이 빼지는 횟수 => 2 ^ (i-1) -1

// 따라서 정답 = sigma (i = 1 to N) (v[N-i] * (2^(N-i) -1) - v[N-i] * (2^(i-1) -1))
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
long long INF = 1e9+7; //소수
int N; 
vector<int> nums;
long long cache[300001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    cache[0] = 1;
    for(int i = 1; i <= N; i++){
        cache[i] = cache[i-1] * 2 % INF;
    }

    for(int i = 0; i < N; i++){
        int tmp;
        cin >> tmp;
        nums.push_back(tmp);
    }

    sort(nums.begin(), nums.end(), greater<int>());

    long long res = 0;
    for (int i = 0; i < N; i++){
        res += nums[i]*(cache[N-i-1]-1);
        res -= nums[i]*(cache[i] -1);
        res %= INF;
        if(res < 0){res += INF;}
    }

    cout << res << endl;
    return 0;
}