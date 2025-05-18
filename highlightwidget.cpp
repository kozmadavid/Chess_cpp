#include "highlightwidget.h"
#include "graphics.hpp"

using namespace genv;

highlightwidget::highlightwidget(Piece* selected, int cell_size)
    : Widget(selected->getCoords().first * cell_size, selected->getCoords().second * cell_size, cell_size, cell_size),
      selected(selected) {}

void highlightwidget::draw() const {
    gout << color(255, 255, 0)
         << move_to(x, y) << line_to(x + width, y)
         << line_to(x + width, y + height) << line_to(x, y + height)
         << line_to(x, y);

    gout << move_to(x - 1, y - 1)
         << line_to(x + width - 1, y - 1)
         << line_to(x + width - 1, y + height - 1)
         << line_to(x - 1, y + height - 1)
         << line_to(x - 1, y - 1);
}
