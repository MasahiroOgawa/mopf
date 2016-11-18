#ifndef IRISDATAHANDLER_H
#define IRISDATAHANDLER_H
#include "datahandler.h"
#include <map>

namespace mo {

class IrisDataHandler : public DataHandler<std::vector<double>, std::vector<double>>
{
public:
    IrisDataHandler();
    void read(const std::string& filename);
    const Matrix& X()const{return X_;}
    const Matrix& B()const{return B_;}

private:
    std::map<std::string,cv::Mat> cls_map_;
    Matrix X_;
    Matrix B_;
};

} // namespace mo

#endif // IRISDATAHANDLER_H
