#include "Cell.h"

using namespace std;

Cell::Cell(int x, int y) : m_x(x), m_y(y)
{

}

int Cell::x() const
{
	return m_x;

}

int Cell::y() const
{
	return m_y;

}

Cell::~Cell()
{
  
}

void Cell::add_neighb(Cell *n1)
{
 	
  
  for(int i = 0 ; i < m_nb_neighb ; i++)
    if(m_neighb[i] == n1)
      return;
  
  m_nb_neighb++;

  Cell **new_neighb = new Cell*[m_nb_neighb];
  for(int i = 0 ; i < m_nb_neighb - 1 ; i++)
    new_neighb[i] = m_neighb[i];

  new_neighb[m_nb_neighb - 1] = n1;
  delete[] m_neighb;
  m_neighb = new_neighb;

  n1->add_neighb(this);
 
}

void Cell::add_neighb(Cell *n1, Cell *n2)
{
  add_neighb(n1);
  add_neighb(n2);
}

void Cell::add_neighb(Cell *n1, Cell *n2, Cell *n3)
{
  add_neighb(n1);
  add_neighb(n2);
  add_neighb(n3);
}

ostream& operator<<(ostream& stream, const Cell& c) {
stream << "("<< c.x()<<","<<c.y()<<")"; 
return stream;
}

bool Cell::is_displayedtxt()
{
	return m_displayedtxt;

}


istream& operator>>(istream& stream, Cell& c) {

char p1;
char p2;
char vi;
char xi;
char yi;
//char end;
stream.get(p1);
stream.get(xi);
stream.get(vi);
stream.get(yi);
stream.get(p2);
//stream.get(end);


xi = xi-'0';
yi = yi-'0';

c.m_x = xi;
c.m_y =yi;


return stream;
}
