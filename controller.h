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

    bool isMenu = 1;
    bool whosTurn = 0; //0-white 1-black
    Piece* selectedPiece(const vector<Piece*> &board); //Picks and gives selected piece to controller
    Piece* selected;
    pair<int, int> clickedCell();
    bool isThereSelected = false;

    bool isCheckmate(vector<Piece*> board);
    bool isDraw(vector<Piece*> board);
};

#endif // CONTROLLER_H
