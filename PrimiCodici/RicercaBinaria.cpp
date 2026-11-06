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

int RicercaBinariaRicorsiva(const vector<int>& a, int k, int sx, int dx)
{
    if (sx > dx) return -1;
    else if (sx == dx) return a[sx] == k ? sx : -1;
    int cx = (sx + dx)/2;
    if (a[cx] >= k) return RicercaBinariaRicorsiva(a, k, sx, cx);
    else return RicercaBinariaRicorsiva(a, k, cx + 1, dx);
}

int RicercaBinariaRicorsiva(const vector<int>& a, int k)
{
    return RicercaBinariaRicorsiva(a, k, 0, a.size()-1);
}

int main()
{
    constexpr int n = 31;
    vector<int> a = {1, 2, 4, 4, 5, 6, 6, 6, 7, 9, 20, 31, 31, 31, 31, 31, 40};
    cout << RicercaBinariaRicorsiva(a, n);
}