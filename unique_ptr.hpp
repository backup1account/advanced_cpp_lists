#ifndef CPP_UNIQUE_PTR_HPP
#define CPP_UNIQUE_PTR_HPP

namespace cpplab {
    template<typename T>
    class unique_ptr;
}

template<typename T>
class cpplab::unique_ptr {
    public:
    unique_ptr(T *ptr = nullptr) : m_ptr(ptr) {}
    ~unique_ptr() { delete m_ptr; }

    T *release() {
        T *ptr = m_ptr;
        m_ptr = nullptr;
        return ptr;
    }

    void reset(T *ptr = nullptr) {
        delete m_ptr;
        m_ptr = ptr;
    }

    T *get() const { return m_ptr; }

    T &operator*() const { return *m_ptr; }
    T *operator->() const { return m_ptr; }

    private:
    T *m_ptr;

    unique_ptr(const unique_ptr &) = delete;
    unique_ptr &operator=(const unique_ptr &) = delete;
};

#endif