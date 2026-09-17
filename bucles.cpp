// Ejercicio 1: comparacion de los dos pares de bucles anidados
// (Pacheco, Capitulo 2, pagina 22)
//
// Compilar: g++ -std=c++14 -O2 bucles.cpp -o bucles
// Ejecutar: ./bucles MAX
#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Uso: ./bucles MAX" << endl;
        return 1;
    }
    int MAX = atoi(argv[1]);

    // A se guarda en un vector de MAX*MAX, fila por fila: A[i][j] = A[i*MAX + j]
    vector<double> A(MAX * MAX);
    vector<double> x(MAX);
    vector<double> y(MAX);

    for (int i = 0; i < MAX; i++) {
        x[i] = 1.0;
        for (int j = 0; j < MAX; j++)
            A[i * MAX + j] = i + j;
    }

    // Primer par de bucles: recorre A por filas
    for (int i = 0; i < MAX; i++) y[i] = 0;
    auto inicio = chrono::high_resolution_clock::now();
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            y[i] += A[i * MAX + j] * x[j];
    auto fin = chrono::high_resolution_clock::now();
    double t1 = chrono::duration<double>(fin - inicio).count();

    // Segundo par de bucles: recorre A por columnas
    for (int i = 0; i < MAX; i++) y[i] = 0;
    inicio = chrono::high_resolution_clock::now();
    for (int j = 0; j < MAX; j++)
        for (int i = 0; i < MAX; i++)
            y[i] += A[i * MAX + j] * x[j];
    fin = chrono::high_resolution_clock::now();
    double t2 = chrono::duration<double>(fin - inicio).count();

    long long iteraciones = (long long)MAX * MAX;

    // Salida: MAX, iteraciones, tiempo primer par, tiempo segundo par
    cout << MAX << "," << iteraciones << "," << t1 << "," << t2 << endl;
    return 0;
}
