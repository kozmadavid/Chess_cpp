#include "boardwidget.h"
#include "graphics.hpp"

using namespace genv;

void BoardWidget::draw() const {
    bool wOrB = true;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            gout << move_to(x + i * width / 8, y + j * height / 8)
                 << color(wOrB ? 230 : 183, wOrB ? 188 : 139, wOrB ? 125 : 73)
                 << box(width / 8, height / 8);
            wOrB = !wOrB;
        }
        wOrB = !wOrB;
    }
}
