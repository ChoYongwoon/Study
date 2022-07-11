#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
bool same = false;
int ans = 20000*20000*2;
//쿼드 트리 문제?
// 1. x값을 기준으로 정렬 (퀵소트)
// 2. 첫 번째 원소부터 다른 원소와의 최소 거리 확인
// 3. x값의 차이가 최소거리 이하인 인덱스에서만 이를 확인

// -> 시간 초과

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

void checkAnswer(vector<Point> &space, int n){

    for (int i = 0; i < n; i ++){
        for (int j = i+1; j < n; j++){
            int check = (space[j].x-space[i].x);
            if(check*check > ans){break;}

            int tmp = checkDistance(space[i], space[j]);
            if (tmp <= ans){ans = tmp;}
        }
    }
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

    checkAnswer(space, n);
    cout << ans << endl;

    return 0;
}