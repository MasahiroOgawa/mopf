#ifndef ANALYSIS_H
#define ANALYSIS_H

namespace mo {


///////////////////////////////
/// \brief sgn
/// return sign of the value
///////////////////////////////
template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

} //namespace mo

#endif
