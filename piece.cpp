#include "piece.h"
#include <iostream>

using namespace std;

Piece::Piece(char _name, string _color)
{
    name = _name;
    color = _color;
}

char Piece::getName()
{
    return name;
}

pair<int,int> Piece::getCoords()
{
    return coords;
}

string Piece::getColor()
{
    return color;
}


void Piece::setCoords(int x,int y)
{
    coords.first = x;
    coords.second = y;
}

vector<pair<int,int>> Piece::getLegalMoves()
{
    return _legalMoves;
}

void Piece::setLegalMoves(vector<pair<int,int>> newLegalMoves)
{
    _legalMoves = newLegalMoves;
}

void Piece::legalMoves_Add(pair<int,int>newItem)
{
    _legalMoves.push_back(newItem);
}

void Piece::emptyLegalMoves()
{
    _legalMoves.clear();
}


