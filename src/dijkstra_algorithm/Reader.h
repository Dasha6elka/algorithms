#ifndef ALGORITHMS_READER_H
#define ALGORITHMS_READER_H


template<typename T>
class Reader
{
public:
    virtual const T &get() = 0;
};


#endif //ALGORITHMS_READER_H
