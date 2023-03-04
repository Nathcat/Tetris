#include "CLI-Rendering.hpp"
#include "Shapes.cpp"

#include <string>
#include <thread>
#include <vector>
#include <cstdlib>
#include <time.h>

/**
 * Contains information required by the entire program about the state.
 */
struct program_state {
    bool running;
    Shape* falling_shape;
    int* board_map;
    std::vector<Shape*> shapes;
};

/**
 * Controls the left / right movement of shapes in a seperate thread.
 * @param state Pointer to the game state information
 */
void left_right_controller(struct program_state* state) {
    int r;
    
    while (state->running) {
        char a[3];
        r = system("stty raw");
        size_t size = read(0, a, 3);
        r = system("stty cooked");

        bool result;

        if (a[0] == 27 && a[1] == 91) {
            switch (a[2]) {
                case 67: result = state->falling_shape->Right(state->board_map); break;
                case 68: result = state->falling_shape->Left(state->board_map); break;
            }
        }
    }
};

/**
 * Chooses a new random shape.
 * @param state Pointer to the state struct.
 */
void new_random_shape(struct program_state* state) {
    state->shapes.push_back(state->falling_shape);
    
    for (int i = 0; i < 10; i++) {
        *(state->board_map + i) |= *(state->falling_shape->shape_map + i);
    }
    
    state->falling_shape = new Square(((rand() % 10) * 2), 0);

    if (state->falling_shape->x + state->falling_shape->width > 20) {
        state->falling_shape->x = 20 - state->falling_shape->width;
    }
};

int main() {
    // Seed the random generator
    srand(time(NULL));

    // Create the program state struct
    struct program_state* state = (struct program_state*) malloc(sizeof(program_state));

    // Each int represents a column, with the right hand side (small end) being the top of the column.
    state->board_map = init_board_map();
    
    // Set the running state to true
    state->running = true;

    // Make all text bold
    std::cout << "\033[1m";

    // Render the game
    render_background();
    render_text();
    render_board();

    // Create a new shape
    state->falling_shape = new Square(((rand() % 10) * 2), 0);

    if (state->falling_shape->x + state->falling_shape->width >= 20) {
        state->falling_shape->x = 20 - state->falling_shape->width;
    }

    // Draw the shape to the board
    state->falling_shape->draw_func(state->falling_shape);

    // Start the left / right controller
    std::thread left_right_controller_thread(left_right_controller, state);

    // Reset the cursor
    std::cout << LOAD_CURSOR << DEFAULT << std::endl;

    while (true) {
        // Wait on second
        sleep(1);

        // If the shape cant fall anymore (on the floor), create a new shape
        if (!state->falling_shape->Fall(state->board_map)) {
            new_random_shape(state);
        }

        // Re-render the board
        render_board();

        // Draw all the old shapes
        for (int i = 0; i < state->shapes.size(); i++) {
            state->shapes.at(i)->draw_func(state->shapes.at(i));
        }

        // Draw the active shape
        state->falling_shape->draw_func(state->falling_shape);

        // Reset the cursor
        std::cout << LOAD_CURSOR << DEFAULT << std::endl;
    }

    std::cout << LOAD_CURSOR << DEFAULT << std::endl;

    state->running = false;

    left_right_controller_thread.join();
    
    return 0;
};