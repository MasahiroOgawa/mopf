#ifndef IRISDATAHANDLER_H
#define IRISDATAHANDLER_H
#include "datahandler.h"
#include <map>


class IrisDataHandler : public DataHandler
{
public:
    IrisDataHandler();
    void read(const std::string& filename);
private:
    std::map<std::string,cv::Mat> cls_map_;
};

#endif // IRISDATAHANDLER_H
