#include <iostream>
#include <vector>
using namespace std;
int n;
vector<int> height;
// divide and conquer
// 왼쪽 segment의 최대, 오른쪽 segment의 최대, 양쪽에 걸친 경우의 최대
// 세 경우 중 가장 큰 값 리턴

int recursiveCheck(int front, int back){
    if(front == back){return height[front];} // 기저, size가 1이면 높이를 리턴
    
    int midpoint = (front + back)/2; // front와 back의 중간지점
    int left = recursiveCheck(front, midpoint); // left segment 재귀 수행
    int right = recursiveCheck(midpoint+1, back); // right segment 재귀 수행
    int res = max(left, right); // 둘 중 큰 값을 결과에 저장

    // 왼쪽 오른쪽에 걸쳐있는 경우 계산
    int mid_l = midpoint; int mid_r = midpoint+1; // 왼쪽의 마지막 요소와 오른쪽의 첫 요소
    int h = min(height[mid_l], height[mid_r]); // 직사각형 높이
    res = max(res, h*(mid_r-mid_l+1)); // 직사각형 넓이 갱신(한칸씩 걸쳐서 만들어진 직사각형과 재귀호출의 것)

    while(front < mid_l || mid_r < back) // 가운데 상자가 전체 넓이가 될 때까지
    {
        // 걸친 상자의 왼쪽이 front보다 뒤에 있고, (오른쪽이 back이거나 확장할 왼쪽 높이가 큰 경우)
        if(front<mid_l && (mid_r==back || height[mid_l-1] > height[mid_r+1]))
        {
            mid_l--;
            h = min(height[mid_l], h);
        }
        else{
            mid_r++;
            h = min(h, height[mid_r]);
        }
        res = max(res, h*(mid_r-mid_l+1)); // 최대 넓이 갱신
    }
    return res;
}


int main() {
    cin >> n;
    for (int i = 0; i < n; i++){
        int input;
        cin >> input;
        height.push_back(input);
    }

    int res = recursiveCheck(0, n-1);
    cout << res << endl;
    return 0;
}