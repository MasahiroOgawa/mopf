#include "daviddatahandler.h"
#include <iostream>
#include <stdexcept>
using namespace std;

namespace mo {

DavidDataHandler::DavidDataHandler()
{
}

void DavidDataHandler::read(const std::string& datadir)
try{
    string filename = datadir + "/trainingData.txt";
    m_trainingDataFile.open(filename.c_str());
    if(!m_trainingDataFile) throw runtime_error("cannot open the input file @DavidDataHandler::read");

    vector<unsigned> topology;
    getTopology(topology);
    unsigned datadim_ = topology[0];

    vector<double> inputVals, targetVals;
    //1 time read to fill X_
    getNextInputs(inputVals);
    if(inputVals.empty()) throw runtime_error("cannot get input values @DavidDataHandler::read()");
    X_ = cv::Mat(inputVals);
    getTargetOutputs(targetVals);
    if(targetVals.empty()) throw runtime_error("cannot get target values @DavidDataHandler::read()");
    B_ = cv::Mat(targetVals);

    //read after 2nd data.
    while(!isEof()){
        if(getNextInputs(inputVals) != datadim_) break;
//        cout<<"inputval="<<cv::Mat(inputVals)<<" ";
        cv::hconcat(X_, cv::Mat(inputVals), X_);
        getTargetOutputs(targetVals);
        if(targetVals.empty()) throw runtime_error("cannot get target values @DavidDataHandler::read()");
        cv::hconcat(B_, targetVals, B_);
    }
}catch(runtime_error& e){
    cerr << "runtime error was thrown in DavidDataHandler::read().\n";
    throw;
}

void DavidDataHandler::getTopology(vector<unsigned> &topology)
{
    string line;
    string label;

    getline(m_trainingDataFile, line);
    stringstream ss(line);
    ss >> label;
    if (this->isEof() || label.compare("topology:") != 0) {
        throw runtime_error("there is no 'topology:' description in the file.");
    }

    while (!ss.eof()) {
        unsigned n;
        ss >> n;
        topology.push_back(n);
    }

    return;
}

unsigned DavidDataHandler::getNextInputs(vector<double> &inputVals)
{
    inputVals.clear();

    string line;
    getline(m_trainingDataFile, line);
    stringstream ss(line);

    string label;
    ss>> label;
    if (label.compare("in:") == 0) {
        double oneValue;
        while (ss >> oneValue) {
            inputVals.push_back(oneValue);
        }
    }

    return inputVals.size();
}

unsigned DavidDataHandler::getTargetOutputs(vector<double> &targetOutputVals)
{
    targetOutputVals.clear();

    string line;
    getline(m_trainingDataFile, line);
    stringstream ss(line);

    string label;
    ss>> label;
    if (label.compare("out:") == 0) {
        double oneValue;
        while (ss >> oneValue) {
            targetOutputVals.push_back(oneValue);
        }
    }

    return targetOutputVals.size();
}

} // namespace mo
