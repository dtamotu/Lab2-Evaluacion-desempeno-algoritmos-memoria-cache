// Ejercicio 3: multiplicacion de matrices por bloques (seis bucles anidados)
//
// Compilar: g++ -std=c++14 -O2 bloques.cpp -o bloques
// Ejecutar: ./bloques n tamBloque
#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Uso: ./bloques n tamBloque" << endl;
        return 1;
    }
    int n = atoi(argv[1]);
    int b = atoi(argv[2]);

    vector<double> A(n * n), B(n * n), C(n * n, 0.0);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            A[i * n + j] = 1.0;
            B[i * n + j] = 2.0;
        }

    auto inicio = chrono::high_resolution_clock::now();

    // Los tres primeros bucles recorren los bloques
    for (int ii = 0; ii < n; ii += b)
        for (int jj = 0; jj < n; jj += b)
            for (int kk = 0; kk < n; kk += b)
                // Los tres siguientes multiplican dentro del bloque
                for (int i = ii; i < min(ii + b, n); i++)
                    for (int j = jj; j < min(jj + b, n); j++)
                        for (int k = kk; k < min(kk + b, n); k++)
                            C[i * n + j] += A[i * n + k] * B[k * n + j];

    auto fin = chrono::high_resolution_clock::now();
    double tiempo = chrono::duration<double>(fin - inicio).count();

    // Comprobacion: cada elemento de C debe valer 2*n
    if (C[0] != 2.0 * n)
        cout << "Error en el resultado" << endl;

    // Salida: n, tamanio de bloque, tiempo en segundos
    cout << n << "," << b << "," << tiempo << endl;
    return 0;
}
