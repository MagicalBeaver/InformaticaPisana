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

void SelectionSort(vector<int>& a)
{

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

int main()
{
    constexpr int n = 50;
    vector<int> a = generaArrayCasuale(n);
    printVector(a); cout << endl;

    auto start = high_resolution_clock::now();

    InsertionSort(a);

    auto stop = high_resolution_clock::now();
    auto durata = duration_cast<microseconds>(stop - start);

    cout << "sorted vector: " << endl;
    printVector(a);
    cout << endl << "durata: " << durata.count() << " ms";
}