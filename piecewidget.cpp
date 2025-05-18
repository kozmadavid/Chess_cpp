#include "piecewidget.h"
#include "graphics.hpp"
#include <fstream>
#include <sstream>

using namespace genv;

PieceWidget::PieceWidget(int x, int y, int cell_size, const std::vector<Piece*>& pieces)
    : Widget(x, y, cell_size * 8, cell_size * 8), pieces(pieces) {}


std::map<std::string, std::vector<Pixel>> PieceWidget::images;

std::vector<Pixel> PieceWidget::loadImage(const std::string& filename) const {
    std::vector<Pixel> pixels;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) return pixels;

    while (getline(file, line)) {
        std::stringstream ss(line);
        Pixel p;
        char comma;
        ss >> p.x >> comma >> p.y >> comma >> p.r >> comma >> p.g >> comma >> p.b;
        pixels.push_back(p);
    }
    return pixels;
}

void PieceWidget::draw() const {
    for (auto* piece : pieces) {
        std::string filename = (piece->getColor() == "white" ? "w" : "b") + std::string(1, piece->getName()) + ".txt";

        auto& imageMap = const_cast<std::map<std::string, std::vector<Pixel>>&>(images);

        if (imageMap.find(filename) == imageMap.end()) {
            imageMap[filename] = loadImage(filename);
        }

        auto& img = imageMap[filename];
        int px = x + piece->getCoords().first * (width / 8+1.25);
        int py = y + piece->getCoords().second * (height / 8+1.25);

        for (const auto& p : img) {
            if (!(p.r >= 150 && p.g == 0 && p.b == 0)) {
                gout << move_to(px + p.x, py + p.y)
                     << color(p.r, p.g, p.b)
                     << dot;
            }
        }
    }
}
