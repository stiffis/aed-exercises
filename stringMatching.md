# String Matching

Consiste en encontrar una subcadena dentro de una cadena más grande.
Existen varios algoritmos para realizar esta tarea, cada uno con sus propias
ventajas y desventajas.

- Aplicación en el operador `like` de SQL.
- Aplicación en la búsqueda de patrones en textos.

## Metodo

- Entrada:
  Dos strings sobre el alfabeto {a, b} de longitud m y n respectivamente.
- Salida:
  Un entero que representa la posición de la primera aparición de la subcadena

## Intuición

```textplain
StringMatching(Patron P[m], Texto T[n]) {
    Result = ()
    For j = 0 to n - m {
        i = 0
        While P[i] == T[j+i] and i < m {
            i = i + 1
        }
        If i == m {
            Result.add(j)
        }
    }
```

Complejidad Temporal: O(n \* m)
Complejidad Espacial: O(1)

## Algoritmo Boyer-Moore

El algoritmo Boyer-Moore es un algoritmo de búsqueda de patrones que utiliza
dos heurísticas para mejorar la eficiencia de la búsqueda: la heurística de mala coincidencia y la heurística de buena coincidencia.

## Heurística de mala coincidencia

La heurística de mala coincidencia se basa en la idea de que si un carácter no coincide, podemos saltar algunas posiciones en el texto.

## Heurística de buena coincidencia

La heurística de buena coincidencia se basa en la idea de que si un carácter coincide, podemos saltar algunas posiciones en el patrón.

# Suffix Tree

Un sufijo es una subcadena que comienza en una posición dada y se extiende hasta el final de la cadena. Un árbol de sufijos es una estructura de datos que representa todos los sufijos de una cadena.
