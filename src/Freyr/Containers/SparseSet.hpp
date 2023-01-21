#pragma once

#include <algorithm>
#include <iterator>
#include <mutex>
#include <vector>

template<typename T>
class SparseSet
{
  public:
    SparseSet(unsigned capacity = 512u)
    {
        dense.reserve(capacity);
        sparse.resize(capacity);
        sorted = false;
    }

    ~SparseSet() = default;

    void insert(T n)
    {
        if (contains(n)) return;
        std::lock_guard<std::mutex> lock{m_lock};

        sparse[n] = (T)dense.size();
        dense.push_back(n);
        sorted = false;
    }

    void remove(T n)
    {
        if (!contains(n)) return;
        std::lock_guard<std::mutex> lock{m_lock};

        dense[sparse[n]]                = dense[dense.size() - 1];
        sparse[dense[dense.size() - 1]] = sparse[n];
        sparse[n]                       = 0;
        dense.pop_back();
        sorted = false;
    }

    bool contains(T n) const { return sparse[n] < dense.size() && dense[sparse[n]] == n; }

    void clear() { dense.clear(); }

    void resize(unsigned size)
    {
        dense.reserve(size);
        sparse.resize(size);
    }

    void sort()
    {
        if (sorted) return;
        std::lock_guard<std::mutex> lock{m_lock};
        denseSort();

        sparseReorder();
        sorted = true;
    }

    T &operator[](int index) { return dense[index]; };

    size_t size() { return dense.size(); }

    auto begin() const { return dense.rbegin(); }

    auto end() const { return dense.rend(); }

  protected:
    FREYR_SPEC void denseSort() { std::sort(dense.begin(), dense.end()); }

    FREYR_SPEC void sparseReorder()
    {
        for (T i = 0; i < dense.size(); i++)
        {
            sparse[dense[i]] = i;
        }
    }

  private:
    std::mutex m_lock;
    std::vector<T> dense;
    std::vector<T> sparse;
    bool sorted;
};
