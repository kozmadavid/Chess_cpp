#ifndef WIDGET_H
#define WIDGET_H

#include <vector>

class Widget
{
protected:
    int x, y, width, height;

public:
    Widget(int x, int y, int width, int height);
    virtual ~Widget() {}
    virtual void draw() const = 0;
};

#endif // WIDGET_H
