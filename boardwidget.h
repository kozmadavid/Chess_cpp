#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

#include "widget.h"
#include "piece.h"
#include <vector>

class BoardWidget : public Widget {
    std::vector<Piece*> board;

public:
    BoardWidget(int x, int y, int cell_size, const std::vector<Piece*>& board)
        : Widget(x, y, cell_size * 8, cell_size * 8), board(board) {}

    void draw() const override;
};

#endif // BOARDWIDGET_H
