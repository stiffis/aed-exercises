// author: stiffis

#include <iostream>
#include <queue>
#include <stack>

template <typename T> class NodeL {
  public:
    T data;
    NodeL *next;
    NodeL(T val) : data(val), next(nullptr) {}
};

template <typename T> class LinkedList {
  private:
    NodeL<T> *head;
    NodeL<T> *tail;

  public:
    LinkedList() : head(nullptr), tail(nullptr) {}

    void append(T val) {
        NodeL<T> *newNode = new NodeL<T>(val);
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void print() {
        NodeL<T> *current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

template <typename T> struct Node {
    T data;
    Node *left;
    Node *right;
    Node(T value) : data(value), left(nullptr), right(nullptr) {}
};

template <typename T> class BST {
  private:
    Node<T> *root;
    Node<T> *insertNodeAux(Node<T> *node, T value) {
        if (node == nullptr) {
            return new Node<T>(value);
        }
        if (value < node->data) {
            node->left = insertNodeAux(node->left, value);
        } else if (value > node->data) {
            node->right = insertNodeAux(node->right, value);
        }
        return node;
    }
    Node<T> *searchNodeAux(Node<T> *node, T value) {
        if (node == nullptr || node->data == value) {
            return node;
        }
        if (value < node->data) {
            return searchNodeAux(node->left, value);
        } else {
            return searchNodeAux(node->right, value);
        }
    }
    void inOrderAux(Node<T> *node) {
        if (node == nullptr) {
            return;
        }
        inOrderAux(node->left);
        std::cout << node->data << " "; // INFO: Print the data
        inOrderAux(node->right);
    }
    void preOrderAux(Node<T> *node) {
        if (node == nullptr) {
            return;
        }
        std::cout << node->data << " "; // INFO: Print the data
        preOrderAux(node->left);
        preOrderAux(node->right);
    }
    void postOrderAux(Node<T> *node) {
        if (node == nullptr) {
            return;
        }
        postOrderAux(node->left);
        postOrderAux(node->right);
        std::cout << node->data << " "; // INFO: Print the data
    }
    void deleteTreeAux(Node<T> *node) {
        if (node == nullptr) {
            return;
        }
        deleteTreeAux(node->left);
        deleteTreeAux(node->right);
        delete node;
    }
    int sizeAux(Node<T> *node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + sizeAux(node->left) + sizeAux(node->right);
    }
    int heightAux(Node<T> *node) {
        if (node == nullptr) {
            return -1; // Height of an empty tree is -1
        }
        int leftHeight = heightAux(node->left);
        int rightHeight = heightAux(node->right);
        return 1 + std::max(leftHeight, rightHeight);
    }
    T minValueAux(Node<T> *node) {
        if (node == nullptr) {
            return T(); // Return default value if tree is empty
        }
        Node<T> *current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current->data;
    }
    T maxValueAux(Node<T> *node) {
        if (node == nullptr) {
            return T(); // Return default value if tree is empty
        }
        Node<T> *current = node;
        while (current && current->right != nullptr) {
            current = current->right;
        }
        return current->data;
    }
    T SuccessorAux(Node<T> *node,
                   T value) { // INFO: Find the successor of a node in order
        Node<T> *current = searchNodeAux(node, value);
        if (current == nullptr) {
            return T(); // Return default value if not found
        }
        if (current->right != nullptr) {
            return minValueAux(current->right);
        }
        Node<T> *successor = nullptr;
        Node<T> *ancestor = node;
        while (ancestor != current) {
            if (current->data < ancestor->data) {
                successor = ancestor;
                ancestor = ancestor->left;
            } else {
                ancestor = ancestor->right;
            }
        }
        return successor ? successor->data : T();
    }
    T PredecessorAux(Node<T> *node,
                     T value) { // INFO: Find the predecessor of a node in order
        Node<T> *current = searchNodeAux(node, value);
        if (current == nullptr) {
            return T(); // Return default value if not found
        }
        if (current->left != nullptr) {
            return maxValueAux(current->left);
        }
        Node<T> *predecessor = nullptr;
        Node<T> *ancestor = node;
        while (ancestor != current) {
            if (current->data > ancestor->data) {
                predecessor = ancestor;
                ancestor = ancestor->right;
            } else {
                ancestor = ancestor->left;
            }
        }
        return predecessor ? predecessor->data : T();
    }
    Node<T> *parentAux(Node<T> *node,
                       T value) { // INFO: Find the parent of a node
        if (!node)
            return nullptr; // árbol vacío

        if (node->left && node->left->data == value) {
            return node; // padre encontrado
        }
        if (node->right && node->right->data == value) {
            return node; // padre encontrado
        }
        return value < node->data ? parentAux(node->left, value)
                                  : parentAux(node->right, value);
    }
    bool isBalancedAux(Node<T> *node) {
        if (node == nullptr) {
            return true;
        }
        int balanceFactor = abs(heightAux(node->left) - heightAux(node->right));
        if (balanceFactor > 1) {
            return false;
        }
        return isBalancedAux(node->left) && isBalancedAux(node->right);
    }
    void deleteNodeAux(Node<T> *&root, T value) {
        if (root == nullptr)
            return; // árbol vacío

        if (value < root->data) { // buscar a la izquierda
            deleteNodeAux(root->left, value);
        } else if (value > root->data) { // buscar a la derecha
            deleteNodeAux(root->right, value);
        } else { // ---- nodo encontrado ----
            // 1. Hoja
            if (!root->left && !root->right) {
                delete root;
                root = nullptr;
            }
            // 2. Solo hijo derecho
            else if (!root->left) {
                Node<T> *tmp = root;
                root = root->right;
                delete tmp;
            }
            // 3. Solo hijo izquierdo
            else if (!root->right) {
                Node<T> *tmp = root;
                root = root->left;
                delete tmp;
            }
            // 4. Dos hijos
            else {
                // Tomamos el sucesor (mínimo del subárbol derecho)
                Node<T> *succ = root->right;
                while (succ->left)
                    succ = succ->left;

                root->data = succ->data; // copiamos dato
                deleteNodeAux(root->right,
                              succ->data); // borramos sucesor duplicado
            }
        }
    }
    void BFS(Node<T> *node) {
        if (node == nullptr) {
            return;
        }
        std::queue<Node<T> *> q;
        q.push(node);
        while (!q.empty()) {
            Node<T> *current = q.front();
            q.pop();
            std::cout << current->data << " ";
            if (current->left != nullptr) {
                q.push(current->left);
            }
            if (current->right != nullptr) {
                q.push(current->right);
            }
        }
    }
    void DFS(Node<T> *node) {
        if (node == nullptr) {
            return;
        }
        std::stack<Node<T> *> s;
        s.push(node);
        while (!s.empty()) {
            Node<T> *current = s.top();
            s.pop();
            std::cout << current->data << " ";
            if (current->right != nullptr) {
                s.push(current->right);
            }
            if (current->left != nullptr) {
                s.push(current->left);
            }
        }
    }
    Node<T> *buildBSTAux(Node<T> *node, T arr[], int star, int end) {
        if (star > end) {
            return nullptr;
        }
        int middle = (star + end) / 2;
        Node<T> *newNode = new Node<T>(arr[middle]);
        newNode->left = buildBSTAux(node, arr, star, middle - 1);
        newNode->right = buildBSTAux(node, arr, middle + 1, end);
        return newNode;
    }
    void printTreeAux(Node<T> *node, int space) {
        if (node == nullptr) {
            return;
        }
        space += 10;
        printTreeAux(node->right, space);
        std::cout << std::endl;
        for (int i = 10; i < space; i++) {
            std::cout << " ";
        }
        std::cout << node->data << "\n";
        printTreeAux(node->left, space);
    }
    class iterator { // INFO: Iterator class for in-order traversal
      private:
        Node<T> *current;
        std::stack<Node<T> *> stack;

      public:
        iterator(Node<T> *root) {
            current = root;
            while (current != nullptr) {
                stack.push(current);
                current = current->left;
            }
        }
        bool hasNext() { return !stack.empty(); }
        T next() {
            if (!hasNext()) {
                throw std::out_of_range("No more elements");
            }
            Node<T> *node = stack.top();
            stack.pop();
            current = node->right;
            while (current != nullptr) {
                stack.push(current);
                current = current->left;
            }
            return node->data;
        }
        iterator operator++() {
            next();
            return *this;
        }
        T operator*() {
            if (!hasNext()) {
                throw std::out_of_range("No more elements");
            }
            return stack.top()->data;
        }
        bool operator!=(const iterator &other) {
            return current != other.current;
        }
        bool operator==(const iterator &other) {
            return current == other.current;
        }
    };

  public:
    Node<T> *getRoot() { return root; }
    void insertNode(T value) { root = insertNodeAux(root, value); }
    Node<T> *searchNode(T value) { return searchNodeAux(root, value); }
    void inOrder() {
        inOrderAux(root);
        std::cout << std::endl;
    }
    void preOrder() {
        preOrderAux(root);
        std::cout << std::endl;
    }
    void postOrder() {
        postOrderAux(root);
        std::cout << std::endl;
    }
    int size() { return sizeAux(root); }
    int height() { return heightAux(root); }
    T minValue() { return minValueAux(root); }
    T maxValue() { return maxValueAux(root); }
    Node<T> *successor(T value) {
        return searchNode(SuccessorAux(root, value));
    }
    Node<T> *predecessor(T value) {
        return searchNode(PredecessorAux(root, value));
    }
    Node<T> *parent(T value) { return parentAux(root, value); }
    bool isBalanced() { return isBalancedAux(root); }
    void deleteNode(T value) { deleteNodeAux(root, value); }
    void deleteTree() {
        deleteTreeAux(root);
        root = nullptr;
    }
    void BFS() {
        BFS(root);
        std::cout << std::endl;
    }
    void DFS() {
        DFS(root);
        std::cout << std::endl;
    }
    void buildBST(T arr[], int size) {
        if (size <= 0) {
            std::cout << "Array is empty." << std::endl;
            return;
        }
        this->root = buildBSTAux(root, arr, 0, size - 1);
    }
    void printTree() {
        printTreeAux(root, 0);
        std::cout << std::endl;
    }
    iterator begin() { return iterator(root); }
    iterator end() { return iterator(nullptr); }
    BST() : root(nullptr) {}
    ~BST() { deleteTree(); }
};

// INFO: FUNCTION TO LIKEDLIST TO BST BALANCED
template <typename T> void linkToBST(LinkedList<T> &list, BST<T> &bst) {
    NodeL<T> *current = list.head;
    T *arr = new T[list.size()];
    int i = 0;
    while (current) {
        arr[i++] = current->data;
        current = current->next;
    }
    bst.buildBST(arr, list.size());
    delete[] arr;
}
