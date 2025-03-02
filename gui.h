#ifndef GUI_H
#define GUI_H

#include "piece.h"
#include <vector>

using namespace std;


class GUI
{
public:
    GUI();
    void drawBoard(vector<Piece*>);
    void drawSelected(Piece*);
    void drawSelectedMoves(vector<pair<int,int>>);

};

#endif // GUI_H
