#include <iostream>
#include <vector>
using namespace std;
int n;
vector<int> arr;
long long res;
// enhanced merge sort
void mergeSort(int front, int back){
    if(front == back){return;}

    int midP = (front + back)/2;
    mergeSort(front, midP);
    mergeSort(midP+1, back);

    int i = front; int j = midP+1;
    vector<int> temp = {};
    while (i <= midP && j <= back){
        if(arr[i] <= arr[j]){
            temp.push_back(arr[i++]); 
        }
        else{
            temp.push_back(arr[j++]);
            res += (midP-i+1);
        }
    }

    while (i <= midP)
    {
        temp.push_back(arr[i++]);
    }
    while (j <= back)
    {
        temp.push_back(arr[j++]);
    }

    int cnt = 0;
    for (int k = front; k <= back; k++){
        arr[k] = temp[cnt++];
    }

    temp.clear();

    return;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i ++){
        int tmp;
        cin >> tmp;
        arr.push_back(tmp);
    }

    mergeSort(0, n-1);
    cout << res << endl;

    return 0;
}
