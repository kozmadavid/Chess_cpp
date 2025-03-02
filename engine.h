#ifndef ENGINE_H
#define ENGINE_H

#include "piece.h"
#include "pawn.h"
#include "king.h"
#include "bishop.h"
#include "rook.h"
#include "queen.h"

using namespace std;

class Engine
{
public:
    Engine();
    vector<Piece*> &getBoard();
    void removePiece(Piece*);
    vector<pair<int,int>> getLegalMoves(Piece* selected);
    bool isCheck(bool whosTurn);
    bool isCheckmate(bool whosTurn);
    bool isTakingAttackingPiece(Piece* piece, pair<int, int> attackMove, Piece* king);
    vector<pair<int, int>> getPathBetween(pair<int, int> start, pair<int, int> end);
private:
    vector<Piece*> board;
};

#endif // ENGINE_H
