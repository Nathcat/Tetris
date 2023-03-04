#include "Shapes.hpp"

bool overlaps_shape(std::vector<Shape*> shapes, Shape* pShape) {
    for (int y = pShape->y; y < pShape->y + pShape->height; y++) {
        
        for (int x = pShape->x; x < pShape->x + pShape->width; x += 2) {
            
            for (int i = 0; i < shapes.size(); i++) {
                
                if (shapes.at(i)->occupies_position(shapes.at(i), x, y)) {
                    return true;
                }   
            }   
        }
    }

    return false;
}

void Shape::GotoPosition() {
    std::cout << GOTO_BOARD_START;

    for (int i = 0; i < x; i++) {
        std::cout << CURSOR_RIGHT;
    }

    for (int i = 0; i < y; i++) {
        std::cout << CURSOR_DOWN;
    }
};

bool Shape::Fall(std::vector<Shape*> shapes) {
    if (y + height == 20) {
        return false;
    }

    y++;

    if (overlaps_shape(shapes, this)) {
        y--;
        return false;
    }

    return true;
};

bool Shape::Right(std::vector<Shape*> shapes) {
    if (x + width == 20) {
        return false;
    }

    x += 2;

    if (overlaps_shape(shapes, this)) {
        x -= 2;
        return false;
    }

    draw_func(this);
    return true;
};

bool Shape::Left(std::vector<Shape*> shapes) {
    if (x == 0) {
        return false;
    }

    x -= 2;

    if (overlaps_shape(shapes, this)) {
        x += 2;
        return false;
    }

    draw_func(this);
    return true;
};

Square::Square(int X, int Y) {
    x = X;
    y = Y;
    width = 4;
    height = 2;

    draw_func = [](Shape* s) {
        s->GotoPosition();

        std::cout << DEFAULT_BLUE << "\033[4P" << "\033[4@" << CURSOR_DOWN << "\033[4P" << "\033[4@";
    };

    occupies_position = [](Shape* s, int X, int Y) {
        return
            (X == s->x && Y == s->y) ||
            (X == s->x && Y == s->y + 1) ||
            (X == s->x + 2 && Y == s->y) ||
            (X == s->x + 2 && Y == s->y + 1);
    };
};