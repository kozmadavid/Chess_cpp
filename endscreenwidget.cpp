#include "endscreenwidget.h"
#include "graphics.hpp"

using namespace genv;

void EndScreenWidget::draw() const
{
    gout.load_font("LiberationSans-Regular.ttf", 60);

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

    int text_width = gout.twidth(label);
    int text_height = 60;
    int text_x = x + (width - text_width) / 2;
    int text_y = y + (height + text_height) / 3;

    gout << move_to(text_x, text_y)
         << color(50, 50, 50)
         << text(label);
}
