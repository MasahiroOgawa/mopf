#ifndef MNISTDATAHANDLER_H
#define MNISTDATAHANDLER_H
#include "datahandler.h"
#include "../../../ext/mnist/mnist_reader.hpp"

namespace mo{
class MnistDataHandler : public DataHandler
{
public:
    MnistDataHandler();
    void read(const std::string& datadir = "");
    void show_traindata();

private:
    mnist::MNIST_dataset<std::vector, std::vector<uint8_t>, uint8_t> dataset_;
};
} // namespace mo

#endif // MNISTDATAHANDLER_H
