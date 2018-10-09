#include <iostream>
#include <MyVector.h>

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    MyVector v (2,3,5);
    //cout << 2^2 << endl;
    cout << v.getLength() << endl;
    return 0;
}
