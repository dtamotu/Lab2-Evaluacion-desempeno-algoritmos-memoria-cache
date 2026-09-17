# Genera las graficas del informe a partir de los CSV
# Uso: python graficas.py [carpeta_resultados] [nombre]
# Ejemplo: python graficas.py resultados_pc pc
import sys
import os
import pandas as pd
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

carpeta = sys.argv[1] if len(sys.argv) > 1 else "resultados"
nombre = sys.argv[2] if len(sys.argv) > 2 else "lab"
os.makedirs("graficas", exist_ok=True)


def guardar(archivo):
    plt.tight_layout()
    plt.savefig("graficas/" + nombre + "_" + archivo, dpi=150)
    plt.close()


# Ejercicio 1: bucles por filas vs por columnas (promedio de las repeticiones)
d = pd.read_csv(carpeta + "/bucles.csv").groupby("MAX").mean().reset_index()
plt.figure(figsize=(5, 3.5))
plt.plot(d["MAX"], d["t_filas"], "o-", label="Primer par (filas)")
plt.plot(d["MAX"], d["t_columnas"], "s-", label="Segundo par (columnas)")
plt.xlabel("MAX")
plt.ylabel("Tiempo (s)")
plt.title("Bucles anidados (" + nombre + ")")
plt.legend()
plt.grid(True)
guardar("bucles.png")

# Ejercicio 2: multiplicacion clasica
c = pd.read_csv(carpeta + "/clasica.csv").groupby("n").mean().reset_index()
plt.figure(figsize=(5, 3.5))
plt.plot(c["n"], c["tiempo"], "o-")
plt.xlabel("n")
plt.ylabel("Tiempo (s)")
plt.title("Multiplicacion clasica (" + nombre + ")")
plt.grid(True)
guardar("clasica.png")

# Ejercicio 3: clasica vs bloques
b = pd.read_csv(carpeta + "/bloques.csv").groupby(["n", "bloque"]).mean().reset_index()
plt.figure(figsize=(5, 3.5))
plt.plot(c["n"], c["tiempo"], "ko-", label="Clasica")
for tam in sorted(b["bloque"].unique()):
    datos = b[b["bloque"] == tam]
    plt.plot(datos["n"], datos["tiempo"], "o--", label="Bloques " + str(tam))
plt.xlabel("n")
plt.ylabel("Tiempo (s)")
plt.title("Clasica vs por bloques (" + nombre + ")")
plt.legend()
plt.grid(True)
guardar("clasica_vs_bloques.png")

# Ejercicio 3: efecto del tamanio de bloque para el n mas grande
nmax = b["n"].max()
datos = b[b["n"] == nmax]
tclasica = c[c["n"] == nmax]["tiempo"].values[0]
plt.figure(figsize=(5, 3.5))
plt.bar([str(x) for x in datos["bloque"]], datos["tiempo"], label="Bloques")
plt.axhline(tclasica, color="red", linestyle="--", label="Clasica")
plt.xlabel("Tamanio de bloque")
plt.ylabel("Tiempo (s)")
plt.title("Efecto del bloque, n=" + str(nmax) + " (" + nombre + ")")
plt.legend()
guardar("tam_bloque.png")

# Tablas resumen en texto (promedios) para copiar al informe
with open("graficas/" + nombre + "_resumen.txt", "w") as f:
    f.write("== Bucles ==\n")
    d["columnas/filas"] = d["t_columnas"] / d["t_filas"]
    f.write(d.to_string(index=False) + "\n\n")
    f.write("== Clasica ==\n")
    f.write(c.to_string(index=False) + "\n\n")
    f.write("== Bloques ==\n")
    tabla = b.pivot(index="n", columns="bloque", values="tiempo")
    tabla["clasica"] = c.set_index("n")["tiempo"]
    f.write(tabla.to_string() + "\n")

print("Graficas guardadas en la carpeta graficas/ con el prefijo", nombre)
