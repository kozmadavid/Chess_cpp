#ifndef KING_H
#define KING_H

#include "piece.h"


class King : public Piece
{
public:
    King(char name, std::string color);
    Piece* copy() const override
    {
            return new King(*this);
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

#endif // KING_H
