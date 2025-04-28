#ifndef GUI_HPP
#define GUI_HPP

#include "graphics.hpp"
#include "widget.h"
#include "piece.h"
#include "boardwidget.h"
#include "piecewidget.h"
#include "movehintwidget.h"
#include "highlightwidget.h"
#include <vector>

const int XX = 800;
const int YY = 800;

class GUI {
private:
    std::vector<Widget*> widgets;
    Piece* selectedPiece = nullptr;

    void addWidget(Widget* widget) { widgets.push_back(widget); }

    void draw() const {
        for (auto widget : widgets) {
            widget->draw();
        }
    }

public:
    GUI() { genv::gout.open(XX,YY); }

    ~GUI() { for (auto widget : widgets) delete widget; }

    void drawBoard(const std::vector<Piece*>& board, int cell_size);
    void setSelectedPiece(Piece* selected);
    void drawSelectedMoves(int cell_size);
    void drawHighlight(int cell_size);
};

#endif // GUI_HPP
