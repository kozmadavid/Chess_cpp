#include "movehintwidget.h"
#include "graphics.hpp"

using namespace genv;

MoveHintWidget::MoveHintWidget(const std::vector<std::pair<int, int>>& moves, int cell_size)
    : Widget(0, 0, cell_size * 8, cell_size * 8), moves(moves), cell_size(cell_size) {}

void MoveHintWidget::draw_circle(int x0, int y0, int r) const
{
    for (int y = -r; y <= r; ++y)
    {
        for (int x = -r; x <= r; ++x)
        {
            if (x * x + y * y <= r * r) gout << move_to(x0 + x, y0 + y) << dot;
        }
    }
}

void MoveHintWidget::draw() const
{
    gout << color(100, 100, 100);
    for (const auto& move : moves)
    {
        draw_circle(move.first * cell_size + cell_size / 2,
                    move.second * cell_size + cell_size / 2, 15);
    }
}
