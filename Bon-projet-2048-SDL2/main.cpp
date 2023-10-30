#include <iostream>
#include <SDL.h>

const int CELL_SIZE = 100; // taille en pixel d'un game object

class GameObject {
public:
    int x, y, width, height;

    GameObject(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}

    void draw(SDL_Renderer* renderer) {
        SDL_Rect rect = { x, y, width, height };
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Couleur blanche
        SDL_RenderFillRect(renderer, &rect);
    }
};

/*class Grid {
private:
    GameObject tiles[4][4];
public:
    Grid() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                tiles[i][j] = GameObject(j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, 0); // VOIR GAME OBJECT PEUT ETRE A CHANGER
            }
        }

        void draw(SDL_Renderer * renderer) {
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    tiles[i][j].draw(renderer);
                }
            }
        }
    }
};*/

class Window {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

public:
    Window(int width, int height) {
        SDL_Init(SDL_INIT_VIDEO);
        window = SDL_CreateWindow("2048", 800, 400, width, height, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, NULL, SDL_RENDERER_ACCELERATED);
    }

    ~Window() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void display() {
        SDL_RenderPresent(renderer);
    }

    SDL_Renderer* getRenderer() {
        return renderer;
    }

    void clear() {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Couleur noire
        SDL_RenderClear(renderer);
    }

    bool isOpen() {
        SDL_Event open;
        while (SDL_PollEvent(&open)) {
            if (open.type == SDL_QUIT) {
                return false;
            }
        }
        return true;
    }
};

int main(int argc, char* args[]) {
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;

    Window window(SCREEN_WIDTH, SCREEN_HEIGHT);

    GameObject obj(100, 100, CELL_SIZE, CELL_SIZE);

    while (window.isOpen()) {
        window.clear();
        obj.draw(window.getRenderer());
        window.display();
    }

    return 0;
}