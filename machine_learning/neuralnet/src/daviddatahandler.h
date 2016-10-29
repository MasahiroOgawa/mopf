#ifndef DAVIDDATAHANDLER_H
#define DAVIDDATAHANDLER_H
#include "datahandler.h"
#include <fstream>
#include <vector>

class DavidDataHandler : public DataHandler
{
public:
    DavidDataHandler();
    void read(const std::string& filename);
    bool isEof(void) { return m_trainingDataFile.eof(); }
    void getTopology(std::vector<unsigned> &topology);

    // Returns the number of input values read from the file:
    unsigned getNextInputs(std::vector<double> &inputVals);
    unsigned getTargetOutputs(std::vector<double> &targetOutputVals);

private:
    std::ifstream m_trainingDataFile;
};

#endif // DAVIDDATAHANDLER_H
