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
        else if (somma <= 0)
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

vector<int> maxSumSegmentBasic(vector<int> a)
{
    int somma = 0;
    int maxSomma = 0;
    int currentFirstIndex = 0;
    int firstIndex = 0;
    int lastIndex = 0;
    for (int i = 0; i < size(a); i++)
    {
        somma += a[i];
        if (somma > maxSomma)
        {
            maxSomma = somma;
            lastIndex = i;
            firstIndex = currentFirstIndex;
        }
        else if (somma <= 0)
        {
            somma = 0;
            currentFirstIndex = i+1;
        }
    }

    if (maxSomma > 0) return {maxSomma, firstIndex, lastIndex};
    else 
    {
        int maxNeg = a[0];
        int index = 0;
        for (int i = 1; i < size(a); i++)
        if (a[i] > maxNeg) 
        {
            maxNeg = a[i];
            index = i;
        }
        return {maxNeg, index, index};
    }
}

/*class SumSegment
{
    int Sum = 0;
    int FirstIndex = 0;
    int LastIndex = 0;
    vector<int> Segment;

    SumSegment(int sum, int firstIndex, int lastIndex, int segment)
    {
        Sum = sum;
        FirstIndex = firstIndex;
        LastIndex = lastIndex;
        Segment = segment;
    }
}
;

vector<int> maxSumSegment(vector<int> a)
{
    int somma = 0;
    int maxSomma = 0;
    int currentFirstIndex = 0;
    int firstIndex = 0;
    int lastIndex = 0;
    for (int i = 0; i < size(a); i++)
    {
        somma += a[i];
        if (somma > maxSomma)
        {
            maxSomma = somma;
            lastIndex = i;
            firstIndex = currentFirstIndex;
        }
        else if (somma <= 0)
        {
            somma = 0;
            currentFirstIndex = i+1;
        }
    }

    if (maxSomma > 0) return new SumSegment(maxSomma, firstIndex, lastIndex, );
    else 
    {
        int maxNeg = a[0];
        int index = 0;
        for (int i = 1; i < size(a); i++)
        if (a[i] > maxNeg) 
        {
            maxNeg = a[i];
            index = i;
        }
        return new SumSegment(maxNeg, index, index, {maxNeg});
    }
}*/

int main()
{
    vector<int> a = {10, 15, -4, -20, 52, 43, -8, 100, -127, 5, 69, -400, 200};
    vector<int> b = {-5, -3, -27, 0, -4, -1};

    vector<int> result = maxSumSegmentBasic(b);
    cout << "somma:  " << result[0] << endl << "range:  " << result[1] << " - " << result[2] << endl;
    return 0;
}