#include "engine.h"
#include <iostream>

#include <algorithm>

using namespace std;

Engine::Engine()
{
    //Kings
    King* white_king = new King('K', "white");
    white_king->setCoords(4,7);
    board.push_back(white_king);

    King* black_king = new King('K', "black");
    black_king->setCoords(4,0);
    board.push_back(black_king);

    //Pawns
    for (int i = 0; i < 2; i++)
    {
        for (int x = 0; x < 8; x++)
        {
            if (i < 1)
            {
                Pawn* pawn = new Pawn('P', "white");
                pawn->setCoords(x,6);
                board.push_back(pawn);
            }
            else
            {
                Pawn* pawn = new Pawn('P', "black");
                pawn->setCoords(x,1);
                board.push_back(pawn);
            }
        }
    }


    //Bishops
    Bishop* white_bishop_b = new Bishop('B', "white");
    white_bishop_b->setCoords(2,7);
    board.push_back(white_bishop_b);

    Bishop* white_bishop_w = new Bishop('B', "white");
    white_bishop_w->setCoords(5,7);
    board.push_back(white_bishop_w);

    Bishop* black_bishop_w = new Bishop('B', "black");
    black_bishop_w->setCoords(2,0);
    board.push_back(black_bishop_w);

    Bishop* black_bishop_b = new Bishop('B', "black");
    black_bishop_b->setCoords(5,0);
    board.push_back(black_bishop_b);

    //Knights
    Knight* white_knight_b = new Knight('N', "white");
    white_knight_b->setCoords(1,7);
    board.push_back(white_knight_b);

    Knight* white_knight_w = new Knight('N', "white");
    white_knight_w->setCoords(6,7);
    board.push_back(white_knight_w);

    Knight* black_knight_w = new Knight('N', "black");
    black_knight_w->setCoords(1,0);
    board.push_back(black_knight_w);

    Knight* black_knight_b = new Knight('N', "black");
    black_knight_b->setCoords(6,0);
    board.push_back(black_knight_b);


    //Queens
    Queen* white_queen = new Queen('Q', "white");
    white_queen->setCoords(3,7);
    board.push_back(white_queen);

    Queen* black_queen = new Queen('Q', "black");
    black_queen->setCoords(3,0);
    board.push_back(black_queen);


    //Rooks
    Rook* white_rook_w = new Rook('R', "white");
    white_rook_w->setCoords(7,7);
    board.push_back(white_rook_w);

    Rook* white_rook_b = new Rook('R', "white");
    white_rook_b->setCoords(0,7);
    board.push_back(white_rook_b);

    Rook* black_rook_w = new Rook('R', "black");
    black_rook_w->setCoords(0,0);
    board.push_back(black_rook_w);

    Rook* black_rook_b = new Rook('R', "black");
    black_rook_b->setCoords(7,0);
    board.push_back(black_rook_b);
}


vector<Piece*> &Engine::getBoard()
{
    return board;
}

vector<pair<int,int>> Engine::getLegalMoves(Piece* selected)
{
    return selected->getLegalMoves();
}

void Engine::removePiece(Piece* piece)
{
    for (auto it = board.begin(); it != board.end(); it++)
        {
            if (*it == piece)
            {
                board.erase(it);
                return;
            }
        }
}

bool Engine::isCheck(bool whosTurn, const vector<Piece*>& customBoard)
{
    string color = (whosTurn == 0) ? "white" : "black";
    Piece* king = nullptr;

    for (auto piece : customBoard)
    {
        if (piece->getName() == 'K' && piece->getColor() == color)
        {
            king = piece;
            break;
        }
    }

    if (king == nullptr) return false;

    for (auto attacker : customBoard)
    {
        if (attacker->getColor() == color) continue;

        attacker->legalMoves(attacker, attacker->whereCanMove(), attacker->canTake(), customBoard);
        vector<pair<int, int>> attackingMoves = attacker->getLegalMoves();

        for (auto move : attackingMoves)
        {
            if (move == king->getCoords())
            {
                return true;
            }
        }
    }

    return false;
}

void Engine::removeInvalidMoves(vector<Piece*>& board, bool whosTurn)
{
    string color = (whosTurn == 0) ? "white" : "black";

    for (auto* piece : board)
    {
        if (piece->getColor() != color || piece->getName() == 'K') continue;

        vector<pair<int, int>> validMoves = piece->getLegalMoves();
        pair<int, int> originalCoords = piece->getCoords();

        for (int i = validMoves.size() - 1; i >= 0; i--)
        {
            vector<Piece*> simulatedBoard;
            for (auto* p : board)
            {
                simulatedBoard.push_back(p->copy());
            }

            Piece* simulatedPiece = nullptr;
            for (auto* p : simulatedBoard)
            {
                if (p->getCoords() == originalCoords && p->getColor() == piece->getColor() && p->getName() == piece->getName())
                {
                    simulatedPiece = p;
                    break;
                }
            }

            if (!simulatedPiece) continue;

            for (int j = 0; j < simulatedBoard.size(); j++)
            {
                Piece* target = simulatedBoard[j];
                if (target->getCoords() == validMoves[i] && target->getColor() != simulatedPiece->getColor())
                {
                    delete target;
                    simulatedBoard.erase(simulatedBoard.begin() + j);
                    break;
                }
            }

            simulatedPiece->setCoords(validMoves[i].first, validMoves[i].second);

            if (isCheck(whosTurn, simulatedBoard))
            {
                validMoves.erase(validMoves.begin() + i);
            }

            for (auto* p : simulatedBoard)
            {
                delete p;
            }
        }

        piece->emptyLegalMoves();
        for (auto& move : validMoves)
        {
            piece->legalMoves_Add(move);
        }
    }
}


bool Engine::isCheckmate(bool whosTurn)
{
    string color;
    if (whosTurn == 0) color = "white";
    else color = "black";

    Piece* king;
    for (auto piece : board)
    {
        if (color == piece->getColor() && piece->getName() == 'K')
        {
            king = piece;
            break;
        }
    }

    vector<pair<int, int>> kingLegalMoves = king->getLegalMoves();

    if (kingLegalMoves.empty())
    {
        for (auto piece : board)
        {
            if (piece->getColor() == color && piece->getName() != 'K')
            {
                if (!piece->getLegalMoves().empty()) return false;
            }
        }

        for (auto piece : board)
        {
            if (piece->getColor() != color && piece->getName() != 'K')
            {
                vector<pair<int, int>> attackingMoves = piece->getLegalMoves();
                for (auto attackMove : attackingMoves)
                {
                    if (isTakingAttackingPiece(piece, attackMove, king)) return false;
                }
            }
        }

        return true;
    }

    return false;
}


bool Engine::isTakingAttackingPiece(Piece* piece, pair<int, int> attackMove, Piece* king)
{
    for (auto attackingPiece : board)
    {
        if (attackingPiece->getColor() != piece->getColor() && attackingPiece->getName() != 'K')
        {
            vector<pair<int, int>> attackingMoves = attackingPiece->getLegalMoves();

            if (find(attackingMoves.begin(), attackingMoves.end(), king->getCoords()) != attackingMoves.end())
            {
                if (attackMove == attackingPiece->getCoords()) return true;
            }
        }
    }

    return false;
}

void Engine::promotion(vector<Piece*> board)
{
    for (auto piece : board)
    {
        if (piece->getColor() == "white")
        {
            if (piece->getName() == 'P' && piece->getCoords().second == 0) cout << "promotion\n";
        }
        else
        {
            if (piece->getName() == 'P' && piece->getCoords().second == 7) cout << "promotion\n";
        }
    }
}

