#ifndef PARAM_H
#define PARAM_H
#include <iostream>
#include <list>


struct Data_param{
  std::string datafname;
  int data_type;
};


struct NN_param{
  double rho;
  double rho_descendingrate;
  double momentum;
  unsigned th_maxit;
  double th_J;
  double th_dJ;
  double th_annihilate;
  int th_topology_unchange;
  bool iterative_update;
  int problem_type;
  int num_neuralnets;
  std::list<unsigned> hidden_topology;

  std::string outdirname;
  std::string outfname;
};


struct Vis_param{
  int show_opt;
  int error_show_opt;
  int display_step;
  int waitms;
  int win_w;
  int win_h;
};


struct Param
{
  NN_param nn;
  Data_param data;
  Vis_param vis;
};


//----------------------
void read_param(std::istream& fi, Param& prm);
void read_listuint(std::istream& fi, std::list<unsigned>& vec, const char delim);
std::ostream& operator <<(std::ostream& os, Param& p);

#endif // PARAM_H
