#include "king.h"
#include "engine.h"

#include <iostream>
#include <algorithm>


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


void King::legalMoves(Piece* selected, vector<pair<int,int>> canMoveWhere, vector<pair<int,int>> canTake, vector<Piece*> board)
{
    emptyLegalMoves();

    pair<int, int> originalCoords = getCoords();
    vector<pair<int, int>> validMoves = canTake;

    pair<int, int> enemyKingPos;
    for (auto piece : board)
    {
        if (piece->getName() == 'K' && piece->getColor() != getColor())
        {
            enemyKingPos = piece->getCoords();
            break;
        }
    }

    for (int i = canTake.size() - 1; i >= 0; i--)
    {
        setCoords(canTake[i].first, canTake[i].second);
        bool isInCheck = false;
        bool isSafeFromEnemyKing = true;

        for (int dx = -1; dx <= 1; dx++)
        {
            for (int dy = -1; dy <= 1; dy++)
            {
                pair<int, int> kingMove = {enemyKingPos.first + dx, enemyKingPos.second + dy};
                if (canTake[i] == kingMove)
                {
                    isSafeFromEnemyKing = false;
                    break;
                }
            }
            if (!isSafeFromEnemyKing) break;
        }

        if (!isSafeFromEnemyKing)
        {
            validMoves.erase(validMoves.begin() + i);
            continue;
        }

        for (auto piece : board)
        {
            if (piece->getName() != 'K' && piece->getColor() != getColor())
            {
                piece->legalMoves(piece, piece->whereCanMove(), piece->canTake(), board);

                for (auto move : piece->getLegalMoves())
                {
                    if (move == getCoords())
                    {
                        isInCheck = true;
                        break;
                    }
                }
            }

            if (isInCheck) break;
        }

        if (isInCheck)
        {
            validMoves.erase(validMoves.begin() + i);
        }
    }

    setCoords(originalCoords.first, originalCoords.second);

    for (int i = validMoves.size()-1; i >= 0; i--)
    {
        for (auto piece : board)
        {
            if (piece->getColor() == getColor() && validMoves[i] == piece->getCoords())
            {
                validMoves.erase(validMoves.begin()+i);
            }
        }
    }

    setLegalMoves(validMoves);
}



/*
void King::legalMoves(Piece* selected, vector<pair<int,int>> canMoveWhere, vector<pair<int,int>> canTake, vector<Piece*> board)
{
    // Saját bábuk eltávolítása a canTake listából
    for (int i = canTake.size() - 1; i >= 0; i--)
    {
        for (auto* piece : board)
        {
            if (canTake[i] == piece->getCoords() && getColor() == piece->getColor())
            {
                canTake.erase(canTake.begin() + i);
                break;
            }
        }
    }

    // Ellenőrizzük az ellenfél bábuit, hogy sakkban lennénk-e
    vector<int> whatToErase;
    pair<int, int> originalCoordinates = getCoords();

    for (int i = 0; i < canTake.size(); i++)
    {
        setCoords(canTake[i].first, canTake[i].second);

        for (auto* piece : board)
        {
            if (getColor() != piece->getColor() && piece->getName() != 'K')
            {
                piece->legalMoves(piece, piece->whereCanMove(), piece->canTake(), board);

                for (auto move : piece->canTake()) // Csak az üthető mezőket vizsgáljuk
                {
                    if (getCoords() == move)
                    {
                        whatToErase.push_back(i);
                    }
                }
            }
        }
    }

    // Debug kiírás, hogy lásd, milyen mezőket törlünk
    cout << "Törlésre jelölt mezők: ";
    for (auto index : whatToErase) {
        if (index < canTake.size()) {
            cout << "(" << canTake[index].first << ", " << canTake[index].second << ") ";
        }
    }
    cout << endl;

    // A törlendő indexeket fordított sorrendben töröljük
    sort(whatToErase.rbegin(), whatToErase.rend());
    for (auto index : whatToErase)
    {
        if (index < canTake.size()) {
            canTake.erase(canTake.begin() + index);
        }
    }

    // Eredeti koordináták visszaállítása
    setCoords(originalCoordinates.first, originalCoordinates.second);
    setLegalMoves(canTake);
}
*/




