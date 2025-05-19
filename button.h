#ifndef BUTTON_H
#define BUTTON_H

#include "widget.h"
#include <string>

class Button : public Widget
{
public:
    Button(int x, int y, int sx, int sy, std::string _label)
        : Widget(x,y,sx,sy), label(_label) {}

    void draw() const override;
    void handle(int mx, int my, bool click);
    bool isPressed();
    bool is_inside(int mx, int my) const;

private:
    std::string label;
    bool pressed = false;
    bool was_clicked = false;
};

#endif // BUTTON_H
