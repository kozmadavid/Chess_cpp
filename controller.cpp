#include "controller.h"
#include <iostream>

using namespace genv;
using namespace std;

const int CELL_SIZE = 100;

Controller::Controller()
{
    gui.loadMenu();
    gui.loadBoard();
}

void Controller::start()
{
    vector<Piece*> &board = engine.getBoard();
    vector<pair<int,int>> selectedLegalMoves;

    while (gin >> ev && ev.keycode != key_escape)
    {
        if (isMenu)
        {
            gui.drawMenu();
            gout.refresh();
        }
        else
        {
            gui.setPieces(board);
            gui.drawBoardContents();
            gout.refresh();

            for (auto piece : board)
                piece->legalMoves(piece->whereCanMove(), piece->canTake(), board);

            engine.removeInvalidMoves(board, whosTurn);
            engine.shortCastleCheck(whosTurn);
            engine.longCastleCheck(whosTurn);

            if (isCheckmate(board))
            {
                cout << "checkmate";
            }

            if (isDraw(board))
            {
                cout << "draw";
            }

            if (isThereSelected && ev.button == btn_left)
            {
                selectedLegalMoves = engine.getLegalMoves(selected);
                bool moved = false;

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
                            if (capturedPiece) engine.removePiece(capturedPiece);

                            selected->setCoords(clickedCell().first, clickedCell().second);

                            if (engine.isPromotion(board))
                            {
                                engine.promotion(selected, 'Q');
                            }

                            engine.shortCastle(whosTurn);
                            engine.longCastle(whosTurn);

                            isThereSelected = false;
                            gui.setSelectedPiece(nullptr);

                            if (shouldSwitchTurn)
                            {
                                whosTurn = !whosTurn;
                            }

                            if (selected->getName() == 'P' || selected->getName() == 'K' || selected->getName() == 'R')
                                selected->setFirstMoveFalse();
                        }
                        moved = true;
                        break;
                    }
                }

                if (!moved)
                {
                    Piece* clickedPiece = selectedPiece(board);
                    if (clickedPiece != nullptr && clickedPiece->getColor() == (whosTurn == 0 ? "white" : "black"))
                    {
                        selected = clickedPiece;
                        isThereSelected = true;
                        gui.setSelectedPiece(selected);
                    }
                    else
                    {
                        selected = nullptr;
                        isThereSelected = false;
                        gui.setSelectedPiece(nullptr);
                    }
                }
            }
            else if (ev.button == btn_left)
            {
                Piece* clickedPiece = selectedPiece(board);
                if (clickedPiece != nullptr && clickedPiece->getColor() == (whosTurn == 0 ? "white" : "black"))
                {
                    selected = clickedPiece;
                    isThereSelected = true;
                    gui.setSelectedPiece(selected);
                }
                else
                {
                    selected = nullptr;
                    isThereSelected = false;
                    gui.setSelectedPiece(nullptr);
                }
            }
        }
    }
}


Piece* Controller::selectedPiece(const vector<Piece*>& board)
{
    if (ev.button == btn_left)
    {
        for (auto piece : board)
        {
            int piece_x = piece->getCoords().first * CELL_SIZE;
            int piece_y = piece->getCoords().second * CELL_SIZE;

            if (ev.pos_x >= piece_x && ev.pos_x < piece_x + CELL_SIZE &&
                ev.pos_y >= piece_y && ev.pos_y < piece_y + CELL_SIZE)
            {
                return piece;
            }
        }
    }
    return nullptr;
}

pair<int, int> Controller::clickedCell()
{
    int column = ev.pos_x / CELL_SIZE;
    int row = ev.pos_y / CELL_SIZE;

    return make_pair(column, row);
}

bool Controller::isCheckmate(vector<Piece*> board)
{
    if (engine.isCheckmate(whosTurn) && engine.isCheck(whosTurn, board)) return true;
    return false;
}

bool Controller::isDraw(vector<Piece*> board)
{
    if (engine.isCheckmate(whosTurn) && !engine.isCheck(whosTurn, board)) return true;
    return false;
}
