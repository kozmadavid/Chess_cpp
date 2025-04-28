#ifndef HIGHLIGHTWIDGET_H
#define HIGHLIGHTWIDGET_H

#include "widget.h"
#include "piece.h"

class highlightwidget : public Widget {
    Piece* selected;
public:
    highlightwidget(Piece* selected, int cell_size);
    void draw() const override;
};

#endif // HIGHLIGHTWIDGET_H
