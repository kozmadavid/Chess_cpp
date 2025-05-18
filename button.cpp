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

    gout << move_to(x+width/5, y)
         << color(50,50,50)
         << text(label);

    if (isPressed()) {
        gout << move_to(x + 2, y + 2)
             << color(150, 150, 150)
             << box(width - 4, height - 4);
    }
}

bool Button::isPressed() const
{
    return false;
}
