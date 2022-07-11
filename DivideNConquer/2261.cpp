#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
//쿼드 트리 문제?
// 1. x값을 기준으로 정렬 (퀵소트)
// 2. 중간을 기준으로 왼쪽에서의 최소와 오른쪽에서의 최소를 구함(분할)
// 3. 2에서 구한 최소값 범위 내의 지점에 대해서 최소값을 구함 (걸치는 것)

struct Point
{
    int x, y;
};

struct Comp {
    bool comp_in_x;
    Comp(bool b) : comp_in_x(b) {}
    bool operator()(Point &p, Point &q) {
        return (this->comp_in_x? p.x < q.x : p.y < q.y);
    }
};

int checkDistance(Point &a, Point &b){
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}

int checkAnswer(vector<Point>:: iterator it, int n){
    if (n == 2){return checkDistance(it[0], it[1]);}
    if (n == 3){
        return min({checkDistance(it[0], it[1]), checkDistance(it[1], it[2]), checkDistance(it[0], it[2])});
    }

    int x_mid = (it[n/2-1].x + it[n/2].x)/2;
    int d = min(checkAnswer(it, n/2), checkAnswer(it + n/2, n-n/2));

    vector<Point> y = {};

    for (int i = 0; i < n; i ++){
        int t = x_mid - it[i].x;
        if (t*t < d){y.push_back(it[i]);}
    }

    int y_size = y.size();
    sort(y.begin(), y.end(), Comp(false));
    for(int i = 0; i < y_size-1; i++){
        for(int j = i+1; (j < y_size) && ((y[j].y-y[i].y)*(y[j].y-y[i].y)<d); j++){
            d = min(d, checkDistance(y[i], y[j]));
        }
    }
    return d;
}


int main(){
    ios_base::sync_with_stdio(false); 
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    vector<Point> space(n);
    for(auto it = space.begin(); it != space.end(); it++){
        cin >> it->x >> it->y;
    }

    sort(space.begin(), space.end(), Comp(true));

    int ans = checkAnswer(space.begin(), n);
    cout << ans << endl;

    return 0;
}