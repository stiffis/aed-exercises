template <typename T> struct NodeAVL {
    T data;
    int height;
    NodeAVL *left;
    NodeAVL *right;
    NodeAVL() : left(nullptr), right(nullptr), height(0) {}
    NodeAVL(T value) : data(value), left(nullptr), right(nullptr), height(0) {}

    void killSelf() {
        if (left != nullptr)
            left->killSelf();
        if (right != nullptr)
            right->killSelf();
        delete this;
    }
};
