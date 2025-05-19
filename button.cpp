#include "button.h"
#include "graphics.hpp"

using namespace genv;

void Button::draw() const
{
    gout.load_font("LiberationSans-Regular.ttf", 40);


    gout << move_to(x, y)
         << color(0, 0, 0)
         << box(width, height);

    gout << move_to(x+2, y+2)
         << color(255, 255, 255)
         << box(width-4, height-4);

    gout << move_to(x+width/5, y-4)
         << color(50, 50, 50)
         << text(label);
}

bool Button::is_inside(int mx, int my) const
{
    return mx >= x && mx <= x + width &&
           my >= y && my <= y + height;
}

void Button::handle(int mx, int my, bool click)
{
    if (click && is_inside(mx, my)) {
        if (!was_clicked) {
            pressed = true;
        } else {
            pressed = false;
        }
        was_clicked = true;
    }
    else {
        pressed = false;
        was_clicked = false;
    }
}

bool Button::isPressed()
{
    bool tmp = pressed;
    pressed = false;
    return tmp;
}
