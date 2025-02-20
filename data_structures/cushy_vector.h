// Static array on heap

#ifndef CUSHY_VECTOR
#define CUSHY_VECTOR

template <typename T, typename SizeType = size_t>
class CushyVector
{
private:
    T *data;
    SizeType size;

public:
    explicit CushyVector(SizeType size) : size(size) { data = new T[size]; }
    CushyVector(const CushyVector &original) : data(nullptr) { *this = original; }
    CushyVector(CushyVector &&original) { *this = original; }
    ~CushyVector() { delete[] data; }
    T *begin() { return data; }
    T *end() { return data + size; }
    const T *begin() const { return data; }
    const T *end() const { return data + size; }
    SizeType getSize() const { return size; }

    CushyVector &operator=(const CushyVector &original)
    {
        size = original.size;
        delete[] data;
        data = new T[size];
        for(SizeType i = 0; i < size; i++)
            data[i] = original.data[i];
        return *this;
    }

    CushyVector &operator=(CushyVector &&original)
    {
        delete[] data;
        data = original.data;
        original.data = nullptr;
        size = original.size;
        return *this;
    }

    bool operator==(const CushyVector &original)
    {
        if(size != original.size)
            return false;
        for(SizeType i = 0; i < size; i++)
            if(data[i] != original.data[i])
                return false;
        return true;
    }

    bool operator!=(const CushyVector &original) { return !(*this == original); }
};

#endif //CUSHY_VECTOR
