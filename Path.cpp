#include "Path.h"

using namespace std;

Path::Path(const Cell *c) : m_c(c)
{
  
}

Path::~Path()
{
  if(m_next != NULL)
    delete m_next;
}

void Path::add_to_path(const Cell *c)
{
  if(m_next == NULL)
    m_next = new Path(c);

  else
    m_next->add_to_path(c);
}