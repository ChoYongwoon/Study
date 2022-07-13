#include <iostream>
using namespace std;
int N;
int cache[31];
//과정이 존나 tricky... 오히려 다른 문제들보다 어려웠음
//f[0] = 1 
//f[2] = 3
//f[4] = 11 (3*f[4-2] + 2) 
//f[6] = 41 (3*f[6-2] + 2*f[6-4] + 2)
//f[N] = (f[N-2] * 3) + (f[N-4]*2) + (f[N-6]*2) + ... + f(0)*2
//f[N-2]=               (f[N-4]*3) + (f[N-6]*2) + ... + f(0)*2
//f[N] - f[N-2] = f[N-2]*3 - f[N-4]
//f[N] = 4*f[N-2] - f[N-4] 

int solve(int n){
    if (n==0){return 1;}
    if (n%2){return 0;}
    if (n==2){return 3;}

    int& res = cache[n];
    if(res != (-1)){return res;}

    res = 0;
    // f[N] = 4*f[N-2] - f[N-4]
    res = 4*solve(n-2) - solve(n-4);
    return res;
}

int main(){
    cin >> N;
    fill(&cache[0], &cache[0]+31, -1);

    int res = solve(N);
    cout << res << endl;
    return 0;
}