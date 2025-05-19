#ifndef GUI_HPP
#define GUI_HPP

#include "graphics.hpp"
#include "piece.h"
#include "boardwidget.h"
#include "piecewidget.h"
#include "movehintwidget.h"
#include "highlightwidget.h"
#include "menuwidget.h"
#include "endscreenwidget.h"
#include "button.h"
#include <vector>

const int XX = 800;
const int YY = 800;

class GUI
{
private:
    bool startPressed = false;
    bool exitPressed = false;

    std::vector<Widget*> menuWidgets;
    std::vector<Widget*> boardWidgets;
    std::vector<Piece*> pieces;

    Piece* selectedPiece = nullptr;

    bool boardLoaded = false;

    void addMenuWidget(Widget* widget) { menuWidgets.push_back(widget); }
    void addBoardWidget(Widget* widget) { boardWidgets.push_back(widget); }

    int cell_size = XX/8;

    //MENU CONTENTS
    menuwidget* menu = new menuwidget(0, 0, cell_size);
    Button* start = new Button(325, 400, 150, 40, "Start");
    Button* exit = new Button(325, 470, 150, 40, "Exit");
    EndScreenWidget* endScreen = nullptr;

    //BOARD CONTENTS
    BoardWidget* boardWidget = new BoardWidget(0, 0, cell_size);
    PieceWidget* pieceWidget = new PieceWidget(0, 0, cell_size, pieces);
    highlightwidget* highlightSelected = nullptr;
    MoveHintWidget* moveHint = nullptr;


public:
    GUI() { genv::gout.open(XX,YY); }

    ~GUI() { for (auto widget : menuWidgets) delete widget;
             for (auto widget : boardWidgets) delete widget;
           }

    void handleMouse(int mx, int my, bool click);
    void setPieces(std::vector<Piece*>&board);

    void setSelectedPiece(Piece* selected);
    void drawSelectedMoves(int cell_size);

    void loadMenu();
    void drawMenu();

    void loadBoard();
    void drawBoardContents();

    void loadEndSreen(std::string);
    void drawEndScreen();

    bool isStartPressed();
    bool isExitPressed();

    void getWidgetNum();
};

#endif // GUI_HPP
