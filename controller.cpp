#include "controller.h"
#include <iostream>

using namespace genv;
using namespace std;

Controller::Controller()
{
}

void Controller::start()
{
    vector<Piece*> &board = engine.getBoard();
    vector<pair<int,int>> selectedLegalMoves;

    while (gin >> ev && ev.keycode != key_escape)
    {
        gui.drawBoard(board);

        for (auto piece : board)
            piece->legalMoves(piece, piece->whereCanMove(), piece->canTake(), board);

        engine.removeInvalidMoves(board, whosTurn);

        if (engine.isCheckmate(whosTurn) && engine.isCheck(whosTurn, board))
            cout << "checkmate";

        if ((selectedPiece(board) != nullptr && whosTurn == 0 && selectedPiece(board)->getColor() == "white") ||
            (selectedPiece(board) != nullptr && whosTurn == 1 && selectedPiece(board)->getColor() == "black"))
        {
            selected = selectedPiece(board);
            isThereSelected = true;
        }

        if (isThereSelected && ev.button == btn_left)
        {
            selectedLegalMoves = engine.getLegalMoves(selected);

            for (auto move : selectedLegalMoves)
            {
                if (clickedCell() == move)
                {
                    pair<int,int> originalCoords = selected->getCoords();
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

                    bool stillInCheck = engine.isCheck(whosTurn, board);

                    selected->setCoords(originalCoords.first, originalCoords.second);

                    if (capturedPiece) board.push_back(capturedPiece);

                    if (!stillInCheck)
                    {
                        if (selected->getName() == 'P' || selected->getName() == 'K' || selected->getName() == 'R')
                            selected->setFirstMoveFalse();

                        if (capturedPiece) engine.removePiece(capturedPiece);

                        selected->setCoords(clickedCell().first, clickedCell().second);
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
            gui.drawSelectedMoves(selectedLegalMoves);
        }

        gout.refresh();
    }
}

Piece* Controller::selectedPiece(vector<Piece*> board)
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

pair<int, int> Controller::clickedCell()
{
    int cellSize = 100;

    int column = ev.pos_x / cellSize;
    int row = ev.pos_y / cellSize;

    return make_pair(column, row);
}
