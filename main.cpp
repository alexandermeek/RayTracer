#include <iostream>
#include <MyVector.h>

using namespace std;

int main() {
    MyVector v (1,1,1);
    cout << v.getLength() << endl;
    cout << v.toString() << endl;

    MyVector u (2,2,2);
    cout << u.toString() << endl;
    u = u * 2;
    cout << u.toString() << endl;

    MyVector w;
    w = u - v;
    cout << w.toString() << endl;

    int a [3] = {0,0,0};
    int b [3] = {1,1,1};
    MyVector x (a, b);
    cout << x.toString();

    cout << w.dotP(u);

    return 0;
}
