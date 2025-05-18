#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include "widget.h"
#include <vector>
#include <string>

class menuwidget : public Widget {

public:
    menuwidget(int x, int y, int cell_size)
        : Widget(x, y, cell_size*8, cell_size*8) {}

    void draw() const override;
};

#endif // MENUWIDGET_H
