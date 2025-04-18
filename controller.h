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
private:
    Engine engine;
    GUI gui;
    genv::event ev;

    bool whosTurn = 0; //0-white 1-black
    Piece* selectedPiece(vector<Piece*> board);
    Piece* selected;
    pair<int, int> clickedCell();
    bool isThereSelected = false;
};

#endif // CONTROLLER_H
