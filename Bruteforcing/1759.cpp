#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int c; int l;
vector<char> mo = {'a', 'e', 'i', 'o', 'u'};
int m=0;
int g=0;
string temp = "";

void recursive(vector<char>& cand, int n, int c){
    if (c==0 && m>=1 &&g>=2){
        cout<< temp <<endl;
        return;
    }

    for (int i = n+1; i < l; i++){
        bool b = false;
        temp += cand[i];
        if(find(mo.begin(), mo.end(), cand[i])!=mo.end()){
            m++; b = true;
        }
        else{g++;}
        recursive(cand, i, c-1);
        temp.pop_back();
        if(b){m--;}
        else{g--;}
    }

}

int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> c >> l;
    vector<char> cand;

    for (int i = 0; i < l; i++){
        char tmp;
        cin >> tmp;
        cand.push_back(tmp);
    }
    sort(cand.begin(), cand.end());

    recursive(cand, -1, c);
    return 0;
}