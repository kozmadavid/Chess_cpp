#include "piece.h"

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


