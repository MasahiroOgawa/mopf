#ifndef VECTOR_H
#define VECTOR_H
#include "matrix.h"

namespace mo {

class Vector : public Matrix{
public:
    Vector();
    Vector(const int n);
    ~Vector();
};

} //namespace mo
#endif // VECTOR_H
