#include "menuwidget.h"
#include "graphics.hpp"

using namespace genv;

void menuwidget::draw() const
{
    bool wOrB = true;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            gout << move_to(x + i * width / 8, y + j * height / 8)
                 << color(wOrB ? 200 : 220, wOrB ? 200 : 220, wOrB ? 200 : 220)
                 << box(width / 8, height / 8);
            wOrB = !wOrB;
        }
        wOrB = !wOrB;
    }
    gout.load_font("LiberationSans-Regular.ttf", 150);
    gout << color(50, 50, 50)
         << move_to(x+width/2/2-15, y+height/9)
         << text("Chess");
}
