#!/bin/bash
# Ejercicio 5: analisis con Cachegrind
# Uso: ./cachegrind.sh laptop|pc [n] [bloque]
#
# Se indican los tamanios reales de cache de cada procesador:
#   laptop (i5-3230M): L1 32 KB, L3 3 MB
#   pc     (i5-10400): L1 32 KB, L3 12 MB

if [ "$1" == "pc" ]; then
    LL="12582912,12,64"
else
    LL="3145728,12,64"
fi
N=${2:-512}
B=${3:-32}
CACHE="--I1=32768,8,64 --D1=32768,8,64 --LL=$LL"

make
mkdir -p cachegrind

echo "Cachegrind clasica n=$N"
valgrind --tool=cachegrind $CACHE --cachegrind-out-file=cachegrind/clasica_$N.out \
    ./clasica $N 2> cachegrind/clasica_$N.txt

echo "Cachegrind bloques n=$N bloque=$B"
valgrind --tool=cachegrind $CACHE --cachegrind-out-file=cachegrind/bloques_${N}_$B.out \
    ./bloques $N $B 2> cachegrind/bloques_${N}_$B.txt

echo ""
echo "===== Resumen clasica ====="
grep -E "refs|misses|miss rate" cachegrind/clasica_$N.txt
echo ""
echo "===== Resumen bloques ====="
grep -E "refs|misses|miss rate" cachegrind/bloques_${N}_$B.txt
echo ""
echo "Para ver el detalle: kcachegrind cachegrind/clasica_$N.out"
