#ifndef DATAHANDLER_H
#define DATAHANDLER_H
#include "../../../ext/mnist/mnist_reader.hpp"

namespace mo {
enum class Datatype{mnist};

class DataHandler
{
public:
    DataHandler(const Datatype dt = Datatype::mnist);
    void init(const Datatype dt);
    void read();
private:
    Datatype dt_;
    mnist::MNIST_dataset<std::vector, std::vector<uint8_t>, uint8_t> mnist_data_;
};
} // namespace mo

#endif // DATAHANDLER_H
