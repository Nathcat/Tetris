#ifndef DEFAULT
#include "CLI-Rendering.hpp"
#endif

#include <vector>


class Shape {
public:
    int x, y, width, height;

    void (*draw_func)(Shape* s);
    bool (*occupies_position)(Shape* s, int X, int Y);

    void GotoPosition();
    bool Fall(std::vector<Shape*> shapes);
    bool Right(std::vector<Shape*> shapes);
    bool Left(std::vector<Shape*> shapes);
};


class Square : public Shape {
public:
    Square(int X, int Y);
};


bool overlaps_shape(std::vector<Shape*> shapes, Shape* pShape);
