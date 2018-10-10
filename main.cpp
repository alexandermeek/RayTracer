#include <iostream>
#include <MyVector.h>

using namespace std;

int main()
{
    MyVector v (1,1,1);
    //cout << 2^2 << endl;
    cout << v.getLength() << endl;
    cout << v.toString() << endl;
    return 0;
}
