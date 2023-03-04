#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>

#define DEFAULT_BLACK    "\033[39;40m"
#define DEFAULT_RED      "\033[39;41m"
#define DEFAULT_GREEN    "\033[39;42m"
#define DEFAULT_YELLOW   "\033[39;43m"
#define DEFAULT_BLUE     "\033[39;44m"
#define DEFAULT_MAGENTA  "\033[39;45m"
#define DEFAULT_CYAN     "\033[39;46m"
#define DEFAULT_WHITE    "\033[39;47m"

#define BLACK_BLACK      "\033[30;40m"
#define BLACK_RED        "\033[30;41m"
#define BLACK_GREEN      "\033[30;42m"
#define BLACK_YELLOW     "\033[30;43m"
#define BLACK_BLUE       "\033[30;44m"
#define BLACK_MAGENTA    "\033[30;45m"
#define BLACK_CYAN       "\033[30;46m"
#define BLACK_WHITE      "\033[30;47m"
#define BLACK_DEFAULT    "\033[30;49m"

#define RED_BLACK        "\033[31;40m"
#define RED_RED          "\033[31;41m"
#define RED_GREEN        "\033[31;42m"
#define RED_YELLOW       "\033[31;43m"
#define RED_BLUE         "\033[31;44m"
#define RED_MAGENTA      "\033[31;45m"
#define RED_CYAN         "\033[31;46m"
#define RED_WHITE        "\033[31;47m"
#define RED_DEFAULT      "\033[31;49m"

#define GREEN_BLACK      "\033[32;40m"
#define GREEN_RED        "\033[32;41m"
#define GREEN_GREEN      "\033[32;42m"
#define GREEN_YELLOW     "\033[32;43m"
#define GREEN_BLUE       "\033[32;44m"
#define GREEN_MAGENTA    "\033[32;45m"
#define GREEN_CYAN       "\033[32;46m"
#define GREEN_WHITE      "\033[32;47m"
#define GREEN_DEFAULT    "\033[32;49m"

#define YELLOW_BLACK     "\033[33;40m"
#define YELLOW_RED       "\033[33;41m"
#define YELLOW_GREEN     "\033[33;42m"
#define YELLOW_YELLOW    "\033[33;43m"
#define YELLOW_BLUE      "\033[33;44m"
#define YELLOW_MAGENTA   "\033[33;45m"
#define YELLOW_CYAN      "\033[33;46m"
#define YELLOW_WHITE     "\033[33;47m"
#define YELLOW_DEFAULT   "\033[33;49m"

#define BLUE_BLACK       "\033[34;40m"
#define BLUE_RED         "\033[34;41m"
#define BLUE_GREEN       "\033[34;42m"
#define BLUE_YELLOW      "\033[34;43m"
#define BLUE_BLUE        "\033[34;44m"
#define BLUE_MAGENTA     "\033[34;45m"
#define BLUE_CYAN        "\033[34;46m"
#define BLUE_WHITE       "\033[34;47m"
#define BLUE_DEFAULT     "\033[34;49m"

#define MAGENTA_BLACK    "\033[35;40m"
#define MAGENTA_RED      "\033[35;41m"
#define MAGENTA_GREEN    "\033[35;42m"
#define MAGENTA_YELLOW   "\033[35;43m"
#define MAGENTA_BLUE     "\033[35;44m"
#define MAGENTA_MAGENTA  "\033[35;45m"
#define MAGENTA_CYAN     "\033[35;46m"
#define MAGENTA_WHITE    "\033[35;47m"
#define MAGENTA_DEFAULT  "\033[35;49m"

#define CYAN_BLACK       "\033[36;40m"
#define CYAN_RED         "\033[36;41m"
#define CYAN_GREEN       "\033[36;42m"
#define CYAN_YELLOW      "\033[36;43m"
#define CYAN_BLUE        "\033[36;44m"
#define CYAN_MAGENTA     "\033[36;45m"
#define CYAN_CYAN        "\033[36;46m"
#define CYAN_WHITE       "\033[36;47m"
#define CYAN_DEFAULT     "\033[36;49m"

#define WHITE_BLACK      "\033[37;40m"
#define WHITE_RED        "\033[37;41m"
#define WHITE_GREEN      "\033[37;42m"
#define WHITE_YELLOW     "\033[37;43m"
#define WHITE_BLUE       "\033[37;44m"
#define WHITE_MAGENTA    "\033[37;45m"
#define WHITE_CYAN       "\033[37;46m"
#define WHITE_WHITE      "\033[37;47m"
#define WHITE_DEFAULT    "\033[37;49m"

#define DEFAULT          "\033[39;49m"
#define RESET            "\033[0;0m"
#define CARRIAGE_RETURN  "\r"
#define RETURN_PREV_LINE "\033[1A"
#define RETURN_START     "\033[H"
#define CLEAR            "\033c"
#define SAVE_CURSOR      "\0337"
#define LOAD_CURSOR      "\0338"
#define CURSOR_DOWN      "\033[B"
#define CURSOR_LEFT      "\033[D"
#define CURSOR_UP        "\033[A"
#define CURSOR_RIGHT     "\033[C"

#define GOTO_TEXT_START  "\033[3;40H"
#define GOTO_TEXT_MARGIN "\033[40G"
#define GOTO_SCORE_TEXT  "\033[8;47H"

#define GOTO_BOARD_START  "\033[3;3H"
#define GOTO_BOARD_MARGIN "\033[3G"

#define BOX_VERTICAL         "\u2551"
#define BOX_HORIZONTAL       "\u2550"
#define BOX_TOP_LEFT         "\u2554"
#define BOX_TOP_RIGHT        "\u2557"
#define BOX_BOTTOM_LEFT      "\u255A"
#define BOX_BOTTOM_RIGHT     "\u255D"

#define WIDTH         60
#define HEIGHT        30
#define SIZEOF_COLOUR 8
#define SIZEOF_CR     1
#define SIZEOF_RPL    4
#define SIZEOF_RS     3
#define SIZEOF_C      2
#define SIZEOF_SC     2
#define SIZEOF_LC     2


void render_background() {
    std::cout << CLEAR << RETURN_START;

    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        if ((i % WIDTH) == 0) {
            std::cout << std::endl;
        }

        std::cout << DEFAULT_BLACK << " ";
    }

    std::cout << SAVE_CURSOR;
}

void render_text() {
    std::cout 
        << GOTO_TEXT_START << WHITE_BLACK << "TETRIS" << CURSOR_DOWN
        << CURSOR_DOWN
        << GOTO_TEXT_MARGIN << "By Nathan Baines" << CURSOR_DOWN
        << CURSOR_DOWN
        << CURSOR_DOWN
        << GOTO_TEXT_MARGIN << "Score: 0";
}

void render_board() {
    std::cout << GOTO_BOARD_START;

    for (int i = 0; i < 20; i++) {
        std::cout << "\033[20P" << DEFAULT_BLACK << "\033[20@" << CURSOR_DOWN << GOTO_BOARD_MARGIN;
    }
    
    std::cout << WHITE_BLACK;

    std::cout << GOTO_BOARD_START << CURSOR_UP << CURSOR_LEFT << BOX_TOP_LEFT;

    for (int i = 0; i < 20; i++) {
        std::cout << BOX_HORIZONTAL;
    }

    std::cout << BOX_TOP_RIGHT << GOTO_BOARD_MARGIN << CURSOR_DOWN << CURSOR_LEFT;

    for (int i = 0; i < 20; i++) {
        std::cout << BOX_VERTICAL << CURSOR_DOWN << CURSOR_LEFT;
    }

    std::cout << BOX_BOTTOM_LEFT;

    for (int i = 0; i < 20; i++) {
        std::cout << BOX_HORIZONTAL;
    }

    std::cout << BOX_BOTTOM_RIGHT << CURSOR_UP << CURSOR_LEFT;

    for (int i = 0; i < 20; i++) {
        std::cout << BOX_VERTICAL << CURSOR_UP << CURSOR_LEFT;
    }
}