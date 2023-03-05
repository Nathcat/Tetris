#include "Shapes.hpp"

bool overlaps_shape(int* board_map, int* shape_map) {
    for (int i = 0; i < 10; i++) {
        if ((board_map[i] & shape_map[i]) != 0) {
            return true;
        }
    }

    return false;
}


Shape::Shape(const Shape& b) {
    log("Shape copy ctor");
    
    x         = b.x;
    y         = b.y;
    width     = b.width;
    height    = b.height;
    shape_map = b.shape_map;
    draw_func = b.draw_func;
};

Shape::Shape(Shape&& b) {
    log("Shape move ctor");
    if (this != &b) {
        x         = b.x;
        y         = b.y;
        width     = b.width;
        height    = b.height;
        shape_map = b.shape_map;
        draw_func = b.draw_func;
        
        if (b.shape_map) {
            b.shape_map = nullptr;
        }
    
        if (b.draw_func) {
            b.draw_func = nullptr;
        }
    }
};

Shape& Shape::operator=(const Shape& b) {
    log("Shape copy assignment");
    x         = b.x;
    y         = b.y;
    width     = b.width;
    height    = b.height;
    shape_map = b.shape_map;
    draw_func = b.draw_func;

    return *this;
};

Shape& Shape::operator=(Shape&& b) {
    log("Shape move assignment");
    if (this == &b) {
        return *this;
    }
    
    x         = b.x;
    y         = b.y;
    width     = b.width;
    height    = b.height;
    shape_map = b.shape_map;
    draw_func = b.draw_func;

    if (b.shape_map) {
        b.shape_map = nullptr;
    }
    
    if (b.draw_func) {
        b.draw_func = nullptr;
    }

    return *this;
};

Shape::~Shape() {
    log("Shape dtor");
    draw_func = nullptr;
    delete[] shape_map;
};

void Shape::GotoPosition() {
    std::cout << GOTO_BOARD_START;

    for (int i = 0; i < x; i++) {
        std::cout << CURSOR_RIGHT;
    }

    for (int i = 0; i < y; i++) {
        std::cout << CURSOR_DOWN;
    }
};

bool Shape::Fall(int* board_map) {
    if (y + height == 20) {
        return false;
    }

    y++;

    for (int i = 0; i < 10; i++) {
        *(shape_map + i) <<= 1;
    }

    if (overlaps_shape(board_map, shape_map)) {
        y--;
        
        for (int i = 0; i < 10; i++) {
            *(shape_map + i) >>= 1;
        }
        
        return false;
    }

    return true;
};

bool Shape::Right(int* board_map) {
    if (x + width == 20) {
        return false;
    }

    x += 2;

    int* new_shape_map = new int[10];
    
    for (int i = 0; i < 9; i++) {
        *(new_shape_map + i + 1) = *(shape_map + i);
    }

    if (overlaps_shape(board_map, new_shape_map)) {
        x -= 2;
        return false;
    }

    shape_map = new_shape_map;

    draw_func(this);
    return true;
};

bool Shape::Left(int* board_map) {
    if (x == 0) {
        return false;
    }

    x -= 2;

    int* new_shape_map = new int[10];
    
    for (int i = 0; i < 9; i++) {
        *(new_shape_map + i) = *(shape_map + i + 1);
    }
    
    if (overlaps_shape(board_map, new_shape_map)) {
        x += 2;
        return false;
    }

    shape_map = new_shape_map;
    
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

    shape_map = new int[10];

    *(shape_map + (x / 2)) = (0b11 << y);
    *(shape_map + (x / 2) + 1) = (0b11 << y);
};
