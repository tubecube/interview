#ifndef QIHOO_VECTOR_H_
#define QIHOO_VECTOR_H_

#include <iostream>

namespace qh
{
    template<class T>
    class vector {
    public:
        //ctor
        vector()
            : data_(NULL), size_(0), capacity_(0)
        {
        }

        explicit vector( size_t n, const T& value = T())
        {
            data_ = new T[n];
            for (size_t i = 0; i < n; i++)
            {
                data_[i] = value;
            }
            size_ = n;
            capacity_ = n;
        }

        vector<T>& operator=(const vector<T>& rhs)
        {
            if (this != &rhs)
            {
                T* nd = new T[rhs.capacity_];
                for (size_t i = 0; i < rhs.size_; ++i)
                {
                    nd[i] = rhs.data_[i];
                }
                delete [] this->data_;
                data_ = nd;
                size_ = rhs.size_;
                capacity_ = rhs.capacity_;
            }
            return *this;
        }

        //dtor
        ~vector()
        {
            if (data_)
            {
                delete[] data_;
            }
        }

        //get
        size_t size() const
        {
            return size_;
        }

        // set & get
        T& operator[](size_t index);

        // set
        void push_back(const T& element);
        void pop_back();
        void resize(size_t n, const T& value = T());
        void reserve(size_t n);
        void clear();

        size_t size()
        {
            return size_;
        }

        size_t capacity()
        {
            return capacity_;
        }

        // test if empty
        bool empty() const;

    private:
        T*      data_;
        size_t  size_;
        size_t  capacity_;
    };

    template<class T>
    T& vector<T>::operator[](size_t index)
    {
        if (index >= size_) {
            std::cout << "out of range!" << std::endl;
            exit(-1);
        }
        return data_[index];
    }

    template<class T>
    void vector<T>::push_back(const T& element)
    {
        if (size_ == capacity_)
            reserve(capacity_ == 0 ? 1 : 2*capacity_);
        assert(capacity_ > size_);
        data_[size_] = element;
        size_++;
    }

    template<class T>
    void vector<T>::pop_back()
    {
        size_--;
    }

    template<class T>
    void vector<T>::resize(size_t n, const T& value)
    {
        if (n > size_)
        {
            reserve(n);
            for (size_t i = size_; i < n; ++i)
            {
                data_[i] = value;
            }
        }
        size_ = n;
    }

    template<class T>
    void vector<T>::reserve(size_t n)
    {
        if (n > capacity_)
        {
            T* d = new T[n];
            for (size_t i = 0; i < size_; ++i)
            {
                d[i] = data_[i];
            }
            delete[] data_;
            data_ = d;
            capacity_ = n;
        }
    }

    template<class T>
    void vector<T>::clear()
    {
        size_ = 0;
    }

    template<class T>
    bool vector<T>::empty() const
    {
        return size_ == 0;
    }
}

#endif


