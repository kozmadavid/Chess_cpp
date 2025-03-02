#include "king.h"
#include "engine.h"
#include <iostream>

King::King(char name, string color) : Piece(name, color)
{
}

bool King::isFirstMove()
{
    return firstMove;
}

void King::setFirstMoveFalse()
{
    firstMove = false;
}

vector<pair<int, int>> King::canTake()
{
    vector<pair<int,int>> ct;

    int x = getCoords().first;
    int y = getCoords().second;

    if (y-1 >= 0) ct.push_back(make_pair(x, y-1));
    if (x+1 <= 7 && y-1 >= 0) ct.push_back(make_pair(x+1, y-1));
    if (x+1 <= 7) ct.push_back(make_pair(x+1, y));
    if (x+1 <= 7 && y+1 <= 7) ct.push_back(make_pair(x+1, y+1));
    if (y+1 <= 7) ct.push_back(make_pair(x, y+1));
    if (x-1 >= 0 && y+1 <= 7) ct.push_back(make_pair(x-1, y+1));
    if (x-1 >= 0) ct.push_back(make_pair(x-1, y));
    if (x-1 >= 0 && y-1 >= 0) ct.push_back(make_pair(x-1, y-1));

    return ct;
}


vector<pair<int,int>> King::whereCanMove() //Same as whereCanTake
{
    vector<pair<int,int>> wcm;
    return wcm;
}


vector<pair<int,int>> King::legalMoves(Piece* selected, vector<pair<int,int>>canMoveWhere, vector<pair<int,int>>canTake, vector<Piece*> board)
{
    vector<pair<int,int>> legalMoves;

    for (int i = canTake.size() - 1; i >= 0; i--)
    {
        bool found = false;
        for (int j = 0; j < board.size(); j++)
        {
            if (canTake[i] == board[j]->getCoords() &&
                    getColor() == board[j]->getColor())
            {
                found = true;
                break;
            }
        }

        if (found) canTake.erase(canTake.begin()+i);
    }

    Piece* king = selected;

    for (int i = canTake.size() - 1; i >= 0; i--)
    {
        auto originalCoordinates = king->getCoords();
        king->setCoords(canTake[i].first, canTake[i].second);

        bool inCheck = false;


        for (auto piece : board)
        {
            if (piece->getColor() != king->getColor() && piece->getName() != 'K')
            {
                for (auto threat : piece->legalMoves(piece,piece->whereCanMove(),piece->canTake(),board))
                {
                    if (canTake[i] == threat)
                    {
                        inCheck = true;
                        break;
                    }
                }
            }
            else if(piece->getColor() != king->getColor() && piece->getName() == 'K')
            {
                for (auto threat : piece->canTake())
                {
                    if (canTake[i] == threat)
                    {
                        inCheck = true;
                        break;
                    }
                }
            }
            if (inCheck) break;
        }


        king->setCoords(originalCoordinates.first, originalCoordinates.second);

        if (inCheck) canTake.erase(canTake.begin()+i);
    }

    for (auto cell : canTake) legalMoves.push_back(cell);

    return legalMoves;
}



