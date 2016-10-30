#ifndef DATAHANDLER_H
#define DATAHANDLER_H
#include <string>
#include <memory> //unique_ptr

namespace mo {
enum class DataType{mnist};

class DataHandler
{
public:
    DataHandler();
    virtual void read(const std::string& datadir = "") = 0; // pure virtual function; must be implemented in derived classes.
    virtual void show_traindata() = 0;
    virtual ~DataHandler(){} // Because DataHandler has virtual func, need virtual destructor to call derived class's destructor.
};

std::unique_ptr<DataHandler> create_handler(const DataType data_type);

} // namespace mo

#endif // DATAHANDLER_H
