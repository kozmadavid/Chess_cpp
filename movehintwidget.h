#ifndef MOVEHINTWIDGET_H
#define MOVEHINTWIDGET_H

#include "widget.h"
#include <vector>

class MoveHintWidget : public Widget {
    std::vector<std::pair<int, int>> moves;
    int cell_size;

    void draw_circle(int x0, int y0, int r) const;

public:
    MoveHintWidget(const std::vector<std::pair<int, int>>& moves, int cell_size);
    void draw() const override;
};

#endif // MOVEHINTWIDGET_H
