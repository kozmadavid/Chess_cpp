#ifndef GUI_H
#define GUI_H

#include "piece.h"
#include <vector>

using namespace std;

struct Pixel
{
    int x,y,r,g,b;
};


class GUI
{
public:
    GUI();
    void drawBoard(vector<Piece*>);
    void drawSelected(Piece*);
    void drawSelectedMoves(vector<pair<int,int>>);
    vector<Pixel> readImage(const string&);
    vector<Pixel> loadPieceImage(const string&);
    void drawPieces(vector<Piece*>);
};

#endif // GUI_H
