#include <iostream>
#include <string>
#include <vector>
using namespace std;
const int M = 5; // Grado máximo del B-tree (máximo de hijos por nodo)

/** INFO:
 * Definición de nodo para B-tree.
 * Cada nodo puede almacenar hasta M-1 claves y M hijos.
 * El nodo puede ser hoja o interno.
 */
template <typename TK> struct Node {
    TK *keys;        // Arreglo dinámico de claves almacenadas en el nodo
    Node **children; // Arreglo dinámico de punteros a hijos
    int count;       // Número de claves actualmente en el nodo
    bool leaf;       // Verdadero si el nodo es hoja, falso si tiene hijos

    /** INFO:
     * Constructor que inicializa un nodo hoja con una lista de claves.
     * Inicializa los punteros a hijos en nullptr.
     */
    Node(initializer_list<TK> elements) {
        this->leaf = true;
        this->keys = new TK[M - 1];
        this->children = new Node<TK> *[M];
        this->count = 0;
        for (auto it = elements.begin(); it != elements.end(); ++it) {
            this->keys[this->count] = *it;
            this->children[this->count] = nullptr;
            this->count++;
        }
        this->children[this->count] = nullptr;
        for (int i = this->count + 1; i < M; ++i)
            this->children[i] = nullptr;
    }

    /** INFO:
     * Constructor que inicializa un nodo hoja a partir de un vector de claves.
     */
    Node(const std::vector<TK> &elements) {
        this->leaf = true;
        this->keys = new TK[M - 1];
        this->children = new Node<TK> *[M];
        this->count = 0;
        for (size_t idx = 0; idx < elements.size(); ++idx) {
            this->keys[this->count] = elements[idx];
            this->children[this->count] = nullptr;
            this->count++;
        }
        this->children[this->count] = nullptr;
        for (int i = this->count + 1; i < M; ++i)
            this->children[i] = nullptr;
    }

    /** INFO:
     * Enlaza un hijo en la posición index_child con los elementos dados.
     * Si se enlaza un hijo, el nodo deja de ser hoja.
     */
    void link_child(int index_child, initializer_list<TK> elements) {
        this->leaf = false; // Ya no es hoja si tiene hijos
        this->children[index_child] = new Node(elements);
    }

    /** INFO:
     * Destructor: libera la memoria de las claves y de los hijos
     * recursivamente.
     */
    ~Node() {
        delete[] keys;
        for (int i = 0; i < M; ++i) {
            if (children[i])
                delete children[i];
        }
        delete[] children;
    }
};

/** INFO:
 * Clase BTree: representa el árbol B de grado M.
 * Proporciona métodos para búsqueda, recorrido, construcción y verificación de
 * propiedades.
 */
template <typename T> class BTree {
    Node<T> *root; // Puntero a la raíz del árbol

  public:
    /** INFO:
     * Constructor: inicializa el árbol con una raíz opcional.
     */
    BTree(Node<T> *root = nullptr) { this->root = root; }

    /** INFO:
     * Destructor: libera la memoria del árbol recursivamente.
     */
    ~BTree() {
        if (root)
            delete root;
    }

    /** INFO:
     * Devuelve una representación en string del árbol en recorrido inorden
     * (ordenado). Útil para visualizar la estructura y contenido del árbol.
     */
    string toString() {
        string result = "";
        toString(root, result);
        if (!result.empty() && result.back() == ',')
            result.pop_back();
        return result;
    }

    /** INFO:
     * Busca una clave en el árbol B.
     * - Comienza desde la raíz y en cada nodo busca la posición adecuada.
     * - Si encuentra la clave en el nodo, retorna true.
     * - Si llega a un nodo hoja y no encuentra la clave, retorna false.
     * - Si no es hoja, desciende al hijo correspondiente y repite el proceso.
     * Complejidad: O(log n), donde n es el número de claves en el árbol.
     */
    bool search(T key) {
        Node<T> *node = root;
        while (node) {
            int i = 0;
            // Busca la posición adecuada para la clave dentro del nodo actual
            while (i < node->count && key > node->keys[i])
                i++;
            // Si encuentra la clave, regresa true
            if (i < node->count && key == node->keys[i])
                return true;
            // Si es hoja y no está la clave, retorna false
            if (node->leaf)
                return false;
            // Si no es hoja, baja al hijo correspondiente
            node = node->children[i];
        }
        return false;
    }

    /** INFO:
     * Busca todas las claves en el rango [begin, end] y las retorna en un
     * vector. Realiza un recorrido en orden, visitando solo los nodos y
     * subárboles necesarios.
     * - Si la clave está dentro del rango, la agrega al resultado.
     * - Solo recorre los hijos que puedan contener claves en el rango.
     * Complejidad: O(log n + k), donde k es la cantidad de claves en el rango.
     */
    vector<int> range_search(T begin, T end) {
        vector<int> res;
        range_search(root, begin, end, res);
        return res;
    }

    /** INFO:
     * Verifica que el árbol cumpla todas las propiedades de un B-tree de grado
     * M:
     * - Todos los nodos (excepto la raíz) tienen al menos ceil(M/2)-1 claves.
     * - Todos los nodos tienen a lo sumo M-1 claves.
     * - Todas las hojas están al mismo nivel.
     * - Las claves de cada nodo están ordenadas.
     * - Todos los hijos de un nodo existen (no hay punteros nulos entre hijos).
     * Retorna true si cumple todas las propiedades, false en caso contrario.
     */
    bool check_properties() {
        int leaf_level = -1;
        return check_properties(root, leaf_level, 0);
    }

    /** INFO:
     * Construye un B-tree óptimo ("lleno") a partir de un vector ordenado de
     * claves. Se agrupan las claves en nodos hoja de hasta M-1 elementos y
     * luego se agrupan estos nodos para formar los niveles superiores,
     * repitiendo hasta formar la raíz. Retorna un puntero al árbol generado.
     */
    static BTree *build_from_ordered_vector(vector<T> elements) {
        if (elements.empty())
            return new BTree(nullptr);

        // Construye el nivel hoja agrupando elementos de M-1 en M-1
        vector<Node<T> *> current_level;
        int n = elements.size();
        for (int i = 0; i < n; i += (M - 1)) {
            int end = min(i + (M - 1), n);
            vector<T> v(elements.begin() + i, elements.begin() + end);
            current_level.push_back(new Node<T>(v));
        }
        // Repite el proceso agrupando nodos hijos y formando padres, hasta
        // quedar solo la raíz
        while (current_level.size() > 1) {
            vector<Node<T> *> next_level;
            int sz = current_level.size();
            for (int i = 0; i < sz; i += M) {
                int end = min(i + M, sz);
                Node<T> *parent = new Node<T>({});
                parent->leaf = false;
                parent->count = end - i - 1;
                // Copia la primera clave de cada hijo (excepto el primero) como
                // separadores en el padre
                for (int j = i + 1; j < end; ++j)
                    parent->keys[j - i - 1] = current_level[j]->keys[0];
                // Enlaza los hijos al padre
                for (int j = i; j < end; ++j)
                    parent->children[j - i] = current_level[j];
                for (int j = end - i; j < M; ++j)
                    parent->children[j] = nullptr;
                next_level.push_back(parent);
            }
            current_level = next_level;
        }
        return new BTree(current_level[0]);
    }

  private:
    /** INFO:
     * (No utilizada en esta versión. Permite construir recursivamente a partir
     * de un vector ordenado.) Divide el rango en grupos de M-1 claves para los
     * nodos hoja, y agrupa en nodos padres.
     */
    static Node<T> *build_from_vector(const vector<T> &elems, int l, int r) {
        int n = r - l;
        if (n <= M - 1) {
            vector<T> v(elems.begin() + l, elems.begin() + r);
            return new Node<T>(v);
        }
        vector<Node<T> *> children;
        vector<T> keys;
        int curr = l;
        while (curr < r) {
            int next = min(curr + (M - 1), r);
            children.push_back(build_from_vector(elems, curr, next));
            if (next < r)
                keys.push_back(elems[next]);
            curr = next + 1;
        }
        Node<T> *node = new Node<T>({});
        node->leaf = false;
        node->count = keys.size();
        for (int i = 0; i < (int)keys.size(); ++i)
            node->keys[i] = keys[i];
        for (int i = 0; i < (int)children.size(); ++i)
            node->children[i] = children[i];
        for (int i = children.size(); i < M; ++i)
            node->children[i] = nullptr;
        return node;
    }

    /** INFO:
     * Recorre el árbol en inorden y agrega las claves al string result.
     * El recorrido en orden garantiza que las claves estén en orden creciente.
     */
    void toString(Node<T> *nodo, string &result) {
        if (!nodo)
            return;
        int i = 0;
        for (; i < nodo->count; i++) {
            if (!nodo->leaf)
                toString(nodo->children[i], result);
            result += std::to_string(nodo->keys[i]) + ",";
        }
        if (!nodo->leaf)
            toString(nodo->children[i], result);
    }

    /** INFO:
     * Busca las claves en el rango [begin, end] en el subárbol 'node'.
     * Solo recorre ramas que pueden contener claves en el rango.
     * - Si la clave actual está fuera del rango, ignora.
     * - Si está dentro, la agrega al resultado.
     * - Llama recursivamente a los hijos necesarios.
     */
    void range_search(Node<T> *node, T begin, T end, vector<int> &res) {
        if (!node)
            return;
        int i = 0;
        while (i < node->count && node->keys[i] < begin) {
            if (!node->leaf)
                range_search(node->children[i], begin, end, res);
            i++;
        }
        for (; i < node->count && node->keys[i] <= end; ++i) {
            if (!node->leaf)
                range_search(node->children[i], begin, end, res);
            if (node->keys[i] >= begin && node->keys[i] <= end)
                res.push_back(node->keys[i]);
        }
        if (!node->leaf)
            range_search(node->children[i], begin, end, res);
    }

    /** INFO:
     * Verifica recursivamente que el árbol cumple las propiedades del B-tree:
     * - Mínimo y máximo de claves por nodo (excepto raíz).
     * - Que los hijos existen si el nodo no es hoja.
     * - Que las claves están ordenadas estrictamente.
     * - Que todas las hojas están al mismo nivel.
     * Retorna true si cumple todas las propiedades, false si alguna falla.
     */
    bool check_properties(Node<T> *node, int &leaf_level, int curr_level) {
        if (!node)
            return true;
        int min_keys = (node == root) ? 1 : ((M % 2 == 0) ? M / 2 - 1 : M / 2);
        if (node->count < min_keys && node != root)
            return false;
        if (node->count > M - 1)
            return false;
        if (!node->leaf) {
            int children_cnt = 0;
            for (int i = 0; i <= node->count; ++i)
                if (node->children[i])
                    children_cnt++;
            if (children_cnt != node->count + 1)
                return false;
        }
        for (int i = 1; i < node->count; ++i)
            if (node->keys[i - 1] >= node->keys[i])
                return false;
        if (!node->leaf) {
            for (int i = 0; i <= node->count; ++i) {
                if (!node->children[i])
                    return false;
            }
        }
        if (node->leaf) {
            if (leaf_level == -1)
                leaf_level = curr_level;
            else if (curr_level != leaf_level)
                return false;
        }
        for (int i = 0; i <= node->count && !node->leaf; ++i)
            if (!check_properties(node->children[i], leaf_level,
                                  curr_level + 1))
                return false;
        return true;
    }
};

void test1() {
    Node<int> *root = new Node<int>({11, 16, 20, 31});
    root->link_child(0, {3, 5});
    root->link_child(1, {12, 15});
    root->link_child(2, {17, 19});
    root->link_child(3, {22, 25, 27, 28});
    root->link_child(4, {32, 36, 37, 38});
    BTree<int> *btree = new BTree<int>(root);

    cout << "Buscar 25: " << btree->search(25) << endl;
    cout << "Buscar 16: " << btree->search(16) << endl;
    cout << "Buscar 35: " << btree->search(35) << endl;

    cout << "Recorrido inorden: " << btree->toString() << endl;

    vector<int> result = btree->range_search(14, 20);
    cout << "Claves en el rango [14, 20]: ";
    for (auto elem : result)
        cout << elem << ", ";
    cout << endl;
    delete btree;
}

void test2() {
    Node<int> *root = new Node<int>({20});
    root->link_child(0, {11, 16});
    root->link_child(1, {31, 35});
    root->children[0]->link_child(0, {3, 5});
    root->children[0]->link_child(1, {12, 15});
    root->children[0]->link_child(2, {17, 19});
    root->children[1]->link_child(0, {22, 25, 27, 28});
    root->children[1]->link_child(1, {32, 33});
    root->children[1]->link_child(2, {36, 38});
    BTree<int> *btree = new BTree<int>(root);

    cout << "Buscar 25: " << btree->search(25) << endl;
    cout << "Buscar 16: " << btree->search(16) << endl;
    cout << "Buscar 37: " << btree->search(37) << endl;

    cout << "Recorrido inorden: " << btree->toString() << endl;

    vector<int> result = btree->range_search(14, 21);
    cout << "Claves en el rango [14, 21]: ";
    for (auto elem : result)
        cout << elem << ", ";
    cout << endl;
    delete btree;
}

void test3() {
    std::vector<int> elements = {1,  2,  3,  4,  5,  6,  7,  8,  9,  10,
                                 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    BTree<int> *btree = BTree<int>::build_from_ordered_vector(elements);
    if (btree->check_properties()) {
        cout << "El árbol cumple con las propiedades de un árbol B." << endl;
        cout << "Recorrido inorden: " << btree->toString() << endl;
    } else {
        cout << "El árbol no cumple con las propiedades de un árbol B." << endl;
    }
    delete btree;
}

int main() {
    cout << "Test 1" << endl;
    test1();
    cout << "Test 2" << endl;
    test2();
    cout << "Test 3" << endl;
    test3();
    return 0;
}

/** PERF: O(purr)
    /\__/\
  (>^ . ^<)
   (")(")_/
*/
