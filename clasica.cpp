// Ejercicio 2: multiplicacion clasica de matrices (tres bucles anidados)
//
// Compilar: g++ -std=c++14 -O2 clasica.cpp -o clasica
// Ejecutar: ./clasica n
#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Uso: ./clasica n" << endl;
        return 1;
    }
    int n = atoi(argv[1]);

    // Matrices de n x n guardadas fila por fila: M[i][j] = M[i*n + j]
    vector<double> A(n * n), B(n * n), C(n * n, 0.0);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            A[i * n + j] = 1.0;
            B[i * n + j] = 2.0;
        }

    auto inicio = chrono::high_resolution_clock::now();

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                C[i * n + j] += A[i * n + k] * B[k * n + j];

    auto fin = chrono::high_resolution_clock::now();
    double tiempo = chrono::duration<double>(fin - inicio).count();

    // Comprobacion: cada elemento de C debe valer 2*n
    if (C[0] != 2.0 * n)
        cout << "Error en el resultado" << endl;

    // Salida: n, tiempo en segundos
    cout << n << "," << tiempo << endl;
    return 0;
}
