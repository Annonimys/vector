#include <iostream>

class Array
{
public:
    Array(std::ostream &ostream)
        : Ostream_(ostream), size_(0), capacity_(2), data_(new int[capacity_])
    {
        Ostream_ << "Constructed. " << *this << std::endl;
    }

    Array(const Array &array)
        : Ostream_(array.Ostream_), size_(array.size_), capacity_(array.capacity_), data_(new int[capacity_])
    {
        CopyData(array.data_, data_);

        Ostream_ << "Constructed from another Array. " << *this << std::endl;
    }

    Array(size_t size, std::ostream &ostream = std::cout, int defaultValue = 0)
        : Ostream_(ostream), size_(size), capacity_(size_ * 2), data_(new int[capacity_])
    {

        for (size_t i = 0; i != size_; ++i)
        {
            data_[i] = defaultValue;
        }

        Ostream_ << "Constructed with default. " << *this << std::endl;
    }

    ~Array()
    {
        delete[] data_;

        Ostream_ << "Destructed " << size_ << std::endl;
    }

    size_t Size() const
    {
        return size_;
    }

    size_t Capacity() const
    {
        return capacity_;
    }

    void Reserve(size_t newCapacity)
    {
        if (newCapacity > capacity_) {
            int *newdata = new int[newCapacity];

            CopyData(data_, newdata);
            delete[] data_;

            capacity_ = newCapacity;
            data_ = newdata;
        }
    }

    void Resize(size_t newSize)
    {

        if (capacity_ < newSize) {
            capacity_ = newSize;

            int *newdata = new int[capacity_];
            CopyData(data_, newdata);
            delete[] data_;

            data_ = newdata;
        }

        size_ = newSize;
    }

    void PushBack(int value = 0)
    {
        if (size_ == capacity_)
        {
            Reserve(size_ * 2);
        }
        data_[size_] = value;
        ++size_;
    }

    void PopBack()
    {
        --size_;
    }

    const int &operator[](const size_t i) const
    {
        return const_cast<Array *>(this)->operator[](i);
    }

    int &operator[](const size_t i)
    {
        return data_[i];
    }

    explicit operator bool() const
    {
        return size_ != 0;
    }

    bool operator<(const Array &it) const
    {
        if (size_ < it.size_)
        {
            for (size_t i = 0; i != size_; ++i)
            {
                if (it.data_[i] >= data_[i])
                {
                    return false;
                }
            }
            return true;
        }

        for (size_t i = 0; i != it.size_; ++i)
        {
            if (data_[i] < it.data_[i])
            {
                return true;
            }
        }
        return false;
    }

    bool operator>(const Array &it) const
    {
        return it < *this;
    }

    bool operator!=(const Array &it) const
    {
        return (*this < it) || (it < *this);
    }

    bool operator==(const Array &it) const
    {
        return !(*this != it);
    }

    bool operator<=(const Array &it) const
    {
        return (*this < it) || (*this == it);
    }

    bool operator>=(const Array &it) const
    {
        return !(*this < it);
    }

    Array &operator<<(const int value)
    {
        PushBack(value);
        return *this;
    }

    Array &operator<<(const Array &it)
    {
        if (capacity_ < size_ + it.size_)
            Reserve(size_ + it.size_);

        for (size_t i = 0; i != it.size_; ++i)
        {
            data_[size_] = it.data_[i];
            ++size_;
        }

        return *this;
    }

    friend std::ostream &operator<<(std::ostream &ostream, const Array &array);

private:
    std::ostream &Ostream_;
    size_t size_, capacity_;

    int *data_;

    void CopyData(int *source, int *fresh)
    {
        for (size_t i = 0; i != size_; ++i)
        {
            fresh[i] = source[i];
        }
    }
};

std::ostream &operator<<(std::ostream &ostream, const Array &array)
{
    ostream << "Result Array's capacity is " << array.capacity_ << " and size is " << array.size_;
    if (array.size_ != 0)
    {
        ostream << ", elements are: ";

        size_t i = 0;
        for (; i + 1 != array.size_; ++i)
        {
            ostream << array[i] << ", ";
        }
        ostream << array[i];
    }
    return ostream;
}