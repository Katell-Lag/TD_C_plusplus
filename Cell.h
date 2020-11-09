#ifndef __CELL_H__
#define __CELL_H__
#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include <iostream>







using namespace std;

class Cell
{
  public:

    Cell(int x, int y);
    int x() const;
    int y() const;
    ~Cell();

    void add_neighb(Cell *n1);
    void add_neighb(Cell *n1, Cell *n2);
    void add_neighb(Cell *n1, Cell *n2, Cell *n3);
    bool is_displayedtxt();
    friend ostream& operator<<(ostream& stream, const Cell& c);
    friend istream& operator>>(istream& stream, Cell& c);

  //protected:

    int m_x, m_y;
    int m_nb_neighb = 0;
    Cell **m_neighb = NULL;
    bool m_displayedtxt = false;
    bool m_displayed = false;
    bool m_flag = false;
};

#endif
