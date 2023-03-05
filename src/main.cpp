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
    Shape falling_shape;
    int* board_map;
    std::vector<Shape> shapes;
};

/**
 * Controls the left / right movement of shapes in a seperate thread.
 * @param state Pointer to the game state information
 */
void left_right_controller(struct program_state* state) {
    log("l/r: Started");
    int r;
    
    while (state->running) {
        log("l/r: New iteration");
        char a[3];
        r = system("stty raw");
        size_t size = read(0, a, 3);
        r = system("stty cooked");

        log("l/r: Read character");
        
        bool result;

        if (a[0] == 27 && a[1] == 91) {
            log("l/r: Is arrow key");
            
            switch (a[2]) {
                case 67: result = state->falling_shape.Right(state->board_map); break;
                case 68: result = state->falling_shape.Left(state->board_map); break;
            }
        } else if (a[0] == 27) {
            log("l/r: Is escape key");
            
            state->running = false;
            exit(0);
        }
    }
};

/**
 * Chooses a new random shape.
 * @param state Pointer to the state struct.
 */
void new_random_shape(struct program_state* state) {
    log("new_random_shape(): Merging shape and board maps");
    for (int i = 0; i < 10; i++) {
        *(state->board_map + i) |= *(state->falling_shape.shape_map + i);
    }

    log("new_random_shape(): Pushing shape");
    state->shapes.push_back(state->falling_shape);

    log("new_random_shape(): Creating a new shape");
    Square s(((rand() % 10) * 2), 0);
    state->falling_shape = s;

    log("new_random_shape(): Checking shape location for edge overlap");
    if (state->falling_shape.x + state->falling_shape.width > 20) {
        state->falling_shape.x = 20 - state->falling_shape.width;
    }

    log("new_random_shape(): Done!");
};

bool has_lost(int* board_map) {
    for (int i = 0; i < 10; i++) {
        if ((*(board_map + i) & 1) == 1) {
            return true;
        }
    }

    return false;
};

void print_bits(int a, int count) {
    for (int i = count - 1; i >= 0; i--) {
        log_file << ((a >> i) & 1);
    }

    log_file << "\n";
}

int main() {
    log("----------PROGRAM START----------");

    log("Seeding random generator");
    
    // Seed the random generator
    srand(time(NULL));

    log("Making game state");
    
    // Create the program state struct
    struct program_state* state = (struct program_state*) malloc(sizeof(program_state));

    log("Creating board map");
    
    // Each int represents a column, with the right hand side (small end) being the top of the column.
    state->board_map = new int[10];
    
    // Set the running state to true
    state->running = true;

    // Make all text bold
    std::cout << "\033[1m";

    log("Initial rendering");
    
    // Render the game
    render_background();
    render_text();
    render_board();

    log("Making new shape");

    // Create a new shape
    Square s(((rand() % 10) * 2), 0);
    state->falling_shape = s;

    if (state->falling_shape.x + state->falling_shape.width >= 20) {
        state->falling_shape.x = 20 - state->falling_shape.width;
    }

    log("Drawing new shape");

    // Draw the shape to the board
    state->falling_shape.draw_func(&(state->falling_shape));

    log("Starting l/r controller");
    
    // Start the left / right controller
    std::thread left_right_controller_thread(left_right_controller, state);

    // Reset the cursor
    std::cout << LOAD_CURSOR << DEFAULT << std::endl;

    while (state->running) {
        log("----------NEW MAINLOOP----------");

        log("Board map:");
        for (int i = 0; i < 10; i++) {
            print_bits(state->board_map[i], 20);
        }

        log("Shape map:");
        for (int i = 0; i < 10; i++) {
            print_bits(state->falling_shape.shape_map[i], 20);
        }
        
        if (has_lost(state->board_map)) {
            log("has_lost() TRUE");
            int r = system("stty cooked");
            std::cout << CLEAR;
            render_background();
            std::cout << GOTO_BOARD_START << "YOU LOST!" << CURSOR_DOWN << GOTO_BOARD_MARGIN << CURSOR_DOWN << "Score: 0";
    
            break;
        }

        log("has_lost() FALSE");
        
        // Wait one second
        sleep(1);

        // If the shape cant fall anymore (on the floor), create a new shape
        if (!state->falling_shape.Fall(state->board_map)) {
            log("Fall() FALSE");
            new_random_shape(state);
        }

        log("Fall() TRUE");
        
        // Re-render the board
        render_board();

        // Draw all the old shapes
        for (int i = 0; i < state->shapes.size(); i++) {
            state->shapes.at(i).draw_func(&(state->shapes.at(i)));
        }

        // Draw the active shape
        state->falling_shape.draw_func(&(state->falling_shape));

        log("Drawing done");
        
        // Reset the cursor
        std::cout << LOAD_CURSOR << DEFAULT << std::endl;
    }

    log("Ending...");

    log_file.close();
    
    std::cout << LOAD_CURSOR << DEFAULT << std::endl;

    state->running = false;

    left_right_controller_thread.join();

    return 0;
};