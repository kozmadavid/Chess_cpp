#ifndef BUTTON_H
#define BUTTON_H

#include "widget.h"
#include <iostream>

class Button : public Widget
{
public:
    Button(int x, int y, int sx, int sy, std::string _label)
        : Widget(x,y,sx,sy) { label = _label; }

    std::string label;
    void draw() const override;
    bool is_inside(int mx, int my) const;
};

#endif // BUTTON_H
