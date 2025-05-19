#ifndef ENDSCREENWIDGET_H
#define ENDSCREENWIDGET_H

#include "widget.h"
#include <vector>
#include <string>

class EndScreenWidget : public Widget {

public:
    EndScreenWidget(int x, int y, int cell_size, std::string _label)
        : Widget(x, y, cell_size*8, cell_size*8), label(_label) {}

    void draw() const override;
private:
    std::string label;
};

#endif // ENDSCREENWIDGET_H
