#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

namespace std {
    inline string to_string(const string& s) { return s; }
}

const int maxColision = 3;

template<typename TK, typename TV>
class HashIterator {
private:
    std::vector<std::pair<TK,TV>> seq;
    size_t pos;
public:
    HashIterator() : seq(), pos(0) {}
    HashIterator(const std::vector<std::pair<TK,TV>>& s, size_t p = 0)
        : seq(s), pos(p) {}

    HashIterator<TK,TV>& operator=(HashIterator<TK,TV> other) {
        seq = std::move(other.seq);
        pos = other.pos;
        return *this;
    }
    bool operator!=(HashIterator<TK,TV> o) const {
        return pos != o.pos;
    }
    HashIterator<TK,TV>& operator++() {
        ++pos;
        return *this;
    }
    std::pair<TK,TV> operator*() const {
        return seq[pos];
    }
};

template<typename TK, typename TV>
class HashTable {
public:
    typedef HashIterator<TK,TV> iterator;

    HashTable(int cap = 5)
        : capacity(cap), size_count(0), buckets(cap) {}

    iterator begin() {
        auto elems = getAllElements();
        return iterator(elems, 0);
    }
    iterator end() {
        auto elems = getAllElements();
        return iterator(elems, elems.size());
    }

    void insert(const TK& key, const TV& value) {
        size_t idx = bucketIndex(key);
        auto& bucket = buckets[idx];
        for (auto& kv : bucket) {
            if (kv.first == key) {
                kv.second = value;
                return;
            }
        }
        bucket.emplace_back(key, value);
        insertionOrder.push_back(key);
        ++size_count;
        if ((int)bucket.size() > maxColision) {
            rehash();
        }
    }
    void insert(const std::pair<TK,TV>& p) {
        insert(p.first, p.second);
    }

    TV& at(const TK& key) {
        size_t idx = bucketIndex(key);
        auto& bucket = buckets[idx];
        for (auto& kv : bucket) {
            if (kv.first == key) return kv.second;
        }
        throw std::out_of_range("Key not found");
    }

    TV& operator[](const TK& key) {
        if (!find(key)) insert(key, TV());
        return at(key);
    }

    bool find(const TK& key) const {
        size_t idx = bucketIndex(key);
        auto& bucket = buckets[idx];
        for (auto& kv : bucket) {
            if (kv.first == key) return true;
        }
        return false;
    }

    bool remove(const TK& key) {
        size_t idx = bucketIndex(key);
        auto& bucket = buckets[idx];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                auto vit = std::find(insertionOrder.begin(), insertionOrder.end(), key);
                if (vit != insertionOrder.end()) insertionOrder.erase(vit);
                --size_count;
                return true;
            }
        }
        return false;
    }

    int getSize() const {
        return size_count;
    }

    std::vector<TK> getAllKeys() {
        return insertionOrder;
    }

    std::vector<std::pair<TK,TV>> getAllElements() {
        std::vector<std::pair<TK,TV>> elems;
        elems.reserve(size_count);
        for (auto& k : insertionOrder) {
            elems.emplace_back(k, at(k));
        }
        return elems;
    }

private:
    int capacity;
    int size_count;
    std::vector<std::vector<std::pair<TK,TV>>> buckets;
    std::vector<TK> insertionOrder;

    size_t bucketIndex(const TK& key) const {
        return std::hash<TK>{}(key) % capacity;
    }

    void rehash() {
        auto elems = getAllElements();
        capacity *= 2;
        buckets.clear();
        buckets.resize(capacity);
        insertionOrder.clear();
        size_count = 0;
        for (auto& p : elems) insert(p);
    }
};

#endif
