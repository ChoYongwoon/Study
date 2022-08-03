#include <iostream>
#include <math.h>
#include <vector>
using namespace std;
int num;
int n;

int main(){
    cin >> num;
    cin >> n;
    vector<int> broken;
    for (int i = 0; i < n; i++){
        int tmp;
        cin >> tmp;
        broken.push_back(tmp);
    }

    int nearest = -10000;
    int term = 1000000;
    for (int i = 0; i <= 999900; i++){ // key point
    // 999900 돌리는 이유 -> 이 이후로는 경우의 수가 나올 수 없음
        int tmp = i;
        int cnt = 0;
        do
        {
            bool check = false;
            int k = tmp%10;
            for (int j = 0; j < n ; j++){
                if (broken[j] == k) {
                    check = true;
                    break;
                }
            }
            if (check) break;
            cnt++;
            tmp /= 10;
        } while (tmp != 0);
        if (cnt != to_string(i).size()) continue;

        if (abs(num - i) < term){ // ex) num이 10일 때 9와 11인 경우 -> 등호 X
            nearest = i;
            term = abs(num-i);
        }
    }

    cout << "Nearest: " << nearest << endl;

    int option1; int option2;
    option1 = abs(num-100);
    option2 = to_string(nearest).size()+abs(num-nearest);
    int res = option1<option2? option1: option2;

    cout << "option1: " << option1 << endl;
    cout << "option2: " << option2 << endl;

    cout << res << endl;
    return 0;
}