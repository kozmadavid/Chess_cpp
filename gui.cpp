#include "gui.h"
#include <algorithm>


void GUI::loadMenu()
{
    addMenuWidget(menu);
    addMenuWidget(start);
    addMenuWidget(exit);
}

void GUI::loadBoard()
{
    addBoardWidget(boardWidget);
}

void GUI::loadEndSreen(std::string label)
{
    endScreen = new EndScreenWidget(0, 0, cell_size,label);
}

void GUI::setPieces(std::vector<Piece*>& board)
{
    pieces = board;

    if (pieceWidget)
    {
        auto it = std::remove(boardWidgets.begin(), boardWidgets.end(), pieceWidget);
        boardWidgets.erase(it, boardWidgets.end());

        delete pieceWidget;
        pieceWidget = nullptr;
    }
    pieceWidget = new PieceWidget(0, 0, cell_size, pieces);
    addBoardWidget(pieceWidget);
}


void GUI::setSelectedPiece(Piece* piece)
{
    if (highlightSelected)
    {
        auto it = std::remove(boardWidgets.begin(), boardWidgets.end(), highlightSelected);
        boardWidgets.erase(it, boardWidgets.end());

        auto it2 = std::remove(boardWidgets.begin(), boardWidgets.end(), moveHint);
        boardWidgets.erase(it2, boardWidgets.end());

        delete highlightSelected;
        delete moveHint;
        highlightSelected = nullptr;
        moveHint = nullptr;
    }

    selectedPiece = piece;

    if (selectedPiece)
    {
        highlightSelected = new highlightwidget(selectedPiece, cell_size);
        addBoardWidget(highlightSelected);

        moveHint = new MoveHintWidget(selectedPiece->getLegalMoves(), cell_size);

        auto it = std::remove(boardWidgets.begin(), boardWidgets.end(), moveHint);
        boardWidgets.erase(it, boardWidgets.end());

        boardWidgets.push_back(moveHint);
    }
}

void GUI::drawMenu()
{
    for (auto widget : menuWidgets) widget->draw();
}

void GUI::drawBoardContents()
{
    if (boardWidget) boardWidget->draw();

    for (auto widget : boardWidgets) if (dynamic_cast<PieceWidget*>(widget) != nullptr) widget->draw();

    if (highlightSelected) highlightSelected->draw();

    if (moveHint) moveHint->draw();
}

void GUI::drawEndScreen()
{
    endScreen->draw();
}

void GUI::handleMouse(int mx, int my, bool click)
{
    start->handle(mx, my, click);
    exit->handle(mx, my, click);

    if (start->isPressed()) startPressed = true;
    if (exit->isPressed())  exitPressed = true;

}

bool GUI::isStartPressed()
{
    if (startPressed)
    {
        startPressed = false;
        return true;
    }
    return false;
}

bool GUI::isExitPressed()
{
    if (exitPressed)
    {
        exitPressed = false;
        return true;
    }
    return false;
}
