#include "bishop.h"
#include "engine.h"

#include <iostream>

Bishop::Bishop(char name, string color) : Piece(name, color)
{
}

bool Bishop::isFirstMove()
{
}

void Bishop::setFirstMoveFalse()
{
}

vector<pair<int, int>> Bishop::canTake()
{
    vector<pair<int,int>> ct;

    int x = getCoords().first;
    int y = getCoords().second;

    for (int i = 1; x + i < 8 && y - i >= 0; i++) ct.push_back(make_pair(x + i, y - i));

    for (int i = 1; x + i < 8 && y + i < 8; i++) ct.push_back(make_pair(x + i, y + i));

    for (int i = 1; x - i >= 0 && y - i >= 0; i++) ct.push_back(make_pair(x - i, y - i));

    for (int i = 1; x - i >= 0 && y + i < 8; i++) ct.push_back(make_pair(x - i, y + i));


    return ct;
}


vector<pair<int,int>> Bishop::whereCanMove() //Same as whereCanTake
{
    vector<pair<int,int>> wcm;
    return wcm;
}


void Bishop::legalMoves(Piece* selected, vector<pair<int, int>> canMoveWhere, vector<pair<int, int>> canTake, vector<Piece*> board)
{
    emptyLegalMoves();
    vector<pair<int, int>> bishopDirections = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

    for (auto direction : bishopDirections)
    {
        int x = getCoords().first;
        int y = getCoords().second;

        while (true)
        {
            x += direction.first;
            y += direction.second;

            if (x < 0 || x >= 8 || y < 0 || y >= 8) break;

            bool blocked = false;

            for (auto p : board)
            {
                if (p->getCoords() == make_pair(x, y))
                {
                    if (p->getColor() != getColor())
                    {
                        legalMoves_Add(make_pair(x, y));  // ellenséges bábu ütése
                    }
                    blocked = true;
                    break;
                }
            }

            if (blocked) break;

            legalMoves_Add(make_pair(x, y)); // szabad mező
        }
    }
}
