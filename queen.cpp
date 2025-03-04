#include "queen.h"
#include "engine.h"

#include <iostream>

Queen::Queen(char name, string color) : Piece(name, color)
{
}

bool Queen::isFirstMove()
{
}

void Queen::setFirstMoveFalse()
{
}

vector<pair<int, int>> Queen::canTake()
{
    vector<pair<int,int>> ct;

    int x = getCoords().first;
    int y = getCoords().second;

    for (int i = 1; x + i < 8 && y - i >= 0; i++) ct.push_back(make_pair(x + i, y - i));

    for (int i = 1; x + i < 8 && y + i < 8; i++) ct.push_back(make_pair(x + i, y + i));

    for (int i = 1; x - i >= 0 && y - i >= 0; i++) ct.push_back(make_pair(x - i, y - i));

    for (int i = 1; x - i >= 0 && y + i < 8; i++) ct.push_back(make_pair(x - i, y + i));

    for (int i = 1; x + i < 8; i++) ct.push_back(make_pair(x + i, y));

    for (int i = 1; x - i >= 0; i++) ct.push_back(make_pair(x - i, y));

    for (int i = 1; y - i >= 0; i++) ct.push_back(make_pair(x, y - i));

    for (int i = 1; y + i < 8; i++) ct.push_back(make_pair(x, y + i));

    return ct;
}


vector<pair<int,int>> Queen::whereCanMove() //Same as whereCanTake
{
    vector<pair<int,int>> wcm;
    return wcm;
}


void Queen::legalMoves(Piece* selected, vector<pair<int, int>> canMoveWhere, vector<pair<int, int>> canTake, vector<Piece*> board)
{
    emptyLegalMoves();
    vector<pair<int, int>> queenDirections = {{-1, 0}, {1, 0}, {0, -1}, {0, 1},
                                              {-1, -1}, {1, 1}, {-1, 1}, {1, -1}};


    for (auto direction : queenDirections)
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
                    if (p->getColor() == getColor()) blockedByOwnPiece = true;

                    else canCaptureEnemy = true;

                    break;
                }
            }

            if (blockedByOwnPiece) break;

            _legalMoves.push_back(make_pair(x, y));

            if (canCaptureEnemy)
            {
                _legalMoves.push_back(make_pair(x, y));
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





