#include "rollingmedian.h"
#include <iostream>

using namespace std;

int main()
{
    string input;
    getline(cin, input);
    cout << RollingMedians().getMedians(input);
    return 0;
}
