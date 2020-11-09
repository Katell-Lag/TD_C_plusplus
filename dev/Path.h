#ifndef __PATH_H__
#define __PATH_H__

#include "Cell.h"
#include <iostream>




using namespace std;

class Path
{
  public:

    Path(const Cell *c);
    ~Path();
    void add_to_path(const Cell *c);

  //protected:

    const Cell *m_c;
    Path *m_next = NULL;
};

#endif
