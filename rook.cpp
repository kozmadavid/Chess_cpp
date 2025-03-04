#include "rook.h"
#include "engine.h"

#include <iostream>

Rook::Rook(char name, string color) : Piece(name, color)
{
}

bool Rook::isFirstMove()
{
    return firstMove;
}

void Rook::setFirstMoveFalse()
{
    firstMove = false;
}

vector<pair<int, int>> Rook::canTake()
{
    vector<pair<int,int>> ct;
    return ct;
}


vector<pair<int,int>> Rook::whereCanMove() //Same as whereCanTake
{
    vector<pair<int,int>> wcm;
    return wcm;
}


void Rook::legalMoves(Piece* selected, vector<pair<int, int>> canMoveWhere, vector<pair<int, int>> canTake, vector<Piece*> board)
{
    emptyLegalMoves();
    vector<pair<int, int>> rookDirections = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    for (auto direction : rookDirections)
    {
        int x = getCoords().first;
        int y = getCoords().second;

        while (true)
        {
            x += direction.first;
            y += direction.second;

            if (x < 0 || x >= 8 || y < 0 || y >= 8) break;

            bool blockedByOwnPiece = false;
            bool canCaptureEnemy = false;

            for (auto p : board)
            {
                if (p->getCoords() == make_pair(x, y))
                {
                    if (p->getColor() == getColor())
                    {
                        blockedByOwnPiece = true;
                    }
                    else
                    {
                        canCaptureEnemy = true;
                    }
                    break;
                }
            }
            if (blockedByOwnPiece) break;

            legalMoves_Add(make_pair(x, y));

            if (canCaptureEnemy)
            {
                legalMoves_Add(make_pair(x, y));
                break;
            }
        }
    }

    vector<pair<int, int>> sameCoordinates = _legalMoves;
    vector<pair<int, int>> toErase;
    vector<pair<int, int>> seenCoordinates;

    for (int i = 0; i < _legalMoves.size(); i++)
    {
        bool isDuplicate = false;
        for (auto& coord : seenCoordinates)
        {
            if (coord == _legalMoves[i])
            {
                isDuplicate = true;
                break;
            }
        }

        if (isDuplicate)
        {
            toErase.push_back(_legalMoves[i]);
        }
        else
        {
            seenCoordinates.push_back(_legalMoves[i]);
        }
    }

    for (auto& coord : toErase)
    {
        for (auto it = _legalMoves.begin(); it != _legalMoves.end(); ++it)
        {
            if (*it == coord)
            {
                _legalMoves.erase(it);
                break;
            }
        }
    }
}




