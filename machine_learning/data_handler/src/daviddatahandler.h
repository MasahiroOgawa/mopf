#ifndef DAVIDDATAHANDLER_H
#define DAVIDDATAHANDLER_H
#include "datahandler.h"
#include <fstream>
#include <vector>

namespace mo {

class DavidDataHandler : public DataHandler<std::vector<double>,std::vector<double>>
{
public:
    DavidDataHandler();
    void read(const std::string& filename);
    const Matrix& X()const{return X_;}
    const Matrix& B()const{return B_;}

private:
    bool isEof(void) { return m_trainingDataFile.eof(); }
    void getTopology(std::vector<unsigned> &topology);

    // Returns the number of input values read from the file:
    unsigned getNextInputs(std::vector<double> &inputVals);
    unsigned getTargetOutputs(std::vector<double> &targetOutputVals);

    std::ifstream m_trainingDataFile;
    Matrix X_;
    Matrix B_;
};

} // namespace mo

#endif // DAVIDDATAHANDLER_H
