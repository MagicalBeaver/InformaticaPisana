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

long fact(long n)
{
    return n <= 1 ? 1 : n*fact(n-1);
}

long fib(long n)
{
    long p = 1;
    long k = 1;
    for (long i = 3; i <= n; i++)
    {
        k = p + k;
        p = k - p;
    }
    return k;
}

void InsertionSort(vector<int>& a)
{
    for (int i = 1; i < a.size(); i++)
    {
        int t = a[i];
        int j = i;
        while (j > 0 && a[j-1] > t)
        {
            a[j] = a[j-1];
            j--;
        }
        a[j] = t;
    }
}

int dist(vector<int>& a, int start, int pivot, int stop)
{
    swap(a[pivot], a[stop]);
    int pivotValue = a[stop];

    int i = start;
    int j = stop-1;
    /*bool foundi = false;
    bool foundj = false;
    while (i < j)
    {
        if (a[i] <= pivotValue) i++;
        else foundi = true;
        if (a[j] > pivotValue) j--;
        else foundj = true;

        if (foundi & foundj)
        {
            swap(a[i], a[j]);

            foundi = false; foundj = false;
            i++; j--;
        }
    }*/
    while (i < j)
    {
        while (a[i] <= pivotValue && i < j) i++;
        while (a[j] > pivotValue && i < j) j--;

        if (i >= j) break;

        swap(a[i], a[j]);
        i++; j--;
    }

    int rank = a[i] > pivotValue ? i : i+1;
    swap(a[rank], a[stop]);
    return rank;
}

void quicksort(vector<int>& a, int start, int stop, int valueToStartDoingInsertionSort = 1)
{
    if (start < stop - (valueToStartDoingInsertionSort-1))
    {
        int pivot = random(start, stop);
        int rank = dist(a, start, pivot, stop);
        quicksort(a, start, rank-1, valueToStartDoingInsertionSort);
        quicksort(a, rank+1, stop, valueToStartDoingInsertionSort);
    }
}

void quicksort(vector<int>& a, int valueToStartDoingInsertionSort = 1)
{
    if (valueToStartDoingInsertionSort <= 1)
    quicksort(a, 0, a.size()-1);
    else 
    {
        quicksort(a, 0, a.size()-1, valueToStartDoingInsertionSort);
        InsertionSort(a);
    }
}

void doStuff(vector<int>& a, int L = 1)
{
    auto start = high_resolution_clock::now();

    quicksort(a, L);

    auto stop = high_resolution_clock::now();
    auto durata = duration_cast<microseconds>(stop - start);

    cout << "sorted vector: " << endl;
    printVector(a); cout << endl;
    cout << "durata: " << durata.count() << " us" << endl;
}

int main()
{
    constexpr int Lmax = 1000;
    constexpr int m = 1000;
    vector<int> a = generaArrayCasuale(m);
    //printVector(a); cout << endl;
    //vector<int> b = a;

    /*for (int i = 1; i <= Lmax; i++)
    {
        vector<int> b = a;
        doStuff(b, i);
    }*/

    doStuff(a, 16);

    /*doStuff(b, L);

    for (int i = 0; i < m; i++)
    b[i] -= a[i];
    printVector(b); cout << endl;*/
}