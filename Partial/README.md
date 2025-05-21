# 📋 Indicaciones específicas

## Parte Práctica (máximo 30 minutos)

- Se resolverá en la computadora, **sin acceso a LeetCode ni a páginas externas a Canvas**.
- La solución debe programarse en **C++**, utilizando el siguiente IDE online: **C++ Compiler and Visualizer**.
- **No está permitido** utilizar otros IDEs como Visual Studio Code o CLion.
- El profesor proporcionará una plantilla básica con casos de prueba para facilitar el desarrollo de la solución.

---

# 💻 Parte Práctica (6 puntos)

Imagina que estás desarrollando el motor de historial de un navegador web o una aplicación de búsqueda como Google, Bing o incluso un sistema interno corporativo. Cada vez que un usuario introduce un término en la barra de búsqueda, ese término debe almacenarse para que el sistema:

- Pueda mostrar el historial cuando el usuario empiece a escribir de nuevo (autocompletado).
- Ofrezca una vista del historial en orden **cronológico** para que el usuario pueda revisar qué buscó y cuándo.
- También permita ver los términos en orden **alfabético**, por ejemplo, para hacer limpieza manual o para buscar visualmente por palabra clave.
- Permita **eliminar términos específicos**, ya sea por privacidad o por corrección.

> No tiene sentido almacenar múltiples veces el mismo término: si ya buscaste “cómo hacer pan” ayer, no necesitas duplicarlo hoy. Pero sí quieres saber **cuándo fue la primera vez** que lo buscaste.

---

## 🎯 Funcionalidades requeridas

El programa debe cumplir con las siguientes características técnicas:

### 1. `void add(string term);`
- Registra un nuevo término si no ha sido registrado antes.
- Debe permitir consultas posteriores en orden cronológico y alfabético.
- **Complejidad:** `O(log n)`

### 2. `void showChronological();`
- Devuelve los términos en el orden exacto en que fueron buscados, **sin repeticiones**.
- **Complejidad:** `O(n)`

### 3. `void showAlphabetical();`
- Devuelve todos los términos en **orden alfabético ascendente**.
- **Complejidad:** `O(n)`

### 4. `void remove(string term);`
- Elimina un término del historial en todas sus representaciones.
- **Complejidad:** `O(log n)`

---

## 🧪 Ejemplo de uso

```cpp
history.add("cpp");
history.add("estructura");
history.add("arbol");
history.add("codigo");
history.add("cpp"); // Ignorar repetido
history.add("datos");

history.showChronological();   
// ["cpp", "estructura", "arbol", "codigo", "datos"]

history.showAlphabetical();  
// ["arbol", "codigo", "cpp", "datos", "estructura"]

history.remove("codigo");

history.showChronological();    
// ["cpp", "estructura", "arbol", "datos"]

history.showAlphabetical();
// ["arbol", "cpp", "datos", "estructura"]
