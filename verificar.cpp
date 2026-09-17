// Verifica que la multiplicacion por bloques da el mismo resultado que la clasica
// Caso: n = 500 y b = 32 (500 no es multiplo de 32, el ultimo bloque tiene 20 filas)
//
// Compilar: g++ -std=c++14 -O2 verificar.cpp -o verificar
// Ejecutar: ./verificar
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n = 500;
    int b = 32;

    // Valores distintos en cada posicion, para que un indice equivocado se note
    vector<double> A(n * n), B(n * n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            A[i * n + j] = (i + 2 * j) % 10;
            B[i * n + j] = (3 * i + j) % 10;
        }

    // Multiplicacion clasica
    vector<double> C1(n * n, 0.0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                C1[i * n + j] += A[i * n + k] * B[k * n + j];

    // Multiplicacion por bloques
    vector<double> C2(n * n, 0.0);
    for (int ii = 0; ii < n; ii += b)
        for (int jj = 0; jj < n; jj += b)
            for (int kk = 0; kk < n; kk += b)
                for (int i = ii; i < min(ii + b, n); i++)
                    for (int j = jj; j < min(jj + b, n); j++)
                        for (int k = kk; k < min(kk + b, n); k++)
                            C2[i * n + j] += A[i * n + k] * B[k * n + j];

    // Comparar todas las posiciones
    if (C1 == C2)
        cout << "n=" << n << " b=" << b << " -> OK: los resultados son iguales" << endl;
    else
        cout << "n=" << n << " b=" << b << " -> ERROR: los resultados son distintos" << endl;

    return 0;
}
