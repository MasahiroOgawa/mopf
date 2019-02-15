#ifndef VECTOR_H
#define VECTOR_H
#include <numeric>
#include <opencv2/core.hpp>

namespace mo {
template<int n> using Vector = cv::Vec<double,n>; //opencv only support specific dimension vector.


/////////////////////////
/// \brief operator<<
/// operator overloading for output of vector<T>
/////////////////////////
template<typename T>
std::ostream& operator <<(std::ostream& os, const std::vector<T>& v){
    auto it=v.begin();
    os << "{" << *it++;
    for(; it!=v.end(); ++it) os << "," << *it;
    return os << "}";
}



/////////////////////////
/// \brief The DistanceType enum
/////////////////////////
enum class DistanceType{
    l2,
    cos,
};

/////////////////////////
/// \brief l2norm
/// \param v1
/// \param v2
/// \return
/////////////////////////
template<typename T>
double l2norm(const std::vector<T>& v1, const std::vector<T>& v2);


/////////////////////////
/// \brief cosnorm
/// \param v1
/// \param v2
/// \return cosine distance = angle distance
/////////////////////////
template<typename T>
double cosnorm(const std::vector<T>& v1, const std::vector<T>& v2);


/////////////////////////
/// \brief norm
/// \param v1
/// \return
/////////////////////////
template<typename T>
double norm(const std::vector<T>& v);


/////////////////////////
/// \brief distance
/// \param v1
/// \param v2
/// \return norm of 2 stl vectors
/////////////////////////
template<typename T>
double distance(const std::vector<T>& v1, const std::vector<T>& v2, const DistanceType dt = DistanceType::l2){
    if(v1.size() != v2.size()){
        std::stringstream errmsg;
        errmsg << "v1.size:" << v1.size() << " must be equal with v2.size:" << v2.size()
               << " @distance()";
        throw std::runtime_error(errmsg.str());
    }

    switch (dt) {
    case DistanceType::l2:
        return l2norm<T>(v1, v2);
    case DistanceType::cos:
        return cosnorm<T>(v1, v2);
    default:
        throw std::invalid_argument("unknown distance type @distance()");
    }
}


//-------------------------------------
template<typename T>
double l2norm(const std::vector<T>& v1, const std::vector<T>& v2){
    double dist{0}; //no implicit constructor for double
    for(size_t i=0; i<v1.size(); ++i){
        dist += (v1[i] - v2[i]) * (v1[i] - v2[i]);
    }

    return sqrt(dist);
}


//-------------------------------------
template<typename T>
double cosnorm(const std::vector<T>& v1, const std::vector<T>& v2){
    return 1 - std::inner_product(v1.begin(), v1.end(), v2.begin(), 0.0) / (norm(v1) * norm(v2));
}


//-------------------------------------
template<typename T>
double norm(const std::vector<T>& v){
    return sqrt(std::inner_product(v.begin(), v.end(), v.begin(), 0.0));
}

} // namespace mo
#endif // VECTOR_H
