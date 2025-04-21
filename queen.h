#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"


class Queen : public Piece
{
public:
    Queen(char name, std::string color);
    Piece* copy() const override
    {
            return new Queen(*this);
    }
    std::vector<std::pair<int,int>> canTake() override;
    std::vector<std::pair<int,int>> whereCanMove() override;
    void legalMoves(std::vector<std::pair<int,int>>canMoveWhere,
            std::vector<std::pair<int,int>>canTake, std::vector<Piece*>board) override;
    bool isFirstMove() override;
    void setFirstMoveFalse() override;
private:
    bool firstMove = true;
};

#endif // QUEEN_H
