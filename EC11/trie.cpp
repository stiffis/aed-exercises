#include <iostream>
#include <string>
#include <unordered_map>

struct TrieNode {
    std::unordered_map<char, TrieNode *> children;
    bool endOfWord;

    TrieNode() : endOfWord(false) {}
    ~TrieNode() {
        for (auto &pair : children) {
            delete pair.second;
        }
    }
};

class Trie {
    TrieNode *root;

  public:
    Trie() : root(new TrieNode) {}
    ~Trie() { delete root; }

    void insert(const std::string &word) {
        TrieNode *node = root;
        for (char c : word) {
            if (!node->children.count(c)) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        node->endOfWord = true;
    }

    bool search(const std::string &word) const {
        TrieNode *node = root;
        for (char c : word) {
            if (!node->children.count(c))
                return false;
            node = node->children.at(c);
        }
        return node->endOfWord;
    }

    bool startsWith(const std::string &prefix) const {
        TrieNode *node = root;
        for (char c : prefix) {
            if (!node->children.count(c))
                return false;
            node = node->children.at(c);
        }
        return true;
    }
};

void test1() {
    Trie *trie = new Trie();
    trie->insert("apple");
    std::cout << trie->search("apple");
    std::cout << trie->search("app");
    std::cout << trie->startsWith("app");
    trie->insert("app");
    std::cout << trie->search("app");
    delete trie;
}

void test2() {
    Trie *trie = new Trie();
    trie->insert("apple");
    trie->insert("banana");
    trie->insert("bandana");
    trie->insert("band");
    std::cout << trie->search("banana");
    std::cout << trie->search("ban");
    std::cout << trie->startsWith("ban");
    trie->insert("ban");
    std::cout << trie->search("ban");
    delete trie;
}

int main() {
    test1();
    test2();
    return 0;
}
