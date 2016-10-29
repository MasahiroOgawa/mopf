#include "knearestneighbor.h"

using namespace std;

namespace mo {
KNearestNeighbor::KNearestNeighbor()
{

}

void KNearestNeighbor::init(const Datatype dt){
    dh_.init(dt);
    dh_.read();
}

} // namespace mo

