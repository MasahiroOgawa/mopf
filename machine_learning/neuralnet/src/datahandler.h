#ifndef DATAHANDLER_H
#define DATAHANDLER_H
#include <string>
#include <opencv2/core.hpp>

class DataHandler
{
public:
    enum DataType{
        David=1,
        Iris,
    };
    DataHandler();
    virtual void read(const std::string& filename)=0; //pure virtual function; must be implemented in derived classes.
    const cv::Mat& X()const{return X_;}
    const cv::Mat& B()const{return B_;}
    virtual ~DataHandler(){}
protected:
    cv::Mat X_; //data vectors; X_=(x1,...,xn)
    cv::Mat B_; //instruction signals; B_=(b1,...,bn), bi is a vector.
    unsigned datadim_; //feature dimension(xi's dim)
};

DataHandler* create_handler(const DataHandler::DataType data_type);
#endif // DATAHANDLER_H
