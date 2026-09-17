#!/bin/bash
# Ejecuta los experimentos y guarda los tiempos en archivos CSV.
# Cada caso se repite 3 veces.

export LC_ALL=C
make

mkdir -p resultados
REPS=3

echo "Ejercicio 1: bucles"
echo "MAX,iteraciones,t_filas,t_columnas" > resultados/bucles.csv
for MAX in 500 1000 2000 3000 4000; do
    for r in $(seq $REPS); do
        ./bucles $MAX >> resultados/bucles.csv
    done
    echo "  MAX=$MAX listo"
done

echo "Ejercicio 2: multiplicacion clasica"
echo "n,tiempo" > resultados/clasica.csv
for n in 100 200 300 400 500 600 800 1000; do
    for r in $(seq $REPS); do
        ./clasica $n >> resultados/clasica.csv
    done
    echo "  n=$n listo"
done

echo "Ejercicio 3: multiplicacion por bloques"
echo "n,bloque,tiempo" > resultados/bloques.csv
for n in 100 200 300 400 500 600 800 1000; do
    for b in 16 32 64 128; do
        for r in $(seq $REPS); do
            ./bloques $n $b >> resultados/bloques.csv
        done
    done
    echo "  n=$n listo"
done

echo "Terminado. Resultados en la carpeta resultados/"
