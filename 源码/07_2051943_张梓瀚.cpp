#include "priQue.h"
#include <iostream>
using namespace std;
int main(){
    int num;
    cin >> num;
    while (cin.fail() || num <= 0)
    {
        cin.clear();
        cin.ignore(1024, '\n');
        cout << "请输入正确的正整数N" << endl;
        cin >> num;
    }
    priQue<int> heap(num);
    for (int i = 0, j; i < num;i++){
        cin >> j;
        while (cin.fail() || j <= 0)
        {
            cin.clear();
            cin.ignore(1024, '\n');
            cout << "请输入正确的正整数长度" << endl;
            cin >> j;
        }
        heap.push(j);
    }
    int ans = 0;
    while (heap.size() > 1)
    {
        int t1 = heap.top();
        heap.pop();
        int t2 = heap.top();
        heap.pop();
        ans += t1 + t2;
        if (heap.empty())
            break;
        else
            heap.push(t1 + t2);
    }
    cout << ans << endl;
    return 0;
}