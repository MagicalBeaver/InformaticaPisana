#include <iostream>
#include <vector>
#include <span>
#include <ctime>
#include <random>
#include <chrono>
using namespace std;
using namespace std::chrono;

int random(int a, int b)
{
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<int> dist(a,b);
    return dist(gen);

    //estremi inclusi:
    //return rand()%(b-a+1) + a;
}

vector<int> generaArrayCasuale(int n, int minVal = -100, int maxVal = 100)
{
    //v.push_back(value) aggiunge value al del vettore
    vector<int> v(n);
    for (int i = 0; i < n; i++)
    v[i] = random(minVal, maxVal);
    return v;
}

void printVector(const vector<int>& a)
{
    for (auto e : a)
    cout << e << " ";
}

int maxSum(const vector<int>& a)
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

vector<int> maxSumSegmentBasic(const vector<int>& a)
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

class SumSegment
{
    int Sum;              public: int sum() {return Sum;}
    int FirstIndex;       public: int firstIndex() {return FirstIndex;}
    int LastIndex;        public: int lastIndex() {return LastIndex;}
    vector<int> Segment;  public: vector<int> segment() {return Segment;}

    public: SumSegment(int sum, int firstIndex, int lastIndex, vector<int> segment)
    {
        Sum = sum;
        FirstIndex = firstIndex;
        LastIndex = lastIndex;
        Segment = segment;
    }
}
;

SumSegment maxSumSegment(const vector<int>& a)
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

    //if (maxSomma > 0) return SumSegment(maxSomma, firstIndex, lastIndex, span(a).subspan(firstIndex, lastIndex));
    if (maxSomma > 0) 
    return SumSegment(maxSomma, firstIndex, lastIndex, vector<int>(a.begin() + firstIndex, a.begin() + lastIndex + 1));
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
        return SumSegment(maxNeg, index, index, {maxNeg});
    }
}

int main()
{
    constexpr int n = 15;
    vector<int> a = generaArrayCasuale(n);
    printVector(a); cout << endl;


    //vector<int> result = maxSumSegmentBasic(a);
    //cout << "somma:  " << result[0] << endl << "range:  " << result[1] << " - " << result[2] << endl;
    /*SumSegment result = maxSumSegment(a);
    cout << "somma:  " << result.sum() << endl << "range:  " << result.firstIndex() << " - " << result.lastIndex() << endl << "array:  ";
    printVector(result.segment()); cout << endl;
    return 0;*/

    //loop tra funzioni:
    using FuncPtr = int (*)(const vector<int>&);
    FuncPtr funzioni[] = 
    {
        maxSum
    };
    string tipologia[] = 
    {
        "Just Sum: ",
        "All But Basic: ",
        "Everything In Class: "
    };

    for (int i = 0; i < sizeof(funzioni)/sizeof(funzioni[0]); i++)
    {
        FuncPtr f = funzioni[i];
        string tipo = tipologia[i];

        auto start = high_resolution_clock::now();

        int risultato = f(a);

        auto stop = high_resolution_clock::now();
        auto durata = duration_cast<microseconds>(stop - start);

        cout << tipo << endl << "somma:  " << risultato << endl << "durata: " << durata.count() << " ms";
    }

}