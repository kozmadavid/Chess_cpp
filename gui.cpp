#include "gui.h"
#include "graphics.hpp"

#include <iostream>

using namespace genv;

const int XX = 800;
const int YY = 800;

const int CELL_SIZE = 100;

GUI::GUI()
{
    gout.open(XX,YY);
}

void GUI::drawBoard(vector<Piece*> board)
{
    bool wOrB = true;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if(wOrB == true)
            {
                gout << color(230,188,125);
                gout << move_to(i*CELL_SIZE,j*CELL_SIZE) << box(CELL_SIZE,CELL_SIZE);
            }
            else
            {
                gout << color(183,139,73);
                gout << move_to(i*CELL_SIZE,j*CELL_SIZE) << box(CELL_SIZE,CELL_SIZE);
            }
            wOrB = !wOrB;
        }
        wOrB = !wOrB;
    }

    gout.load_font("D:/cpp_projects/sneak_leadando/LiberationSans-Regular.ttf", 60);

    for (auto piece : board)
    {
        if (piece->getColor() == "white") gout << color(255,255,255);
        else gout << color(0,0,0);

        gout << move_to(piece->getCoords().first*CELL_SIZE, piece->getCoords().second*CELL_SIZE) << text(piece->getName());
    }
}

void GUI::drawSelected(Piece* selected)
{
    int x = selected->getCoords().first*CELL_SIZE;
    int y = selected->getCoords().second*CELL_SIZE;

    gout << move_to(x,y) << color(255,255,0)
         << line_to(x+CELL_SIZE,y) << line_to(x+CELL_SIZE,y+CELL_SIZE)
         << line_to(x,y+CELL_SIZE) << line_to(x,y);

    gout << move_to(x-1,y-1) << line_to(x+CELL_SIZE-1,y-1)
         << line_to(x+CELL_SIZE-1,y+CELL_SIZE-1)
         << line_to(x-1,y+CELL_SIZE-1) << line_to(x-1,y-1);
}

void draw_circle(int x0, int y0, int r)
{
    for (int y = -r; y <= r; y++)
    {
        for (int x = -r; x <= r; x++)
        {
            if (x*x + y*y <= r*r) gout << move_to(x0+x, y0+y) << dot;
        }
    }
}

void GUI::drawSelectedMoves(vector<pair<int,int>>LegalMoves)
{
    for (auto move : LegalMoves)
    {
        gout << color(0,0,0);
        draw_circle(move.first*CELL_SIZE+CELL_SIZE/2,move.second*CELL_SIZE+CELL_SIZE/2,15);
    }

}
