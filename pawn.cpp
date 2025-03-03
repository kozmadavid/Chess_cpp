#include "pawn.h"
#include "engine.h"

using namespace std;

Pawn::Pawn(char name, string color) : Piece(name, color)
{
}

bool Pawn::isFirstMove()
{
    return firstMove;
}

void Pawn::setFirstMoveFalse()
{
    firstMove = false;
}

vector<pair<int, int>> Pawn::canTake()
{
    vector<pair<int, int>> canTake;

    int x = getCoords().first;
    int y = getCoords().second;
    int direction = (getColor() == "white") ? -1 : 1;

    if (x > 0 && (y + direction >= 0 && y + direction <= 7))
    {
        canTake.push_back({x - 1, y + direction});
    }

    if (x < 7 && (y + direction >= 0 && y + direction <= 7))
    {
        canTake.push_back({x + 1, y + direction});
    }

    return canTake;
}


vector<pair<int,int>> Pawn::whereCanMove()
{
    vector<pair<int,int>> wcm;

    if (firstMove)
    {
        if (getColor() == "white")
        {
            wcm.push_back(make_pair(getCoords().first, getCoords().second-1));
            wcm.push_back(make_pair(getCoords().first, getCoords().second-2));
        }
        else
        {
            wcm.push_back(make_pair(getCoords().first, getCoords().second+1));
            wcm.push_back(make_pair(getCoords().first, getCoords().second+2));
        }
    }
    else if (getColor() == "white") wcm.push_back(make_pair(getCoords().first, getCoords().second-1));

    else if (getColor() == "black") wcm.push_back(make_pair(getCoords().first, getCoords().second+1));


    return wcm;
}


void Pawn::legalMoves(Piece* selected, vector<pair<int,int>>canMoveWhere, vector<pair<int,int>>canTake, vector<Piece*> board)
{
    emptyLegalMoves();
    for (int i = canMoveWhere.size() - 1; i >= 0; i--)
    {
        for (int j = 0; j < board.size(); j++)
        {
            if (canMoveWhere[i] == board[j]->getCoords())
            {
                canMoveWhere.erase(canMoveWhere.begin()+i);
                break;
            }
        }
    }

    if (isFirstMove())
        {
            int x = selected->getCoords().first;
            int y = selected->getCoords().second;

            if (getColor() == "white" && y - 2 >= 0)
            {
                bool isBlocked = false;
                for (int j = 0; j < board.size(); j++)
                {
                    if (board[j]->getCoords() == make_pair(x, y - 1))
                    {
                        isBlocked = true;
                        break;
                    }
                }

                if (isBlocked) canMoveWhere.clear();
            }

            else if (getColor() == "black" && y + 2 <= 7)
            {
                bool isBlocked = false;
                for (int j = 0; j < board.size(); j++)
                {
                    if (board[j]->getCoords() == make_pair(x, y + 1))
                    {
                        isBlocked = true;
                        break;
                    }
                }

                if (isBlocked) canMoveWhere.clear();
            }
        }

    for (auto cell : canMoveWhere) _legalMoves.push_back(cell); //canMoveWhere filtered, added to legalMoves

    //_________________________________________________________________________________________________________

    for (int i = canTake.size() - 1; i >= 0; i--)
    {
        bool found = false;
        for (int j = 0; j < board.size(); j++)
        {
            if (canTake[i] == board[j]->getCoords() &&
                    getColor() != board[j]->getColor())
            {
                found = true;
                break;
            }
        }

        if (!found) canTake.erase(canTake.begin()+i);
    }

    for (auto cell : canTake) _legalMoves.push_back(cell); //canTake filtered, added to legalMoves

}

