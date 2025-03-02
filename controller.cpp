#include "controller.h"
#include <iostream>

using namespace genv;
using namespace std;

Controller::Controller()
{
}

void Controller::start()
{
    Engine engine;
    GUI gui;
    event ev;

    vector<Piece*> &board = engine.getBoard();
    vector<pair<int,int>> legalMoves_test;

    while (gin >> ev && ev.keycode != key_escape)
    {
        gui.drawBoard(board);

        if (engine.isCheck(whosTurn)) cout << "check" << endl;
        if (engine.isCheckmate(whosTurn) && engine.isCheck(whosTurn)) cout << "checkmate" << endl;

        if ((selectedPiece(ev,board) != nullptr && whosTurn == 0 && selectedPiece(ev,board)->getColor() == "white") ||
                (selectedPiece(ev,board) != nullptr && whosTurn == 1 && selectedPiece(ev,board)->getColor() == "black"))
        {
            selected = selectedPiece(ev,board);
            isThereSelected = true;
        }

        if (isThereSelected && ev.button == btn_left)
        {
            legalMoves_test = engine.getLegalMoves(selected);

            for (auto move : legalMoves_test)
            {
                if (clickedCell(ev) == move)
                {
                    auto originalCoords = selected->getCoords();
                    Piece* capturedPiece = nullptr;

                    for (int i = 0; i < board.size(); i++)
                    {
                        if (move == board[i]->getCoords())
                        {
                            capturedPiece = board[i];
                            break;
                        }
                    }

                    selected->setCoords(move.first, move.second);

                    bool shouldSwitchTurn = true;

                    if (capturedPiece)
                    {
                        if (capturedPiece->getColor() != selected->getColor())
                        {
                            engine.removePiece(capturedPiece);
                        }
                        else
                        {
                            capturedPiece = nullptr;
                            shouldSwitchTurn = false;
                        }
                    }

                    bool stillInCheck = engine.isCheck(whosTurn);

                    selected->setCoords(originalCoords.first, originalCoords.second);

                    if (capturedPiece) board.push_back(capturedPiece);

                    if (!stillInCheck)
                    {
                        if (selected->getName() == 'P' || selected->getName() == 'K' || selected->getName() == 'R')
                            selected->setFirstMoveFalse();

                        if (capturedPiece) engine.removePiece(capturedPiece);

                        selected->setCoords(clickedCell(ev).first, clickedCell(ev).second);
                        isThereSelected = false;

                        if (shouldSwitchTurn)
                        {
                            whosTurn = !whosTurn;
                        }
                    }
                }
            }
        }

        if (isThereSelected)
        {
            gui.drawSelected(selected);
            gui.drawSelectedMoves(legalMoves_test);
        }

        gout.refresh();
    }
}

Piece* Controller::selectedPiece(event ev, vector<Piece*> board)
{

    int cellSize = 100;

    if (ev.button == btn_left)
        {
            for (auto piece : board)
            {
                int piece_x = piece->getCoords().first * cellSize;
                int piece_y = piece->getCoords().second * cellSize;

                if (ev.pos_x >= piece_x && ev.pos_x < piece_x + cellSize &&
                        ev.pos_y >= piece_y && ev.pos_y < piece_y + cellSize)
                {
                    return piece;
                }
            }
        }
    return nullptr;
}

pair<int, int> Controller::clickedCell(event ev)
{
    int cellSize = 100;

    int column = ev.pos_x / cellSize;
    int row = ev.pos_y / cellSize;

    return make_pair(column, row);
}
