#ifndef DEFAULT
#include "CLI-Rendering.hpp"
#endif

#include <vector>


class Shape {
public:
    int x, y, width, height;
    int* shape_map;

    void (*draw_func)(Shape* s);

    void GotoPosition();
    bool Fall(int* board_map);
    bool Right(int* board_map);
    bool Left(int* board_map);
};


class Square : public Shape {
public:
    Square(int X, int Y);
};


bool overlaps_shape(int* board_map, int* shape_map);

int* init_board_map();
