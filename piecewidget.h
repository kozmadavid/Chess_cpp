#ifndef PIECEWIDGET_H
#define PIECEWIDGET_H

#include "widget.h"
#include "piece.h"
#include <map>
#include <vector>
#include <string>

struct Pixel {
    int x, y, r, g, b;
};

class PieceWidget : public Widget {
    std::vector<Piece*> pieces;
    static std::map<std::string, std::vector<Pixel>> images;

    std::vector<Pixel> loadImage(const std::string& filename) const;
public:
    PieceWidget(int x, int y, int cell_size, const std::vector<Piece*>& pieces);
    void draw() const override;
};

#endif // PIECEWIDGET_H
