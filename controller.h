#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "piece.h"
#include "engine.h"
#include "gui.h"
#include "graphics.hpp"


class Controller
{
public:
    Controller();
    void start();
    int getCurrentPlayer();

private:
    bool whosTurn = 0; //0-white 1-black
    Piece* selectedPiece(genv::event ev, vector<Piece*> board);
    Piece* selected;
    pair<int, int> clickedCell(genv::event ev);
    bool isThereSelected = false;
};

#endif // CONTROLLER_H
