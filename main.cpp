#include <cstdlib>
#include "vibes.h"
#include "Path.h"
#include "Cell.h"
#include <fstream>
#include <unistd.h>
#include <iostream>




using namespace std;

struct Maze
{
  Cell *c0, *cf;
};

void draw_gate(const Cell *n1, const Cell *n2)
{
  vibes::drawBox(min(n1->m_x, n2->m_x) + 0.1, max(n1->m_x, n2->m_x) + 0.9,
                 min(n1->m_y, n2->m_y) + 0.1, max(n1->m_y, n2->m_y) + 0.9,
                 "lightGray[lightGray]");
}

void display_cell(Cell *cell)
{
  vibes::drawBox(cell->m_x, cell->m_x + 1, cell->m_y, cell->m_y + 1, "[lightGray]");
  cell->m_displayed = true;

  for(int i = 0 ; i < cell->m_nb_neighb ; i++)
  {
    if(!cell->m_neighb[i]->m_displayed)
      display_cell(cell->m_neighb[i]);
    draw_gate(cell, cell->m_neighb[i]);
  }
}

void display(Maze maze)
{
  display_cell(maze.c0);
  vibes::drawCircle(maze.c0->m_x + 0.5, maze.c0->m_y + 0.5, 0.3, "#00AC07[#00AC07]");
  vibes::drawCircle(maze.cf->m_x + 0.5, maze.cf->m_y + 0.5, 0.3, "#F39F00[#F39F00]");
}

void display_path(Path *path)
{
  if(path->m_next != NULL)
  {
    vibes::drawBox(min(path->m_c->m_x, path->m_next->m_c->m_x) + 0.45, max(path->m_c->m_x, path->m_next->m_c->m_x) + 0.55,
                   min(path->m_c->m_y, path->m_next->m_c->m_y) + 0.45, max(path->m_c->m_y, path->m_next->m_c->m_y) + 0.55,
                   "#0088AC[#0088AC]");
    display_path(path->m_next);
  }
}

bool find_path(Cell *c, Cell *cf, Path *path)
{
  c->m_flag = true;

  if(c == cf)
    return true;

  for(int i = 0 ; i < c->m_nb_neighb ; i++)
  {
    if(c->m_neighb[i]->m_flag)
      continue;

    if(find_path(c->m_neighb[i], cf, path))
    {
      path->add_to_path(c);
      return true;
    }
  }

  return false;
}

Maze create_8x8_maze()
{
  Cell* a[8][8];
  for(int i = 0 ; i < 8 ; i++)
  {
    for(int j = 0 ; j < 8 ; j++)
    {
      a[i][j] = new Cell(i, j);
    }
  }

  a[1][0]->add_neighb(a[0][0], a[2][0]);
  a[2][1]->add_neighb(a[2][0], a[1][1]);
  a[0][1]->add_neighb(a[0][2], a[1][1]);
  a[0][3]->add_neighb(a[0][2], a[0][4]);
  a[0][5]->add_neighb(a[0][4], a[1][5]);
  a[1][6]->add_neighb(a[1][5], a[1][7], a[0][6]);
  a[0][7]->add_neighb(a[0][6]);
  a[2][5]->add_neighb(a[1][5], a[2][6]);
  a[2][7]->add_neighb(a[2][6], a[3][7]);
  a[3][6]->add_neighb(a[3][5], a[4][6], a[3][7]);
  a[4][7]->add_neighb(a[5][7], a[4][6]);
  a[6][7]->add_neighb(a[6][6]);
  a[5][6]->add_neighb(a[5][7], a[5][5], a[6][6]);
  a[4][5]->add_neighb(a[5][5], a[4][4]);
  a[3][4]->add_neighb(a[4][4], a[2][4]);
  a[1][4]->add_neighb(a[2][4], a[1][3]);
  a[1][2]->add_neighb(a[1][3], a[2][2]);
  a[3][2]->add_neighb(a[2][2], a[3][1], a[4][2]);
  a[4][3]->add_neighb(a[4][2], a[5][3]);
  a[5][4]->add_neighb(a[5][3]);
  a[6][3]->add_neighb(a[6][4], a[6][2], a[5][3]);
  a[5][2]->add_neighb(a[5][3], a[5][1]);
  a[5][0]->add_neighb(a[5][1]);
  a[4][1]->add_neighb(a[4][0], a[3][1]);
  a[3][0]->add_neighb(a[4][0]);
  a[1][4]->add_neighb(a[2][4], a[1][3]);
  a[1][2]->add_neighb(a[1][3], a[2][2]);
  a[3][2]->add_neighb(a[2][2], a[3][1]);
  a[7][6]->add_neighb(a[7][7], a[7][5]);
  a[7][4]->add_neighb(a[7][5], a[7][3]);
  a[7][2]->add_neighb(a[7][3], a[7][1]);
  a[7][0]->add_neighb(a[7][1], a[6][0]);
  a[6][1]->add_neighb(a[6][0], a[6][2]);
  a[6][3]->add_neighb(a[6][2], a[6][4]);
  a[6][5]->add_neighb(a[6][3]);
  a[2][3]->add_neighb(a[3][3], a[1][3]);

  Maze m;
  m.c0 = a[0][0]; m.cf = a[7][7];
  return m;
}


Maze create_4x4_maze()
{
  Cell *cA = new Cell(0, 0);
  Cell *cB = new Cell(0, 1);
  Cell *cC = new Cell(0, 2);
  Cell *cD = new Cell(0, 3);
  Cell *cE = new Cell(1, 3);
  Cell *cF = new Cell(1, 2);
  Cell *cG = new Cell(1, 1);
  Cell *cH = new Cell(1, 0);
  Cell *cI = new Cell(2, 0);
  Cell *cJ = new Cell(2, 1);
  Cell *cK = new Cell(2, 2);
  Cell *cL = new Cell(2, 3);
  Cell *cM = new Cell(3, 3);
  Cell *cN = new Cell(3, 2);
  Cell *cO = new Cell(3, 1);
  Cell *cP = new Cell(3, 0);

  cH->add_neighb(cA, cI);
  cB->add_neighb(cG, cA);
  cJ->add_neighb(cG, cK);
  cF->add_neighb(cG, cC);
  cD->add_neighb(cC, cE);
  cL->add_neighb(cE, cM);
  cN->add_neighb(cO, cM);
  cP->add_neighb(cO);

  Maze m;
  m.c0 = cA; m.cf = cM;
  return m;
}


void save_cell(Cell *cell, ofstream *f){
	
	*f<<*cell;
	cell-> m_displayedtxt = true;
	*f<<cell-> m_nb_neighb;
	for(int i = 0 ; i < cell->m_nb_neighb ; i++)
		*f<<*cell->m_neighb[i];
	*f<<endl;	
	for(int j = 0 ; j < cell->m_nb_neighb ; j++)
		{
		//cout<<cell->m_neighb[j]->is_displayed()<<endl;
		if (!cell->m_neighb[j]->is_displayedtxt()){
			//cell->m_neighb[j]-> m_displayedtxt = true;
			save_cell(cell->m_neighb[j], f);
			
		}}


}



void save_maze(const Maze& maze, const string& file_name){

ofstream f(file_name); // tentative d’ouverture (constructeur)
if(!f.is_open())
	cout << "Erreur d’ouverture de " << file_name << endl;
else{
	f<<"# Start:"<<endl;
	f<<*maze.c0<<endl;
	f<<"# End:"<<endl;
	f<<*maze.cf<<endl;
	f<<"# Cells:"<<endl;
	save_cell(maze.c0, &f);
	
	
}
f.close();
}



Maze read_maze(const string& file_name){
	Maze m;
	map<pair<int,int>,Cell*> m_cells;
	
	Cell* c1; 
	c1 = new Cell(0, 5);

	Cell* c2; //utilisation du pointage
	c2 = new Cell(0, 5);


	ifstream f(file_name);
	string str;
	getline(f, str);
	cout<<str<<endl; //affichage de start
	
	
	f>>*c1;
	cout<<*c1<<endl; //affichage de la cellule de départ


	string str1;
	getline(f, str1);// pour finir la ligne

	string str2;
	getline(f, str2);
	cout<<str2<<endl; //affichage de end

	
	f>>*c2;
	cout<<*c2<<endl; //affichage de la cellule  d'arrivée
	

	string str4;
	getline(f, str4); //fin ligne
	
	
	string str3;
	getline(f, str3);//affichage #cell
	cout<<str3<<endl;
	str3.clear();

	

	while(!f.eof()) {
	
	Cell* c; 
	c = new Cell(2, 0);
	f>>*c;
	pair<int,int> cle;
	cle = make_pair(c->x(), c->y());
	if (m_cells.find(cle) == m_cells.end())
		m_cells[cle] = c;
	cout<<*c<<endl;

	char n;
	
	f>>n;
	n = n-'0';

	
	for(int j = 0 ; j <  (int)n; j++){
		
		Cell* cj = new Cell(0, 6);
		f>>*cj;
		cout<<(int)n;
		cout<<*cj<<endl;
		
		pair<int,int> clej;
		clej = make_pair(cj->x(), cj->y());
		if (m_cells.find(clej) == m_cells.end())
			m_cells[clej] = cj;
		
		m_cells[cle]->add_neighb(m_cells[clej]);
		
	

	}
	
	string str5;
	getline(f, str5);
	cout<<"str5 "<<str5<<endl;
	str5.clear();
	}
	
	pair<int,int> clet;
	clet = make_pair(0, 0);
	m.c0 = m_cells[clet];

	pair<int,int> clef;
	clef = make_pair(7, 7);
	m.cf = m_cells[clef];
	
	f.close();

	return m;
}




int main()
{
  //Maze maze = create_8x8_maze();
  const string& file_name = "laby2.txt";
  //save_maze(maze, file_name); 
  Maze maze;
  maze = read_maze(file_name); //lecture du labyrinthe laby2
  const string& file_name2 = "labytest.txt";
  save_maze(maze, file_name2);  //sauvegarde créée à partir du laby fabriqué à partir de laby2.txt -> on retrouve bien le même labyrinthe
 
  Path *path = new Path(maze.cf);
  
  vibes::beginDrawing();
  vibes::newFigure("Maze");
  vibes::setFigureProperties("Maze", vibesParams("x", 200, "y", 200, "width", 700, "height", 700));
  vibes::axisLimits(0-0.5, 8+0.5, 0-0.5, 8+0.5);

  display(maze);
  find_path(maze.c0, maze.cf, path);
  display_path(path);
  
  vibes::endDrawing();

  return EXIT_SUCCESS;
}
