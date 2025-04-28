#include "gui.h"

void GUI::drawBoard(const std::vector<Piece*>& board, int cell_size)
{
    for (auto widget : widgets) delete widget;
    widgets.clear();

    BoardWidget* boardWidget = new BoardWidget(0, 0, cell_size, board);
    addWidget(boardWidget);

    PieceWidget* pieceWidget = new PieceWidget(0, 0, cell_size, board);
    addWidget(pieceWidget);

    draw();
}


void GUI::drawSelectedMoves(int cell_size)
{
    if (selectedPiece == nullptr) return;

    std::vector<std::pair<int, int>> moves = selectedPiece->getLegalMoves();

    MoveHintWidget* hintWidget = new MoveHintWidget(moves, cell_size);
    addWidget(hintWidget);

    draw();
}

void GUI::drawHighlight(int cell_size)
{
    highlightwidget* highlightSelected = new highlightwidget(selectedPiece, cell_size);
    addWidget(highlightSelected);

    draw();
}

void GUI::setSelectedPiece(Piece* piece)
{
    selectedPiece = piece;
}
