#include<iostream>
using namespace std;
long long D; long long P; long long Q;
long long res = 1e10;

int main(){
    ios_base::sync_with_stdio(false);

    cin >> D >> P >> Q;
    if(D%Q == 0 || D%P == 0){
        cout << D << endl;
        return 0;
    }
    
    /*
    long long max_Q = D/Q + 1;
    for (int i = 0; i < max_Q; i++){ // 모든 경우를 다 순회 (Q가 0개일 때부터 최대일 때까지)
        long long Q_term = Q*i;
        long long tmp = D-Q_term;
        if(tmp%Q == 0){
            cout << D << endl;
            return 0;
        }
        long long P_term = P*(tmp/P + 1);
        res = min(res, P_term + Q_term);
    }
    res = min(res, max_Q*Q);*/

    /*
    while(true){ // D에서 1씩 증가시켜가면서 가능한 경우를 확인 => 위의 방법보다 더 오래걸림..
        long long max_P = D/P + 1;
        bool check = false;
        for(int i = 0; i < max_P; i++){
            long long tmp = D - P*i;
            if(tmp % Q == 0){
                check = true;
                break;
            }
        }
        if(check){
            res = D;
            break;
        }
        D++;
    }*/

    
    //P랑 Q 중 더 큰 것을 사용하자! => 시간 초과
    if(P>Q) swap(P,Q);
    long long max_iter = D/Q + 1; // Q원 최대 사용 개수

    for (int i = 0; i < max_iter; i++){ // 모든 경우를 다 순회 (Q가 0개일 때부터 최대일 때까지)
        long long Q_term = Q*i;
        long long tmp = D-Q_term;
        if(tmp%P == 0){
            cout << D << endl;
            return 0;
        }
        long long P_term = P*(tmp/P + 1);
        if(res == P_term + Q_term){break;} // 반복되는 루프임을 알았고, 이 조건을 추가.
        res = min(res, P_term + Q_term);
    }
    res = min(res, max_iter*Q);

    cout << res << endl;

    return 0;
}