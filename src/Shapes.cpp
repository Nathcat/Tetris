#include "Shapes.hpp"

bool overlaps_shape(int* board_map, int* shape_map) {
    for (int i = 0; i < 10; i++) {
        if ((board_map[i] & shape_map[i]) != 0) {
            return true;
        }
    }

    return false;
}

int* init_board_map() {
    int* p = new int[10];
    memset(p, 0, sizeof(int) * 10);
    return p;
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
        return false;
    }

    for (int i = 0; i < 10; i++) {
        *(shape_map + i) >>= 1;
    }

    return true;
};

bool Shape::Right(int* board_map) {
    if (x + width == 20) {
        return false;
    }

    x += 2;

    int* new_shape_map = init_board_map();
    memcpy(shape_map, new_shape_map + 1, sizeof(int) * 9);

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

    int* new_shape_map = init_board_map();
    memcpy(shape_map + 1, new_shape_map, sizeof(int) * 9);

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

    shape_map = init_board_map();

    *(shape_map + x) = (0x11 << y);
    *(shape_map + x + 1) = (0x11 << y);
};