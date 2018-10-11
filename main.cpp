#include <iostream>
#include <MyVector.h>

using namespace std;

int main() {
    MyVector v (0,1,0);
    cout << v.magnitude() << " " << v.toString() << endl;

    MyVector u (1,0,0);
    cout << u.magnitude() << " " << u.toString() << endl;

    cout << v.cosTheta(u);

    return 0;
}
