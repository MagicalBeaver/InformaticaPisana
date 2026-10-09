// compila con:  g++ -std=c++17 segmax.cpp -o segmax
#include <iostream>
#include <vector>
#include <string>

// per creare numeri casuali
#include <random>
// per misurare i tempi di esecuzione
#include <chrono>

using namespace std;

int SommaMassima1(const vector<int>& B){ // O(n^3) tempo
    auto maxs = 0;
    auto n = B.size();  // numero di interi presenti in B
    for (auto i = 0; i < n; ++i){
        for (auto j = i; j < n; ++j){ // tutte le coppie 0 ≤ i ≤ j <n: Theta(n^2)
            auto somma = 0;
            for (auto k = i; k <= j; ++k)
                somma += B[k]; // somma = somma + B[k]
            if (somma > maxs)
                maxs = somma;
        }
    }
    return maxs;
}

int SommaMassima2(const vector<int>& B){ // O(n^2) tempo
    auto maxs = 0;
    auto n = B.size();  // numero di interi presenti in B
    for (auto i = 0; i < n; ++i){
        auto somma = 0;
        for (auto j = i; j < n; ++j){
            somma += B[j]; // somma = somma + B[j]
            if (somma > maxs)
                maxs = somma;
        }
    }
    return maxs;
}

int SommaMassima3(const vector<int>& B) { // O(n) tempo
  auto maxs = 0;
  auto somma = 0;

  for (auto j = 0; j < B.size(); j++) {
    if (somma > 0)
      somma += B[j];  // deposito/prelievo
    else
      somma = B[j];   // apri nuovo c/c

    if (somma > maxs)
      maxs = somma;
  }
  return maxs;
}


int random(int a, int b){ // restituisce un numero random in [a..b]
    static random_device rd;  // per inizializzare il generatore
    static mt19937 gen(rd()); // static evita di creare ogni volta il generatore a ogni chiamata 
    uniform_int_distribution<int> dist(a, b);

    return dist(gen);
}

vector<int> generaArrayCasuale(int n, int minVal = -100, int maxVal = 100){  // accetta solo n oppure tutti gli argomenti
    vector<int> A(n); // vettore di n interi da riempire
    for (auto i = 0; i < n; i++){
        A[i] = random(minVal,maxVal);
    }
    return A;
}

void printArray(const vector<int>& B){
    //for (auto i = 0; i < B.size(); ++i){ cout << B[i] << " ";}
    for (auto x : B){
        cout << x << " ";
    }
    cout << endl;
}

int main()
{
    constexpr auto N = 100;                // dimensione = numero di interi random
    vector<int> A = generaArrayCasuale(N); // vector<int> A = {4, -6, 3, 5, -2, 1, -4, 6, -3};
    A[0] = 1, A[N - 1] = -1; // così abbiamo almeno un positivo e un negativo in A
    if (N < 100)
        printArray(A); // questa chiamata ignorata se N è grande

    // array di puntatori a funzioni, evita di scrivere tre volte il codice per misurare i tempi
    using FuncPtr = int (*)(const vector<int> &);
    FuncPtr funzioni[] = {
        SommaMassima3,
        SommaMassima2,
        SommaMassima1
    };
    string complessita[] = {
        "lineare",
        "quadratica",
        "cubica"
    };

    for (auto i = 0; i < 3; ++i) {
        auto f = funzioni[i]; // SommaMassima
        auto costo = complessita[i]; // ricordiamoci la sua complessità teorica

        auto start = chrono::high_resolution_clock::now();  // tempo d'inizio

        auto risultato = f(A); // calcoliamo una delle SommaMassima a turno

        auto stop = chrono::high_resolution_clock::now();    // tempo di fine
        auto durata = chrono::duration_cast<chrono::microseconds>(stop - start);

        cout << "Somma massima (tempo " << costo << "): " << risultato << " [" << durata.count() << " microsecondi]" << endl;
    }
   
    return 0;
}
