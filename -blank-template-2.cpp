#include <iostream>
using namespace std;

const string nick = "buddy";

int cool(string nn)
{
    nn = nick;
    cout << "That's neat, " << nn << "!" << endl;
    return 0;
}
