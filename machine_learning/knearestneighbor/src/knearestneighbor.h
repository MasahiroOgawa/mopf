#ifndef KNEARESTNEIGHBOR_H
#define KNEARESTNEIGHBOR_H
#include "../../data_handler/src/datahandler.h"

namespace mo {
class KNearestNeighbor
{
public:
    KNearestNeighbor();
    void init(const Datatype dt = Datatype::mnist);
    void eval();
    void classify();
private:
    DataHandler dh_;
};

} // namespace mo

#endif // KNEARESTNEIGHBOR_H
