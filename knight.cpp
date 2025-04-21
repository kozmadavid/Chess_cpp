#include "knight.h"
#include "engine.h"

#include <iostream>

Knight::Knight(char name, string color) : Piece(name, color)
{
}

bool Knight::isFirstMove()
{
}

void Knight::setFirstMoveFalse()
{
}

vector<pair<int, int>> Knight::canTake()
{
    vector<pair<int,int>> ct;

    int x = getCoords().first;
    int y = getCoords().second;

    ct.push_back(make_pair(x + 2, y + 1));
    ct.push_back(make_pair(x + 2, y - 1));
    ct.push_back(make_pair(x - 2, y + 1));
    ct.push_back(make_pair(x - 2, y - 1));
    ct.push_back(make_pair(x + 1, y + 2));
    ct.push_back(make_pair(x + 1, y - 2));
    ct.push_back(make_pair(x - 1, y + 2));
    ct.push_back(make_pair(x - 1, y - 2));

    return ct;
}


vector<pair<int,int>> Knight::whereCanMove() //Same as canTake
{
    vector<pair<int,int>> wcm;
    return wcm;
}


void Knight::legalMoves(Piece* selected, vector<pair<int, int>> canMoveWhere, vector<pair<int, int>> canTake, vector<Piece*> board)
{
    emptyLegalMoves();

    vector<pair<int, int>> validMoves;

    for (auto move : canTake)
    {
        int x = move.first;
        int y = move.second;

        if (x < 0 || x >= 8 || y < 0 || y >= 8) continue;

        bool blockedByOwnPiece = false;

        for (auto piece : board)
        {
            if (piece->getCoords().first == x && piece->getCoords().second == y)
            {
                if (piece->getColor() == getColor())
                {
                    blockedByOwnPiece = true;
                }
                break;
            }
        }

        if (!blockedByOwnPiece)
        {
            validMoves.push_back(move);
        }
    }

    setLegalMoves(validMoves);
}







