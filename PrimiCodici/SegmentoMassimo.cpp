#include <iostream>
#include <vector>
using namespace std;

int maxSum(vector<int> a)
{
    int somma = 0;
    int maxSomma = 0;
    for (int i = 0; i < size(a); i++)
    {
        somma += a[i];
        if (somma > maxSomma)
        maxSomma = somma;
        else if (somma < 0)
        somma = 0;
    }

    if (maxSomma > 0) return maxSomma;
    else 
    {
        int maxNeg = a[0];
        for (int i = 1; i < size(a); i++)
        if (a[i] > maxNeg) maxNeg = a[i];
        return maxNeg;
    }
}

int main()
{
    vector<int> a = {10, 15, -4, -20, 52, 43, -127, 5, 69};

    cout << "sus" << endl;
    return 0;
}