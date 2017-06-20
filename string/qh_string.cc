#include "qh_string.h"

#include <string.h>

namespace qh
{
    // TODO 将在这里写实现代码

    string::string()
        : data_(NULL), len_(0)
    {
    }

    string::string( const char* s )
    {
        if (s == NULL) {
            data_ = NULL;
            len_ = 0;
        } else {
            len_ = 0;
            while (*(s+len_) != 0)
                len_++;
            if (len_ == 0)
                data_ = NULL;
            else {
                this->data_ = new char[len_+1];
                for (size_t i=0; i<len_; ++i)
                    data_[i] = *(s+i);
                data_[len_] = 0;
            }
        }
    }

    string::string( const char* s, size_t len )
    {
        if (s == NULL || len == 0) {
            data_ = NULL;
            len_ = 0;
        } else {
            len_ = len;
            this->data_ = new char[len_+1];
            for (size_t i=0; i<len_; ++i)
                data_[i] = *(s+i);
            data_[len_] = 0;
        }
    }

    string::string( const string& rhs )
    {
        if (rhs.data_ == NULL || rhs.len_ == 0) {
            data_ = NULL;
            len_ = 0;
        } else {
            len_ = rhs.len_;
            data_ = new char[len_+1];
            for (size_t i=0; i<len_; ++i)
                data_[i] = rhs.data_[i];
            data_[len_] = 0;
        }
    }

    string& string::operator=( const string& rhs )
    {
        if (this != &rhs)
        {
            if (rhs.data_ == NULL || rhs.len_ == 0)
            {
                data_ = NULL;
                len_ = 0;
            }
            else
            {
                char *nd = new char[rhs.len_+1];
                for (size_t i=0; i<rhs.len_; ++i)
                    nd[i] = rhs.data_[i];
                nd[rhs.len_] = 0;
                delete [] data_;
                len_ = rhs.len_;
                data_ = nd;
            }
        }
        return *this;
    }

    string::~string()
    {
        if (data_ != NULL)
            delete[] data_;
    }

    size_t string::size() const
    {
        return len_;
    }

    const char* string::data() const
    {
        return data_;
    }

    const char* string::c_str() const
    {
        return data_;
    }

    char* string::operator[]( size_t index )
    {
        if (index >= len_)
            return NULL;
        else
            return data_ + index;
    }
}
