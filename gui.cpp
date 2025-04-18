#include "gui.h"
#include "graphics.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>

using namespace genv;

const int XX = 800;
const int YY = 800;
const int CELL_SIZE = 100;

map<string, vector<Pixel>> pieceImages;

GUI::GUI() {
    gout.open(XX, YY);
}

vector<Pixel> GUI::loadPieceImage(const string& filename) {
    if (pieceImages.find(filename) == pieceImages.end()) {
        pieceImages[filename] = readImage(filename);
    }
    return pieceImages[filename];
}

void GUI::drawBoard(vector<Piece*> board) {
    bool wOrB = true;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (wOrB) {
                gout << color(230, 188, 125);
            } else {
                gout << color(183, 139, 73);
            }
            gout << move_to(i * CELL_SIZE, j * CELL_SIZE) << box(CELL_SIZE, CELL_SIZE);
            wOrB = !wOrB;
        }
        wOrB = !wOrB;
    }
    drawPieces(board);
}

void GUI::drawSelected(Piece* selected) {
    int x = selected->getCoords().first * CELL_SIZE;
    int y = selected->getCoords().second * CELL_SIZE;

    gout << move_to(x, y) << color(255, 255, 0)
         << line_to(x + CELL_SIZE, y) << line_to(x + CELL_SIZE, y + CELL_SIZE)
         << line_to(x, y + CELL_SIZE) << line_to(x, y);

    gout << move_to(x - 1, y - 1)
         << line_to(x + CELL_SIZE - 1, y - 1)
         << line_to(x + CELL_SIZE - 1, y + CELL_SIZE - 1)
         << line_to(x - 1, y + CELL_SIZE - 1)
         << line_to(x - 1, y - 1);
}

void draw_circle(int x0, int y0, int r) {
    for (int y = -r; y <= r; y++) {
        for (int x = -r; x <= r; x++) {
            if (x * x + y * y <= r * r)
                gout << move_to(x0 + x, y0 + y) << dot;
        }
    }
}

vector<Pixel> GUI::readImage(const string& filename) {
    vector<Pixel> pixels;
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cerr << "Image file: " << filename << " can not be opened!\n";
        return pixels;
    }

    while (getline(file, line)) {
        stringstream ss(line);
        string value;
        Pixel p;

        getline(ss, value, ',');
        p.x = stoi(value);
        getline(ss, value, ',');
        p.y = stoi(value);
        getline(ss, value, ',');
        p.r = stoi(value);
        getline(ss, value, ',');
        p.g = stoi(value);
        getline(ss, value, ',');
        p.b = stoi(value);

        pixels.push_back(p);
    }

    file.close();
    return pixels;
}

void GUI::drawPieces(vector<Piece*> board) {
    for (auto piece : board) {
        string filename;

        if (piece->getColor() == "white") {
            filename = "w" + string(1, piece->getName()) + ".txt";
        } else {
            filename = "b" + string(1, piece->getName()) + ".txt";
        }

        vector<Pixel> image = loadPieceImage(filename);

        if (image.empty()) continue;

        int x = piece->getCoords().first * CELL_SIZE + 7.5;
        int y = piece->getCoords().second * CELL_SIZE + 7.5;

        for (const auto& pixel : image) {
            if (!(pixel.r >= 150 && pixel.g == 0 && pixel.b == 0)) {
                gout << move_to(x + pixel.x, y + pixel.y)
                     << color(pixel.r, pixel.g, pixel.b)
                     << dot;
            }
        }
    }
}

void GUI::drawSelectedMoves(vector<pair<int, int>> LegalMoves) {
    for (auto move : LegalMoves) {
        gout << color(100, 100, 100);
        draw_circle(move.first * CELL_SIZE + CELL_SIZE / 2, move.second * CELL_SIZE + CELL_SIZE / 2, 15);
    }
}
