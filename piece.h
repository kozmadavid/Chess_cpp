#ifndef PIECE_H
#define PIECE_H

#include <set>
#include <vector>
#include <string>


class Piece
{
public:
    Piece(char _name, std::string _color);

    char getName();
    std::string getColor();
    std::pair<int,int> getCoords();
    std::vector<std::pair<int,int>> getLegalMoves();

    void setLegalMoves(std::vector<std::pair<int,int>> newLegalMoves);
    void setCoords(int, int);
    void emptyLegalMoves();
    void legalMoves_Add(std::pair<int,int>);

    virtual std::vector<std::pair<int,int>> canTake() = 0; //Fc that determines which pieces can the piece take
    virtual std::vector<std::pair<int,int>> whereCanMove() = 0; //Fc that determines which coordinates can the piece move
    virtual void legalMoves(
            Piece* selected, std::vector<std::pair<int,int>>canMoveWhere,
            std::vector<std::pair<int,int>>canTake, std::vector<Piece*>board) = 0; //Fc which comes back the actual moves which the piece can make on the board
    virtual bool isFirstMove() = 0;
    virtual void setFirstMoveFalse() = 0;
private:
    std::string color;
    std::pair<int,int> coords;
protected:
    std::vector<std::pair<int,int>> _legalMoves;
    char name;
};

#endif // PIECE_H
