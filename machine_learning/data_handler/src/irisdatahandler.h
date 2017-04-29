#ifndef IRISDATAHANDLER_H
#define IRISDATAHANDLER_H
#include "datahandler.h"
#include <map>

namespace mo {

class IrisDataHandler : public DataHandler<std::vector<double>, double>
{
public:
    IrisDataHandler();
    void read(const std::string& datadir);
    char show(const std::vector<double>& datum, const std::string& winname="iris"){return '0';} // do not implement because we assume
    void show_traindata();

private:
    std::map<std::string,cv::Mat> cls_map_;
};

} // namespace mo

#endif // IRISDATAHANDLER_H
