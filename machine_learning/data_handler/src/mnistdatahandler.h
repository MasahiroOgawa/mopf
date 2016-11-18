#ifndef MNISTDATAHANDLER_H
#define MNISTDATAHANDLER_H
#include "datahandler.h"
#include "../../../ext/mnist/src/mnist_reader.hpp"
#include "../../../image/src/image.h"
#include "../../../visualization/src/visualization.h"

namespace mo{

class MnistDataHandler : public DataHandler<std::vector<unsigned char>, unsigned char>
{
public:
    MnistDataHandler(){}
    void read(const std::string& datadir);

    //////////////////
    /// \brief show
    /// \param datum
    /// \return pushed key
    //////////////////
    char show(const std::vector<unsigned char>& datum, const std::string& winname="mnist image");

    void show_traindata();
    const Matrix& X()const;
    const Matrix& B()const;
};

} // namespace mo

#endif // MNISTDATAHANDLER_H
