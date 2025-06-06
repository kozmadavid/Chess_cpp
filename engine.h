#ifndef ENGINE_H
#define ENGINE_H

#include "piece.h"
#include "pawn.h"
#include "king.h"
#include "bishop.h"
#include "rook.h"
#include "queen.h"
#include "knight.h"

using namespace std;

class Engine
{
public:
    Engine();
    vector<Piece*> &getBoard();
    void removePiece(Piece*);
    void removeInvalidMoves(vector<Piece*>&board,bool whosTurn);
    vector<pair<int,int>> getLegalMoves(Piece* selected);

    bool isCheck(bool whosTurn,const vector<Piece*>& customBoard);
    bool isCheckmate(bool whosTurn);

    bool isTakingAttackingPiece(Piece* piece, pair<int, int> attackMove, Piece* king);

    bool isPromotion(vector<Piece*> board);
    void promotion(Piece* pawn, char promoted);

    void shortCastle(bool whosTurn);
    void shortCastleCheck(bool whosTurn);
    void longCastle(bool whosTurn);
    void longCastleCheck(bool whosTurn);
private:
    vector<Piece*> board;
};

#endif // ENGINE_H
