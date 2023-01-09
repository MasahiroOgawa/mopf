#include "param.h"
#include <sstream>
using namespace std;

void read_param(std::istream& fi, Param& prm){
  streamsize max_strlen(1024);
  string str;
  while(fi>>str){
    if(str=="datafname:") fi>>prm.data.datafname;
    else if(str=="data_type:") fi>>prm.data.data_type;

    else if(str=="rho:") fi>>prm.nn.rho;
    else if(str=="rho_descendingrate:") fi>>prm.nn.rho_descendingrate;
    else if(str=="momentum:") fi>>prm.nn.momentum;
    else if(str=="th_maxit:") fi>>prm.nn.th_maxit;
    else if(str=="th_J:") fi>>prm.nn.th_J;
    else if(str=="th_dJ:") fi>>prm.nn.th_dJ;
    else if(str=="th_annihilate:") fi>>prm.nn.th_annihilate;
    else if(str=="th_topology_unchange:") fi>>prm.nn.th_topology_unchange;
    else if(str=="hidden_topology:") read_listuint(fi,prm.nn.hidden_topology,'#');
    else if(str=="problem_type:") fi>>prm.nn.problem_type;
    else if(str=="iterative_update:") fi>>prm.nn.iterative_update;
    else if(str=="outdirname:") fi>>prm.nn.outdirname;
    else if(str=="outfname:") fi>>prm.nn.outfname;
    else if(str=="num_neuralnets:") fi>>prm.nn.num_neuralnets;

    else if(str=="show_opt:") fi>>prm.vis.show_opt;
    else if(str=="error_show_opt:") fi>>prm.vis.error_show_opt;
    else if(str=="display_step:") fi>>prm.vis.display_step;
    else if(str=="waitms:") fi>>prm.vis.waitms;
    else if(str=="win_w:") fi>>prm.vis.win_w;
    else if(str=="win_h:") fi>>prm.vis.win_h;

    fi.ignore(max_strlen,'\n'); //read until reaching the max_strlen or the end of the line.
  }
}

void read_listuint(std::istream& fi, std::list<unsigned>& vec, const char delim) {
  string line;
  getline(fi,line,delim); //read until delim

  std::istringstream iss(line);
  int num;
  while(iss>>num) vec.push_back(num);
}

std::ostream& operator <<(std::ostream& os, Param& prm){
  os << "datafname:" << prm.data.datafname << "\n";
  os << "data_type:" << prm.data.data_type << "\n";

  os << "rho:" << prm.nn.rho << "\n";
  os << "rho_descendingrate:" << prm.nn.rho_descendingrate << "\n";
  os << "momentum:" << prm.nn.momentum << "\n";
  os << "th_maxit:" << prm.nn.th_maxit << "\n";
  os << "th_J:" << prm.nn.th_J << "\n";
  os << "th_dJ:" << prm.nn.th_dJ << "\n";
  os << "th_annihilate:" << prm.nn.th_annihilate << "\n";
  os << "th_topology_unchange:" << prm.nn.th_topology_unchange << "\n";

  os << "problem_type:" << prm.nn.problem_type << "\n";
  os << "iterative_update:" << prm.nn.iterative_update << "\n";
  os << "outdirname:" << prm.nn.outdirname << "\n";
  os << "outfname:" << prm.nn.outfname << "\n";
  os << "num_neuralnets:" << prm.nn.num_neuralnets << "\n";
  os << "hidden_topology:"; for(auto& i : prm.nn.hidden_topology) os << i << "\n";

  os << "show_opt:" << prm.vis.show_opt << "\n";
  os << "error_show_opt:" << prm.vis.error_show_opt << "\n";
  os << "display_step:" << prm.vis.display_step << "\n";
  os << "waitms:" << prm.vis.waitms << "\n";
  os << "win_w:" << prm.vis.win_w << "\n";
  os << "win_h:" << prm.vis.win_h << "\n";
  return os;
}
