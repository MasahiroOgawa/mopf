#ifndef HILL_CLIMBING_H
#define HILL_CLIMBING_H


/////////////////
/// \brief The Hill_climbing class
/// based on "これなら分かる最適化数学　金谷健一" p.81
/////////////////
class Hill_climbing
{
public:
    Hill_climbing(const double& h0, const double& eps, const double& delta);
    void compute();
    void linear_search(double (*f)(const double&));
private:
    double h0_;
    double eps_;
    double delta_;
};

#endif // HILL_CLIMBING_H
