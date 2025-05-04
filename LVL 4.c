#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include<time.h>
#include<stdlib.h>
#include<stdbool.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include "Variables.h"
#include "input_lvl4.h"
#include "sprite animation.h"
#include "Sprite_render.h"
#include "collision.h"
#include "iori_fight.h"
#include "kyo_algorithm_hard.h"
#include "set & reset.h"
#include "texture_destination_setup.h"
//#include "texture_destination_setup.h"

SDL_Texture* initialize_texture_from_file(const char* file_name, SDL_Renderer* renderer);
#include "Image_process.h"


// Constants for tile size and screen size
#define TILE_SIZE 40
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MAP_WIDTH 160
#define MAP_HEIGHT 15

// Define tile types
#define TILE_EMPTY 0
#define TILE_GROUND 1
#define TILE_BRICK 2
#define TILE_COIN 3
#define MOVEMENT_SPEED 5
#define ANIMATION_SPEED 50 // Milliseconds per frame
#define FALSE 0
#define TRUE 1



// Define maximum camera movement speed
//#define CAMERA_SPEED 20


SDL_Texture* sprite_texture[5][4];
SDL_Rect sprite = { 20, 100, 40, 40 };
SDL_Texture* textures1[9];
SDL_Texture* textures2[10];
SDL_Texture* textures3[10];
Mix_Chunk* jump;
SDL_Texture* game_Over;
SDL_Texture* game_Over1;
SDL_Texture* game_Win;
Mix_Chunk* effect;
Mix_Chunk* iori_effect;
//SDL_Window* window;
//SDL_Renderer* renderer;
//int game_is_running = FALSE;
int death=0;
int OBSTACLE_SPEED = 9;
int difficulty = 1;
int creds = 0;
int a = 0;
int startColumn;
int endColumn;
int jumping = 0;
int falling = 1;
int jumpStartY;
int map = 3;
int gameMap1[MAP_HEIGHT][MAP_WIDTH];
int gameMap2[MAP_HEIGHT][MAP_WIDTH];
int gameMap3[MAP_HEIGHT][MAP_WIDTH];
int cameraX = 0;
int movingRight = 0;
int movingLeft = 0;
int game_over = 0;
int frame = 0; // Current frame of the animation
int walkingDirection = 0; // 0: right, 1: left
Uint32 walkingTimer = 0; // Timer for walking animation
SDL_Event event;
int quit = 0;
const int FONT_SIZE = 24;
const int DELAY = 50;
const char* MENU_OPTIONS[] = { "Start Game", "Credits", "Options" };
const char* DIFFICULTY_OPTIONS[] = { "EASY", "MEDIUM", "HARD" };
const int MENU_OPTIONS_COUNT = 3;
const char* NAMES[] = { "S.M. FAHIM ABRAR(220041105)", "MOHAMMAD SADMAN SAAD(220041115)", "TASNIF EMRAN EKANTO(220041135)" };
const int NAME_COUNT = 3;
//const int FONT_SIZE_TITLE = 90;
//const int FONT_SIZE_PRESS_TO_START = 60;
const int FONT_SIZE_MENU = 60;
//const SDL_Color TEXT_COLOR = { 255, 255, 255, 255 }; // White
//const char* TITLE_TEXT = "OBSTACLE MAYHEM";
//const char* PRESS_TO_START_TEXT = "Press Enter To Start";
const char* OPTIONS_TEXT = "DIFFICULTY";
TTF_Font* fontPressToStart;
TTF_Font* fontTitle;
SDL_Texture* pressToStartTexture;
SDL_Texture* backgroundTexture;
SDL_Texture* titleTexture;
SDL_Texture* obstacleTexture;
SDL_Texture* obstacle2Texture;
SDL_Rect obstacle = { 0,0,40,40 };
SDL_Rect obstacle1 = { 0,-300,40,40 };
SDL_Rect obstacle2 = { 0,-600,40,40 };
SDL_Rect obstacle3 = { 0,-900,40,40 };
SDL_Rect obstacle4 = { 0,440,40,40 };
int titleWidth = 0, titleHeight = 0;
int pressToStartWidth = 0, pressToStartHeight = 0;
//SDL_Texture* tile_texture = NULL;
//SDL_Rect select_tile = { 0,0,40,40 };
// Jump speed and height
int jumpSpeed = 20;
int jumpHeight = 200;
int characterBottom; // Bottom y-coordinate of the character
int characterRight;  // Right x-coordinate of the character
int characterLeft;
int music = 0;
// Function to initialize SDL
void initializeSDL() {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    // if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
      //   printf("SDL_mixer could not initialize! Mix_Error: %s\n", Mix_GetError());
         //exit(-1);
  //   }
}
SDL_Texture* loadTextTexture(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    if (!surface) {
        printf("Failed to render text: %s\n", TTF_GetError());
        return NULL;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        printf("Failed to create texture from surface: %s\n", SDL_GetError());
    }
    return texture;
}
int credit_screen(SDL_Renderer* renderer) {

    TTF_Font* font = TTF_OpenFont("PlayfairDisplay-ExtraBold.ttf", FONT_SIZE);
    if (!font) {
        printf("Failed to load font: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    SDL_Texture* bg = IMG_LoadTexture(renderer, "golden.png");
    SDL_Texture* nameTextures[3];
    int nameWidths[3];
    int nameHeights[3];
    SDL_Color color = { 0,0,0,255 };
    for (int i = 0; i < NAME_COUNT; i++) {
        nameTextures[i] = loadTextTexture(renderer, font, NAMES[i], color);
        if (!nameTextures[i]) {
            for (int j = 0; j < i; j++) {
                SDL_DestroyTexture(nameTextures[j]);
            }
            TTF_CloseFont(font);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            TTF_Quit();
            SDL_Quit();
            return 1;
        }
        SDL_QueryTexture(nameTextures[i], NULL, NULL, &nameWidths[i], &nameHeights[i]);
    }

    TTF_CloseFont(font);

    bool quit = false;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    creds = 0;
                    for (int i = 0; i < NAME_COUNT; i++) {
                        SDL_DestroyTexture(nameTextures[i]);
                    }
                    quit = true;

                }
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, bg, NULL, NULL);
        for (int i = 0; i < NAME_COUNT; i++) {
            SDL_Rect nameRect = { (SCREEN_WIDTH - nameWidths[i]) / 2, 150 + i * 100, nameWidths[i], nameHeights[i] };
            SDL_RenderCopy(renderer, nameTextures[i], NULL, &nameRect);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }

    for (int i = 0; i < NAME_COUNT; i++) {
        SDL_DestroyTexture(nameTextures[i]);
    }

    return 0;
}


//ekanto
int initialize_window(void)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "Error initializing SDL.\n");
        return FALSE;
    }


    window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS);
    if (!window)
    {
        fprintf(stderr, "Error creating SDL Window\n");
        return FALSE;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); //cal the refresh rate of the monitor
    if (!renderer)
    {
        fprintf(stderr, "Error creating SDL renderer.\n");
        return FALSE;
    }

    return TRUE;

}

void renderSprite() {
    SDL_RenderCopy(renderer, sprite_texture[walkingDirection][frame], NULL, &sprite);
}
void loadObstacle() {
    obstacleTexture = IMG_LoadTexture(renderer, "spike.png");
    obstacle2Texture = IMG_LoadTexture(renderer, "tnt.jpg");
}
// lvl4 not need
int options_screen(SDL_Renderer* renderer) {
    SDL_Texture* backgroundTexture = IMG_LoadTexture(renderer, "redhell.jpg");
    if (!backgroundTexture) {
        printf("Failed to load background texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 0;
    }

    TTF_Font* fontTitle = TTF_OpenFont("Honk-Regular-VariableFont_MORF,SHLN.ttf", FONT_SIZE_TITLE);
    TTF_Font* fontMenu = TTF_OpenFont("Micro5-Regular.ttf", FONT_SIZE_MENU);
    if (!fontTitle || !fontMenu) {
        printf("Failed to load font: %s\n", TTF_GetError());
        SDL_DestroyTexture(backgroundTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 0;
    }

    SDL_Texture* titleTexture = loadTextTexture(renderer, fontTitle, OPTIONS_TEXT, TEXT_COLOR);
    if (!titleTexture) {
        TTF_CloseFont(fontTitle);
        TTF_CloseFont(fontMenu);
        SDL_DestroyTexture(backgroundTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 0;
    }

    SDL_Texture* optionsTextures[3];
    int optionsWidths[3];
    int optionsHeights[3];
    for (int i = 0; i < 3; i++) {
        optionsTextures[i] = loadTextTexture(renderer, fontMenu, DIFFICULTY_OPTIONS[i], TEXT_COLOR);
        if (!optionsTextures[i]) {
            for (int j = 0; j < i; j++) {
                SDL_DestroyTexture(optionsTextures[j]);
            }
            SDL_DestroyTexture(titleTexture);
            TTF_CloseFont(fontTitle);
            TTF_CloseFont(fontMenu);
            SDL_DestroyTexture(backgroundTexture);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            TTF_Quit();
            SDL_Quit();
            return 0;
        }
        SDL_QueryTexture(optionsTextures[i], NULL, NULL, &optionsWidths[i], &optionsHeights[i]);
    }

    TTF_CloseFont(fontTitle);
    TTF_CloseFont(fontMenu);

    int titleWidth, titleHeight;
    SDL_QueryTexture(titleTexture, NULL, NULL, &titleWidth, &titleHeight);

    bool quit = false;
    int selectedOption = 0;
    while (!quit && !creds) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_UP) {
                    selectedOption = (selectedOption - 1 + MENU_OPTIONS_COUNT) % MENU_OPTIONS_COUNT;
                }
                else if (event.key.keysym.sym == SDLK_DOWN) {
                    selectedOption = (selectedOption + 1) % MENU_OPTIONS_COUNT;
                }
                else if (event.key.keysym.sym == SDLK_RETURN) {
                    if (selectedOption == 0) {
                        // Start game
                        difficulty = 0;
                        for (int i = 0; i < MENU_OPTIONS_COUNT; i++) {
                            SDL_DestroyTexture(optionsTextures[i]);
                        }
                        quit = true;
                    }
                    else if (selectedOption == 1) {
                        difficulty = 1;
                        for (int i = 0; i < MENU_OPTIONS_COUNT; i++) {
                            SDL_DestroyTexture(optionsTextures[i]);
                        }
                        quit = true;

                    }
                    else if (selectedOption == 2) {
                        difficulty = 2;
                        for (int i = 0; i < MENU_OPTIONS_COUNT; i++) {
                            SDL_DestroyTexture(optionsTextures[i]);
                        }
                        quit = true;
                    }
                }
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

        SDL_Rect titleRect = { (SCREEN_WIDTH - titleWidth) / 2, 50, titleWidth, titleHeight };
        SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);

        for (int i = 0; i < MENU_OPTIONS_COUNT; i++) {
            SDL_Rect menuRect = { (SCREEN_WIDTH - optionsWidths[i]) / 2, 200 + i * 100, optionsWidths[i], optionsHeights[i] };
            if (i == selectedOption) {
                SDL_SetTextureColorMod(optionsTextures[i], 135, 206, 235); // Highlight selected option
            }
            else {
                SDL_SetTextureColorMod(optionsTextures[i], 255, 255, 255);
            }
            SDL_RenderCopy(renderer, optionsTextures[i], NULL, &menuRect);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(10); // Control frame rate
    }

    for (int i = 0; i < MENU_OPTIONS_COUNT; i++) {
        SDL_DestroyTexture(optionsTextures[i]);
    }
    SDL_DestroyTexture(titleTexture);
    SDL_DestroyTexture(backgroundTexture);
    //  SDL_DestroyRenderer(renderer);
    //  SDL_DestroyWindow(window);
    //  TTF_Quit();
     // SDL_Quit();
    return selectedOption == 0 ? 1 : 0; // Return 1 to start game, 0 otherwise
}
int start_screen(SDL_Renderer* renderer) {
    SDL_Texture* backgroundTexture = IMG_LoadTexture(renderer, "background.jpeg");
    if (!backgroundTexture) {
        printf("Failed to load background texture: %s\n", SDL_GetError());
        return 0;
    }

    TTF_Font* fontTitle = TTF_OpenFont("Honk-Regular-VariableFont_MORF,SHLN.ttf", FONT_SIZE_TITLE);
    TTF_Font* fontMenu = TTF_OpenFont("Micro5-Regular.ttf", FONT_SIZE_MENU);
    if (!fontTitle || !fontMenu) {
        printf("Failed to load font: %s\n", TTF_GetError());
        SDL_DestroyTexture(backgroundTexture);
        return 0;
    }

    SDL_Texture* titleTexture = loadTextTexture(renderer, fontTitle, TITLE_TEXT, TEXT_COLOR);
    if (!titleTexture) {
        TTF_CloseFont(fontTitle);
        TTF_CloseFont(fontMenu);
        SDL_DestroyTexture(backgroundTexture);
        return 0;
    }

    SDL_Texture* menuTextures[3];
    int menuWidths[3];
    int menuHeights[3];
    for (int i = 0; i < 3; i++) {
        menuTextures[i] = loadTextTexture(renderer, fontMenu, MENU_OPTIONS[i], TEXT_COLOR);
        if (!menuTextures[i]) {
            for (int j = 0; j < i; j++) {
                SDL_DestroyTexture(menuTextures[j]);
            }
            SDL_DestroyTexture(titleTexture);
            TTF_CloseFont(fontTitle);
            TTF_CloseFont(fontMenu);
            SDL_DestroyTexture(backgroundTexture);
            return 0;
        }
        SDL_QueryTexture(menuTextures[i], NULL, NULL, &menuWidths[i], &menuHeights[i]);
    }

    TTF_CloseFont(fontTitle);
    TTF_CloseFont(fontMenu);

    int titleWidth, titleHeight;
    SDL_QueryTexture(titleTexture, NULL, NULL, &titleWidth, &titleHeight);

    bool quit = false;
    Mix_Music* bgMusic = Mix_LoadMUS("menu.wav");
    if (bgMusic == NULL) {
        printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
        return 1;
    }
    Mix_VolumeMusic(MIX_MAX_VOLUME / 2);

    Mix_PlayMusic(bgMusic, -1);
    int selectedOption = 0;
    while (!quit && !creds) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_UP) {
                    selectedOption = (selectedOption - 1 + MENU_OPTIONS_COUNT) % MENU_OPTIONS_COUNT;
                }
                else if (event.key.keysym.sym == SDLK_DOWN) {
                    selectedOption = (selectedOption + 1) % MENU_OPTIONS_COUNT;
                }
                else if (event.key.keysym.sym == SDLK_RETURN) {
                    if (selectedOption == 0) {
                        // Start game
                        quit = true;
                    }
                    else if (selectedOption == 1) {
                        credit_screen(renderer);
                    }
                    else if (selectedOption == 2) {
                        options_screen(renderer);
                    }
                }
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

        SDL_Rect titleRect = { (SCREEN_WIDTH - titleWidth) / 2, 50, titleWidth, titleHeight };
        SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);

        for (int i = 0; i < MENU_OPTIONS_COUNT; i++) {
            SDL_Rect menuRect = { (SCREEN_WIDTH - menuWidths[i]) / 2, 200 + i * 100, menuWidths[i], menuHeights[i] };
            if (i == selectedOption) {
                SDL_SetTextureColorMod(menuTextures[i], 255, 0, 0); // Highlight selected option
            }
            else {
                SDL_SetTextureColorMod(menuTextures[i], 255, 255, 255);
            }
            SDL_RenderCopy(renderer, menuTextures[i], NULL, &menuRect);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(10); // Control frame rate
    }

    Mix_HaltMusic();
    Mix_FreeMusic(bgMusic);

    for (int i = 0; i < MENU_OPTIONS_COUNT; i++) {
        SDL_DestroyTexture(menuTextures[i]);
    }
    SDL_DestroyTexture(titleTexture);
    SDL_DestroyTexture(backgroundTexture);
    return selectedOption == 0 ? 1 : 0;
}

//ekanto
void setup()
{

    texture_destination_setup();


}


void set_map1() {
    //  for (int i = 0; i < MAP_HEIGHT - 3; i++) {
       //   for (int j = 0; j < MAP_WIDTH; j++) {
       //       gameMap1[i][j] = 2;
       //   }
    //  }
    for (int i = 0; i < MAP_WIDTH; i++) {
        gameMap1[12][i] = 1;
    }
    for (int i = MAP_HEIGHT - 2; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            if (j != 5 && j != 6)
                gameMap1[i][j] = 8;
        }
    }

    for (int i = 9; i < MAP_WIDTH - 1; i = i + 15) {
        int x = rand() % 2;
        gameMap1[11][i] = 4;
        gameMap1[11][i + 1] = 5;
        gameMap1[10][i] = 7;
        gameMap1[10][i + 1] = 6;
        if (x == 1) {
            gameMap1[14][i + 7] = 0;
            gameMap1[14][i + 8] = 0;
            gameMap1[13][i + 7] = 0;
            gameMap1[13][i + 8] = 0;
            gameMap1[12][i + 7] = 0;
            gameMap1[12][i + 8] = 0;
        }
        if (x == 0) {
            gameMap1[8][i + 8] = 3;
            gameMap1[14][i + 7] = 0;
            gameMap1[14][i + 8] = 0;
            gameMap1[14][i + 9] = 0;
            gameMap1[13][i + 7] = 0;
            gameMap1[13][i + 8] = 0;
            gameMap1[13][i + 9] = 0;
            gameMap1[12][i + 7] = 0;
            gameMap1[12][i + 8] = 0;
            gameMap1[12][i + 9] = 0;
        }

    }
    gameMap1[14][5] = 0;
    gameMap1[14][6] = 0;
    gameMap1[13][5] = 0;
    gameMap1[13][6] = 0;
    gameMap1[12][5] = 0;
    gameMap1[12][6] = 0;
}
void setmap2() {
    // for (int i = 0; i < MAP_HEIGHT - 3; i++) {
       //  for (int j = 0; j < MAP_WIDTH; j++) {
       //      gameMap2[i][j] = 2;
        // }
    // }
    for (int j = 0; j < MAP_WIDTH; j++) {
        gameMap2[12][j] = 1;
    }
    for (int i = MAP_HEIGHT - 2; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            if (j != 5 && j != 6)
                gameMap2[i][j] = 9;
        }
    }

    for (int i = 9; i < MAP_WIDTH - 1; i = i + 15) {
        int x = rand() % 2;
        gameMap2[11][i] = 4;
        gameMap2[11][i + 1] = 5;
        gameMap2[10][i] = 7;
        gameMap2[10][i + 1] = 6;
        if (x == 1) {
            gameMap2[14][i + 7] = 0;
            gameMap2[14][i + 8] = 0;
            gameMap2[13][i + 7] = 0;
            gameMap2[13][i + 8] = 0;
            gameMap2[12][i + 7] = 0;
            gameMap2[12][i + 8] = 0;
            gameMap2[11][i + 9] = 8;
            gameMap2[11][i + 12] = 8;
            //   gameMap2[11][i + 11] = 8;
             //  gameMap2[11][i + 12] = 8;
        }
        if (x == 0) {
            gameMap2[8][i + 8] = 3;
            gameMap2[14][i + 7] = 0;
            gameMap2[14][i + 8] = 0;
            gameMap2[14][i + 9] = 0;
            gameMap2[13][i + 7] = 0;
            gameMap2[13][i + 8] = 0;
            gameMap2[13][i + 9] = 0;
            gameMap2[12][i + 7] = 0;
            gameMap2[12][i + 8] = 0;
            gameMap2[12][i + 9] = 0;
            gameMap2[11][i + 11] = 8;
            gameMap2[11][i + 12] = 8;

        }

    }
    gameMap2[14][5] = 0;
    gameMap2[14][6] = 0;
    gameMap2[13][5] = 0;
    gameMap2[13][6] = 0;
    gameMap2[12][5] = 0;
    gameMap2[12][6] = 0;
}
void setmap3() {
    // for (int i = 0; i < MAP_HEIGHT - 3; i++) {
          //  for (int j = 0; j < MAP_WIDTH; j++) {
          //      gameMap2[i][j] = 2;
           // }
       // }
    for (int j = 0; j < MAP_WIDTH; j++) {
        gameMap3[12][j] = 1;
    }
    for (int i = MAP_HEIGHT - 2; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            if (j != 5 && j != 6)
                gameMap3[i][j] = 9;
        }
    }

    for (int i = 9; i < MAP_WIDTH - 1; i = i + 15) {
        int x = rand() % 2;
        gameMap3[11][i] = 4;
        gameMap3[11][i + 1] = 5;
        gameMap3[10][i] = 7;
        gameMap3[10][i + 1] = 6;
        if (x == 1) {
            gameMap3[14][i + 7] = 0;
            gameMap3[14][i + 8] = 0;
            gameMap3[13][i + 7] = 0;
            gameMap3[13][i + 8] = 0;
            gameMap3[12][i + 7] = 0;
            gameMap3[12][i + 8] = 0;
            gameMap3[11][i + 9] = 8;
            gameMap3[11][i + 12] = 8;
            //   gameMap2[11][i + 11] = 8;
             //  gameMap2[11][i + 12] = 8;
        }
        if (x == 0) {
            gameMap3[8][i + 8] = 3;
            gameMap3[14][i + 7] = 0;
            gameMap3[14][i + 8] = 0;
            gameMap3[14][i + 9] = 0;
            gameMap3[13][i + 7] = 0;
            gameMap3[13][i + 8] = 0;
            gameMap3[13][i + 9] = 0;
            gameMap3[12][i + 7] = 0;
            gameMap3[12][i + 8] = 0;
            gameMap3[12][i + 9] = 0;
            gameMap3[11][i + 11] = 8;
            gameMap3[11][i + 12] = 8;

        }

    }
    gameMap3[14][5] = 0;
    gameMap3[14][6] = 0;
    gameMap3[13][5] = 0;
    gameMap3[13][6] = 0;
    gameMap3[12][5] = 0;
    gameMap3[12][6] = 0;
}

void load_map_texture() {
    textures1[TILE_GROUND] = IMG_LoadTexture(renderer, "block2.png");
    textures1[TILE_BRICK] = IMG_LoadTexture(renderer, "sky.png");
    textures1[TILE_COIN] = IMG_LoadTexture(renderer, "coin.png");
    // textures1[TILE_EMPTY] = IMG_LoadTexture(renderer, "sol.png");
    textures1[4] = IMG_LoadTexture(renderer, "tuyau1.png");
    textures1[5] = IMG_LoadTexture(renderer, "tuyau2.png");
    textures1[6] = IMG_LoadTexture(renderer, "tuyau3.png");
    textures1[7] = IMG_LoadTexture(renderer, "tuyau4.png");
    textures1[8] = IMG_LoadTexture(renderer, "block5.png");
}

void load_map2_texture() {
    textures2[TILE_GROUND] = IMG_LoadTexture(renderer, "block4.png");
    textures2[TILE_BRICK] = IMG_LoadTexture(renderer, "sky.png");
    textures2[TILE_COIN] = IMG_LoadTexture(renderer, "coin.png");
    //  textures2[TILE_EMPTY] = IMG_LoadTexture(renderer, "sol.png");
    textures2[4] = IMG_LoadTexture(renderer, "tuyau5.png");
    textures2[5] = IMG_LoadTexture(renderer, "tuyau6.png");
    textures2[6] = IMG_LoadTexture(renderer, "tuyau7.png");
    textures2[7] = IMG_LoadTexture(renderer, "tuyau8.png");
    textures2[8] = IMG_LoadTexture(renderer, "tnt.jpg");
    textures2[9] = IMG_LoadTexture(renderer, "block3.png");
}

void load_sprite_texture() {
    sprite_texture[0][0] = IMG_LoadTexture(renderer, "standing1.png");
    sprite_texture[0][1] = IMG_LoadTexture(renderer, "standing2.png");
    sprite_texture[0][2] = IMG_LoadTexture(renderer, "standing3.png");
    sprite_texture[0][3] = IMG_LoadTexture(renderer, "standing3.png");
    sprite_texture[1][0] = IMG_LoadTexture(renderer, "right1.png");
    sprite_texture[1][1] = IMG_LoadTexture(renderer, "right2.png");
    sprite_texture[1][2] = IMG_LoadTexture(renderer, "right3.png");
    sprite_texture[1][3] = IMG_LoadTexture(renderer, "right3.png");
    sprite_texture[2][0] = IMG_LoadTexture(renderer, "left1.png");
    sprite_texture[2][1] = IMG_LoadTexture(renderer, "left2.png");
    sprite_texture[2][2] = IMG_LoadTexture(renderer, "left3.png");
    sprite_texture[2][3] = IMG_LoadTexture(renderer, "left3.png");
    sprite_texture[3][0] = IMG_LoadTexture(renderer, "jump1.png");
    sprite_texture[3][1] = IMG_LoadTexture(renderer, "jump2.png");
    sprite_texture[3][2] = IMG_LoadTexture(renderer, "jump3.png");
    sprite_texture[3][3] = IMG_LoadTexture(renderer, "jump4.png");
    sprite_texture[4][0] = IMG_LoadTexture(renderer, "fall1.png");
    sprite_texture[4][1] = IMG_LoadTexture(renderer, "fall2.png");
    sprite_texture[4][2] = IMG_LoadTexture(renderer, "fall3.png");
    sprite_texture[4][3] = IMG_LoadTexture(renderer, "fall4.png");


}
void load_map3_texture() {
    textures3[TILE_GROUND] = IMG_LoadTexture(renderer, "block2.png");
    textures3[TILE_BRICK] = IMG_LoadTexture(renderer, "sky.png");
    textures3[TILE_COIN] = IMG_LoadTexture(renderer, "coin.png");
    //  textures2[TILE_EMPTY] = IMG_LoadTexture(renderer, "sol.png");
    textures3[4] = IMG_LoadTexture(renderer, "tuyau9.png");
    textures3[5] = IMG_LoadTexture(renderer, "tuyau10.png");
    textures3[6] = IMG_LoadTexture(renderer, "tuyau11.png");
    textures3[7] = IMG_LoadTexture(renderer, "tuyau12.png");
    textures3[8] = IMG_LoadTexture(renderer, "tnt.jpg");
    textures3[9] = IMG_LoadTexture(renderer, "block5.png");
}
//ekanto
image_process()
{
    sprite_animation_MC();
}


void updateAnimation(Uint32 currentTime) {
    if (movingRight && !movingLeft && !jumping && !falling) {
        walkingDirection = 1;
    }
    else if (movingLeft && !movingRight && !jumping && !falling) {
        walkingDirection = 2;
    }
    else if (!movingLeft && !movingRight && !jumping)
        walkingDirection = 0;
    else if (jumping)
        walkingDirection = 3;
    else if (falling)
        walkingDirection = 4;
    if (walkingDirection != 0 && walkingDirection != 3 && walkingDirection != 4) {
        if (currentTime - walkingTimer >= ANIMATION_SPEED) {
            walkingTimer = currentTime;
            frame = (frame + 1) % 4;
        }
    }
    else if (walkingDirection == 0) {
        if (currentTime - walkingTimer >= 100) {
            walkingTimer = currentTime;
            frame = (frame + 1) % 4;
        }
    }
    else if (walkingDirection == 3 && !movingLeft) {
        if (sprite.y == 475) {
            frame = 0;
        }
        frame = 1;

    }
    else if (walkingDirection == 3 && movingLeft) {
        if (sprite.y == 475)
            frame = 2;
        else
            frame = 3;

    }
    else if (walkingDirection == 4 && !movingLeft) {
        if (sprite.y == 475)
            frame = 1;
        else
            frame = 0;
    }
    else if (walkingDirection == 4 && movingLeft) {
        if (sprite.y == 475)
            frame = 3;
        else
            frame = 2;
    }



}

void vertical_collision() {
    if (map == 0) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = startColumn; x < endColumn; x++) {
                if (gameMap1[y][x] == TILE_GROUND || gameMap1[y][x] == TILE_COIN || gameMap1[y][x] == 8) {
                    int blockTop = y * TILE_SIZE;
                    int blockBottom = (y + 1) * TILE_SIZE;
                    int blockLeft = x * TILE_SIZE - cameraX;
                    int blockRight = (x + 1) * TILE_SIZE - cameraX;
                    // Check if character's bottom collides with block's top
                    if (characterBottom >= blockTop && sprite.y < blockTop && characterLeft < blockRight && characterRight > blockLeft) {
                        sprite.y = blockTop - sprite.h;
                        falling = 0;
                        break;
                    }

                    // Check if character's top collides with block's bottom while falling
                    if (jumping && characterBottom > blockTop && characterLeft < blockRight && characterRight > blockLeft) {
                        sprite.y = blockBottom;
                        jumping = 0;
                        //falling = 1;
                    }
                }
            }
            if (!falling) break;
        }
    }
    if (map == 1) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = startColumn; x < endColumn; x++) {
                if (gameMap2[y][x] == TILE_GROUND || gameMap2[y][x] == TILE_COIN || gameMap2[y][x] == 9) {
                    int blockTop = y * TILE_SIZE;
                    int blockBottom = (y + 1) * TILE_SIZE;
                    int blockLeft = x * TILE_SIZE - cameraX;
                    int blockRight = (x + 1) * TILE_SIZE - cameraX;

                    // Check if character's bottom collides with block's top
                    if (characterBottom >= blockTop && sprite.y < blockTop && characterLeft < blockRight && characterRight > blockLeft) {
                        sprite.y = blockTop - sprite.h;
                        falling = 0;
                        break;
                    }

                    // Check if character's top collides with block's bottom while falling
                    if (jumping && characterBottom > blockTop && characterLeft < blockRight && characterRight > blockLeft) {
                        sprite.y = blockBottom;
                        jumping = 0;
                        // falling = 1;
                    }
                }
            }
            if (!falling) break;
        }
    }
    if (map == 2) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = startColumn; x < endColumn; x++) {
                if (gameMap3[y][x] == TILE_GROUND || gameMap3[y][x] == TILE_COIN || gameMap3[y][x] == 9) {
                    int blockTop = y * TILE_SIZE;
                    int blockBottom = (y + 1) * TILE_SIZE;
                    int blockLeft = x * TILE_SIZE - cameraX;
                    int blockRight = (x + 1) * TILE_SIZE - cameraX;

                    // Check if character's bottom collides with block's top
                    if (characterBottom >= blockTop && sprite.y < blockTop && characterLeft < blockRight && characterRight > blockLeft) {
                        sprite.y = blockTop - sprite.h;
                        falling = 0;
                        break;
                    }

                    // Check if character's top collides with block's bottom while falling
                    if (jumping && characterBottom > blockTop && characterLeft < blockRight && characterRight > blockLeft) {
                        sprite.y = blockBottom;
                        jumping = 0;
                        // falling = 1;
                    }
                }
            }
            if (!falling) break;
        }
    }



}

void horizontal_collsion() {
    if (map == 0) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = startColumn; x < endColumn; x++) {
                if (gameMap1[y][x] == TILE_GROUND || gameMap1[y][x] == 8) {
                    int blockTop = y * TILE_SIZE;
                    int blockBottom = (y + 1) * TILE_SIZE;
                    int blockLeft = x * TILE_SIZE - cameraX;
                    int blockRight = (x + 1) * TILE_SIZE - cameraX;

                    if (characterRight >= blockLeft && characterLeft <= blockRight && characterBottom > blockTop && sprite.y < blockBottom) {
                        if (sprite.x + sprite.w / 2 < (blockLeft + blockRight) / 2) {
                            sprite.x = blockLeft - sprite.w;
                        }
                        else {
                            sprite.x = blockRight;
                        }
                    }
                }
                else if (gameMap1[y][x] == 4 || gameMap1[y][x] == 5 || gameMap1[y][x] == 6 || gameMap1[y][x] == 7) {
                    int blockTop = y * TILE_SIZE;
                    int blockBottom = (y + 1) * TILE_SIZE;
                    int blockLeft = x * TILE_SIZE - cameraX;
                    int blockRight = (x + 1) * TILE_SIZE - cameraX;
                    if (characterRight >= blockLeft && characterLeft <= blockRight && characterBottom > blockTop && sprite.y < blockBottom) {
                        if (sprite.x + sprite.w / 2 < (blockLeft + blockRight) / 2) {
                            sprite.x = blockLeft - sprite.w;
                        }
                        else if (sprite.x + sprite.w / 2 > (blockLeft + blockRight) / 2) {
                            sprite.x = blockRight;
                        }
                        else {
                            sprite.x = 0;
                        }
                    }
                }
            }
        };
    }
    if (map == 1) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = startColumn; x < endColumn; x++) {
                if (gameMap2[y][x] == TILE_GROUND || gameMap2[y][x] == 9) {
                    int blockTop = y * TILE_SIZE;
                    int blockBottom = (y + 1) * TILE_SIZE;
                    int blockLeft = x * TILE_SIZE - cameraX;
                    int blockRight = (x + 1) * TILE_SIZE - cameraX;

                    if (characterRight >= blockLeft && characterLeft <= blockRight && characterBottom > blockTop && sprite.y < blockBottom) {
                        if (sprite.x + sprite.w / 2 < (blockLeft + blockRight) / 2) {
                            sprite.x = blockLeft - sprite.w;
                        }
                        else {
                            sprite.x = blockRight;
                        }
                    }
                }
                else if (gameMap2[y][x] == 4 || gameMap2[y][x] == 5 || gameMap2[y][x] == 6 || gameMap2[y][x] == 7) {
                    int blockTop = y * TILE_SIZE;
                    int blockBottom = (y + 1) * TILE_SIZE;
                    int blockLeft = x * TILE_SIZE - cameraX;
                    int blockRight = (x + 1) * TILE_SIZE - cameraX;
                    if (characterRight >= blockLeft && characterLeft <= blockRight && characterBottom > blockTop && sprite.y < blockBottom) {
                        if (sprite.x + sprite.w / 2 < (blockLeft + blockRight) / 2) {
                            sprite.x = blockLeft - sprite.w;
                        }
                        else if (sprite.x + sprite.w / 2 > (blockLeft + blockRight) / 2) {
                            sprite.x = blockRight;
                        }
                        else {
                            sprite.x = 0;
                        }
                    }
                }
                else if (gameMap2[y][x] == 8) {
                    int blockTop = y * TILE_SIZE;
                    int blockBottom = (y + 1) * TILE_SIZE;
                    int blockLeft = x * TILE_SIZE - cameraX;
                    int blockRight = (x + 1) * TILE_SIZE - cameraX;
                    if (characterRight >= blockLeft && characterLeft <= blockRight && characterBottom > blockTop && sprite.y < blockBottom) {
                        if (sprite.x + sprite.w / 2 < (blockLeft + blockRight) / 2) {
                            // sprite.x = blockLeft - sprite.w;
                            game_over = 1;
                        }
                        else {
                            game_over = 1;
                        }

                    }
                }
            }
        }

    }
    if (map == 2) {

        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = startColumn; x < endColumn; x++) {
                if (gameMap3[y][x] == TILE_GROUND || gameMap3[y][x] == 9) {
                    int blockTop = y * TILE_SIZE;
                    int blockBottom = (y + 1) * TILE_SIZE;
                    int blockLeft = x * TILE_SIZE - cameraX;
                    int blockRight = (x + 1) * TILE_SIZE - cameraX;

                    if (characterRight >= blockLeft && characterLeft <= blockRight && characterBottom > blockTop && sprite.y < blockBottom) {
                        if (sprite.x + sprite.w / 2 < (blockLeft + blockRight) / 2) {
                            sprite.x = blockLeft - sprite.w;
                        }
                        else {
                            sprite.x = blockRight;
                        }
                    }
                }
                else if (gameMap3[y][x] == 4 || gameMap3[y][x] == 5 || gameMap3[y][x] == 6 || gameMap3[y][x] == 7) {
                    int blockTop = y * TILE_SIZE;
                    int blockBottom = (y + 1) * TILE_SIZE;
                    int blockLeft = x * TILE_SIZE - cameraX;
                    int blockRight = (x + 1) * TILE_SIZE - cameraX;
                    if (characterRight >= blockLeft && characterLeft <= blockRight && characterBottom > blockTop && sprite.y < blockBottom) {
                        if (sprite.x + sprite.w / 2 < (blockLeft + blockRight) / 2) {
                            sprite.x = blockLeft - sprite.w;
                        }
                        else if (sprite.x + sprite.w / 2 > (blockLeft + blockRight) / 2) {
                            sprite.x = blockRight;
                        }
                        else {
                            sprite.x = 0;
                        }
                    }
                }
                else if (gameMap3[y][x] == 8) {
                    int blockTop = y * TILE_SIZE;
                    int blockBottom = (y + 1) * TILE_SIZE;
                    int blockLeft = x * TILE_SIZE - cameraX;
                    int blockRight = (x + 1) * TILE_SIZE - cameraX;
                    if (characterRight >= blockLeft && characterLeft <= blockRight && characterBottom > blockTop && sprite.y < blockBottom) {
                        if (sprite.x + sprite.w / 2 < (blockLeft + blockRight) / 2) {
                            // sprite.x = blockLeft - sprite.w;
                            game_over = 1;
                        }
                        else {
                            game_over = 1;
                        }

                    }
                }
            }
        }
    }
}

void process_input1() {
    SDL_Delay(20);
    if (sprite.y >= SCREEN_HEIGHT) {
        game_over = 1;
    }
    // Handle events
    while (SDL_PollEvent(&event)) {



        // Inside your main loop
        if (event.type == SDL_QUIT) {
            quit = 1;
        }
        else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_RIGHT:
            case SDL_SCANCODE_D:
                movingRight = 1;
                break;
            case SDL_SCANCODE_LEFT:
            case SDL_SCANCODE_A:
                movingLeft = 1;
                break;
            case SDL_SCANCODE_UP:
            case SDL_SCANCODE_W:
                // Handle jumping
            //    Mix_VolumeChunk(jump, MIX_MAX_VOLUME / 10);
              //  Mix_PlayChannel(-1, jump, 0);
                if (!jumping && !falling) {
                    jumping = 1;
                    jumpStartY = sprite.y;
                }
                break;
            }
        }
        else if (event.type == SDL_KEYUP) {
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_RIGHT:
            case SDL_SCANCODE_D:
                movingRight = 0;
                break;
            case SDL_SCANCODE_LEFT:
            case SDL_SCANCODE_A:
                movingLeft = 0;
                break;
            }
        }
    }

    if (movingRight) {
        if (sprite.x >= 400 && cameraX != MAP_WIDTH * TILE_SIZE - SCREEN_WIDTH) {
            cameraX += MOVEMENT_SPEED;
            if (cameraX > MAP_WIDTH * TILE_SIZE - SCREEN_WIDTH) {
                cameraX = MAP_WIDTH * TILE_SIZE - SCREEN_WIDTH;
            }
        }
        else {
            sprite.x += MOVEMENT_SPEED;
            if (sprite.x + sprite.w >= SCREEN_WIDTH && map == 0) {
                sprite.x = SCREEN_WIDTH - sprite.w;
                map = 1;
                sprite.x = 0;
                sprite.y = 100;
                cameraX = 0;
            }
            else if (sprite.x + sprite.w >= SCREEN_WIDTH && map == 1) {
                sprite.x = SCREEN_WIDTH - sprite.w;
                map = 2;
                sprite.x = 0;
                sprite.y = 100;
                cameraX = 0;
            }
        }
    }

    if (movingLeft) {
        if (sprite.x == SCREEN_WIDTH / 2 && cameraX != 0) {
            cameraX -= MOVEMENT_SPEED;
            if (cameraX < 0) {
                cameraX = 0;
            }
        }
        else {
            sprite.x -= MOVEMENT_SPEED;
            if (sprite.x - sprite.w < 0) {
                sprite.x = 0;
            }
        }
    }

    if (jumping) {
        // Move character upward
        sprite.y -= jumpSpeed;
        // Check if reached maximum jump height
        if (sprite.y <= jumpStartY - jumpHeight) {
            jumping = 0;
            falling = 1; // Start falling
        }
        if (sprite.y <= (jumpStartY - jumpHeight) / 2 && movingRight) {
            jumping = 0;
            falling = 1;
            movingRight = 0;
        }
        if (sprite.y <= (jumpStartY - jumpHeight) / 2 && movingLeft) {
            jumping = 0;
            falling = 1;
            movingLeft = 0;
        }
    }


    // Left x-coordinate of the character

    characterBottom = sprite.y + sprite.h; // Bottom y-coordinate of the character
    characterRight = sprite.x + sprite.w;  // Right x-coordinate of the character
    characterLeft = sprite.x;
    if (falling)
        sprite.y += 10;
    falling = 1;
    if (sprite.y <= 480) {
        vertical_collision();
    }

    horizontal_collsion();



}
//ekanto
void update()
{
    // Sleep the execution until we reach the frame time in ms
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time); // no of ms elapsed to after the SDL library was installed

    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME)
    {
        SDL_Delay(time_to_wait);
    }

    // Sleep until we reach our target framerate
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), last_frame_time + FRAME_TARGET_TIME));//keeps looping until the current time exceeds the expected time for the next frame

    // Get a delta time factor converted to seconds to be used to update objects later
    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;

    // Logic to keep fixed timestep
    last_frame_time = SDL_GetTicks();

    // Frame animation
    ///SA
    frameTime++;//wastes time
    kyo_frametime++;
    worldmap_frameTime++;



    world_map_animation();

    kyo_sprite_animation();

    effects_animation();

    kyo_effects_animation();

    health_bar_animation();
    cutscene_animation();



    if (orochi_saga)
    {
        orochi_iori_sprite_animation();
    }
    else
    {
        iori_sprite_animation();
    }



    collision();
    //kyo_algorithm();

    iori_fight();
    if (!halt_screen && kyo_start)// changed

        kyo_algorithm_hard();

}


//ekanto

void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y) {
    SDL_Color textColor = { 255, 255, 255, 255 }; // White color
    SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, text, textColor, SCREEN_WIDTH - 100);
    if (textSurface == NULL) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == NULL) {
        printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        SDL_FreeSurface(textSurface);
        return;
    }

    SDL_Rect renderQuad = { x, y, textSurface->w, textSurface->h };
    SDL_RenderCopy(renderer, textTexture, NULL, &renderQuad);

    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
}

void renderMap(SDL_Renderer* renderer, int gameMap[][MAP_WIDTH], SDL_Texture* textures[], int cameraX) {
    // Calculate the visible range of tiles based on camera position
    startColumn = cameraX / TILE_SIZE;
    endColumn = (cameraX + SCREEN_WIDTH) / TILE_SIZE + 1;
    endColumn = (endColumn > MAP_WIDTH) ? MAP_WIDTH : endColumn;

    // Loop through the visible range of tiles in the game map array
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = startColumn; x < endColumn; x++) {
            // Calculate the position to render each tile
            int xPos = x * TILE_SIZE - cameraX;
            int yPos = y * TILE_SIZE;

            // Determine the tile type and render accordingly
            switch (gameMap[y][x]) {
            case TILE_EMPTY:
            {
                // Render empty space (optional)
                SDL_Rect solRect = { xPos, yPos, TILE_SIZE, TILE_SIZE };
                SDL_RenderCopy(renderer, textures[TILE_EMPTY], NULL, &solRect);
                break;
            }
            case TILE_GROUND:
            {
                // Render ground
                SDL_Rect groundRect = { xPos, yPos, TILE_SIZE, TILE_SIZE };
                SDL_RenderCopy(renderer, textures[TILE_GROUND], NULL, &groundRect);
                break;
            }
            case TILE_BRICK:
            {
                // Render brick
                SDL_Rect brickRect = { xPos, yPos, TILE_SIZE, TILE_SIZE };
                SDL_RenderCopy(renderer, textures[TILE_BRICK], NULL, &brickRect);
                break;
            }
            case TILE_COIN:
            {
                // Render coin (optional)
                SDL_Rect coinRect = { xPos, yPos, 40, 40 };
                SDL_RenderCopy(renderer, textures[TILE_COIN], NULL, &coinRect);
                break;
            }
            case 4:
            {
                SDL_Rect obs1Rect = { xPos, yPos, TILE_SIZE, TILE_SIZE };
                SDL_RenderCopy(renderer, textures[4], NULL, &obs1Rect);
                break;
            }
            case 5:
            {
                SDL_Rect obs2Rect = { xPos, yPos, TILE_SIZE, TILE_SIZE };
                SDL_RenderCopy(renderer, textures[5], NULL, &obs2Rect);
                break;
            }
            case 6:
            {
                SDL_Rect obs3Rect = { xPos, yPos, TILE_SIZE, TILE_SIZE };
                SDL_RenderCopy(renderer, textures[6], NULL, &obs3Rect);
                break;
            }
            case 7:
            {
                SDL_Rect obs4Rect = { xPos, yPos, TILE_SIZE, TILE_SIZE };
                SDL_RenderCopy(renderer, textures[7], NULL, &obs4Rect);
                break;
            }
            case 8:
            {
                SDL_Rect obs5Rect = { xPos, yPos, TILE_SIZE, TILE_SIZE };
                SDL_RenderCopy(renderer, textures[8], NULL, &obs5Rect);
                break;
            }
            //     case 8:
             //    {
              //       SDL_Rect forRect = { xPos, yPos, TILE_SIZE, TILE_SIZE };
              //       SDL_RenderCopy(renderer, textures[8], NULL, &forRect);
              //       break;
              //   }

            default:
                // Handle unknown tile types (optional)
                break;
            }
        }
    }
}

void renderMap2(SDL_Renderer* renderer, int gameMap[][MAP_WIDTH], SDL_Texture* textures[], int cameraX) {
    // Calculate the visible range of tiles based on camera position
    startColumn = cameraX / TILE_SIZE;
    endColumn = (cameraX + SCREEN_WIDTH) / TILE_SIZE + 1;
    endColumn = (endColumn > MAP_WIDTH) ? MAP_WIDTH : endColumn;

    // Loop through the visible range of tiles in the game map array
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = startColumn; x < endColumn; x++) {
            // Calculate the position to render each tile
            int xPos = x * TILE_SIZE - cameraX;
            int yPos = y * TILE_SIZE;

            // Determine the tile type and render accordingly
            switch (gameMap[y][x]) {
            case TILE_EMPTY:
            {
                // Render empty space (optional)
                SDL_Rect solRect = { xPos, yPos, TILE_SIZE, TILE_SIZE };
                SDL_RenderCopy(renderer, textures[TILE_EMPTY], NULL, &solRect);
                break;
            }
            case TILE_GROUND:
            {
                // Render ground
                SDL_Rect groundRect = { xPos, yPos, TILE_SIZE, TILE_SIZE };
                SDL_RenderCopy(renderer, textures[TILE_GROUND], NULL, &groundRect);
                break;
            }
            case TILE_BRICK:
            {
                // Render brick
                SDL_Rect brickRect = { xPos, yPos, TILE_SIZE, TILE_SIZE };
                SDL_RenderCopy(renderer, textures[TILE_BRICK], NULL, &brickRect);
                break;
            }
            case TILE_COIN:
            {
                // Render coin (optional)
                SDL_Rect coinRect = { xPos, yPos, TILE_SIZE, TILE_SIZE };
                SDL_RenderCopy(renderer, textures[TILE_COIN], NULL, &coinRect);
                break;
            }
            case 4:
            {
                SDL_Rect obs1Rect = { xPos, yPos, TILE_SIZE, TILE_SIZE };
                SDL_RenderCopy(renderer, textures[4], NULL, &obs1Rect);
                break;
            }
            case 5:
            {
                SDL_Rect obs2Rect = { xPos, yPos, TILE_SIZE, TILE_SIZE };
                SDL_RenderCopy(renderer, textures[5], NULL, &obs2Rect);
                break;
            }
            case 6:
            {
                SDL_Rect obs3Rect = { xPos, yPos, TILE_SIZE, TILE_SIZE };
                SDL_RenderCopy(renderer, textures[6], NULL, &obs3Rect);
                break;
            }
            case 7:
            {
                SDL_Rect obs4Rect = { xPos, yPos, TILE_SIZE, TILE_SIZE };
                SDL_RenderCopy(renderer, textures[7], NULL, &obs4Rect);
                break;
            }
            case 8:
            {
                SDL_Rect forRect = { xPos, yPos, TILE_SIZE, TILE_SIZE };
                SDL_RenderCopy(renderer, textures[8], NULL, &forRect);
                break;
            }
            case 9:
            {
                SDL_Rect for2Rect = { xPos, yPos, TILE_SIZE, TILE_SIZE };
                SDL_RenderCopy(renderer, textures[9], NULL, &for2Rect);
                break;
            }

            default:
                // Handle unknown tile types (optional)
                break;
            }
        }
    }
}
void renderMap3(SDL_Renderer* renderer, int gameMap[][200], SDL_Texture* textures[], int cameraX) {
    // Calculate the visible range of tiles based on camera position
    startColumn = cameraX / TILE_SIZE;
    endColumn = (cameraX + SCREEN_WIDTH) / TILE_SIZE + 1;
    endColumn = (endColumn > MAP_WIDTH) ? MAP_WIDTH : endColumn;

    // Loop through the visible range of tiles in the game map array
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = startColumn; x < endColumn; x++) {
            // Calculate the position to render each tile
            int xPos = x * TILE_SIZE - cameraX;
            int yPos = y * TILE_SIZE;

            // Determine the tile type and render accordingly
            switch (gameMap[y][x]) {
            case TILE_EMPTY:
            {
                // Render empty space (optional)
                SDL_Rect solRect = { xPos, yPos, TILE_SIZE, TILE_SIZE };
                SDL_RenderCopy(renderer, textures[TILE_EMPTY], NULL, &solRect);
                break;
            }
            case TILE_GROUND:
            {
                // Render ground
                SDL_Rect groundRect = { xPos, yPos, TILE_SIZE, TILE_SIZE };
                SDL_RenderCopy(renderer, textures[TILE_GROUND], NULL, &groundRect);
                break;
            }
            case TILE_BRICK:
            {
                // Render brick
                SDL_Rect brickRect = { xPos, yPos, TILE_SIZE, TILE_SIZE };
                SDL_RenderCopy(renderer, textures[TILE_BRICK], NULL, &brickRect);
                break;
            }
            case TILE_COIN:
            {
                // Render coin (optional)
                SDL_Rect coinRect = { xPos, yPos, TILE_SIZE, TILE_SIZE };
                SDL_RenderCopy(renderer, textures[TILE_COIN], NULL, &coinRect);
                break;
            }
            case 4:
            {
                SDL_Rect obs1Rect = { xPos, yPos, TILE_SIZE, TILE_SIZE };
                SDL_RenderCopy(renderer, textures[4], NULL, &obs1Rect);
                break;
            }
            case 5:
            {
                SDL_Rect obs2Rect = { xPos, yPos, TILE_SIZE, TILE_SIZE };
                SDL_RenderCopy(renderer, textures[5], NULL, &obs2Rect);
                break;
            }
            case 6:
            {
                SDL_Rect obs3Rect = { xPos, yPos, TILE_SIZE, TILE_SIZE };
                SDL_RenderCopy(renderer, textures[6], NULL, &obs3Rect);
                break;
            }
            case 7:
            {
                SDL_Rect obs4Rect = { xPos, yPos, TILE_SIZE, TILE_SIZE };
                SDL_RenderCopy(renderer, textures[7], NULL, &obs4Rect);
                break;
            }
            case 8:
            {
                SDL_Rect forRect = { xPos, yPos, TILE_SIZE, TILE_SIZE };
                SDL_RenderCopy(renderer, textures[8], NULL, &forRect);
                break;
            }
            case 9:
            {
                SDL_Rect for2Rect = { xPos, yPos, TILE_SIZE, TILE_SIZE };
                SDL_RenderCopy(renderer, textures[9], NULL, &for2Rect);
                break;
            }

            default:
                // Handle unknown tile types (optional)
                break;
            }
        }
    }
}
//ekanto
void render()
{

    if (!sp_sprite5)
        SDL_SetRenderDrawColor(renderer, 237, 234, 222, 0);
    else
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);

    SDL_RenderClear(renderer);

    // Set the source rectangle to render the current frame
    animation_render_crop_controller();

    SDL_RenderPresent(renderer);
}

void intermediate_screen() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! TTF_Error: %s\n", TTF_GetError());
        SDL_Quit();
        return;
    }

    SDL_Window* window = SDL_CreateWindow("Typewriter Effect", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return;
    }

    TTF_Font* font = TTF_OpenFont("Oswald-VariableFont_wght.ttf", FONT_SIZE);
    if (font == NULL) {
        printf("Failed to load font! TTF_Error: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return;
    }
    SDL_Texture* cutscene = IMG_LoadTexture(renderer, "iori cutscene.png");

    const char* firstMessage = "Kyo:  Well, just as usual you look like you're trying to pick a fight with the whole world... Yagami, You've got no friends, do you?";
    const char* secondMessage = "Iori:  Spout Whatever garbage you want";
    const char* thirdMessage = "Kyo:  What, aren't you in the mood to talk?";
    const char* fourthMessage = "Iori:  First, I'm going to burn you to ash, Die,Kyo Kusanagi";
    const char* fifthMessage = "Kyo:  Allright, I'll Finish You Quickly";

    int length;
    char buffer[256];

    int quit = 0;
    SDL_Event e;

    // Render the first message one character at a time
    length = strlen(firstMessage);
    for (int i = 1; i <= length && !quit; i++) {
        strncpy(buffer, firstMessage, i);
        buffer[i] = '\0';

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black background
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, cutscene, NULL, NULL);
        renderText(renderer, font, buffer, 50, 450);
        SDL_RenderPresent(renderer);
       // SDL_Delay(DELAY);
        SDL_Delay(0);

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }
    }

   // SDL_Delay(500); // Pause before clearing the first message
    SDL_Delay(0);

    // Clear the first message
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black background
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, cutscene, NULL, NULL);
    SDL_RenderPresent(renderer);


   // SDL_Delay(500); // Pause before showing the second message
    SDL_Delay(0);

    // Render the second message one character at a time
    length = strlen(secondMessage);
    for (int i = 1; i <= length && !quit; i++) {
        strncpy(buffer, secondMessage, i);
        buffer[i] = '\0';

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black background
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, cutscene, NULL, NULL);
        renderText(renderer, font, buffer, 50, 450);
        SDL_RenderPresent(renderer);
       // SDL_Delay(DELAY - 30);
        SDL_Delay(0);

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }
    }
    //SDL_Delay(300); // Pause before clearing the first message
    SDL_Delay(0);

    // Clear the first message
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black background
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, cutscene, NULL, NULL);
    SDL_RenderPresent(renderer);


  //  SDL_Delay(500); // Pause before showing the second message
    SDL_Delay(0);

    // Render the second message one character at a time
    length = strlen(thirdMessage);
    for (int i = 1; i <= length && !quit; i++) {
        strncpy(buffer, thirdMessage, i);
        buffer[i] = '\0';

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black background
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, cutscene, NULL, NULL);
        renderText(renderer, font, buffer, 50, 450);
        SDL_RenderPresent(renderer);
      //  SDL_Delay(DELAY + 5);
        SDL_Delay(0);

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }
    }
   // SDL_Delay(100); // Pause before clearing the first message
    SDL_Delay(0);

    // Clear the first message
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black background
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, cutscene, NULL, NULL);
    SDL_RenderPresent(renderer);

  //  SDL_Delay(500); // Pause before showing the second message
    SDL_Delay(0);

    // Render the second message one character at a time
    length = strlen(fourthMessage);
    for (int i = 1; i <= length && !quit; i++) {
        strncpy(buffer, fourthMessage, i);
        buffer[i] = '\0';

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black background
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, cutscene, NULL, NULL);
        renderText(renderer, font, buffer, 50, 450);
        SDL_RenderPresent(renderer);
       // SDL_Delay(DELAY + 10);
        SDL_Delay(0);

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }
    }
    //SDL_Delay(1000); // Pause before clearing the first message
    SDL_Delay(0);

    // Clear the first message
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black background
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, cutscene, NULL, NULL);
    SDL_RenderPresent(renderer);


  //  SDL_Delay(500); // Pause before showing the second message
    SDL_Delay(0);

    // Render the second message one character at a time
    length = strlen(fifthMessage);
    for (int i = 1; i <= length && !quit; i++) {
        strncpy(buffer, fifthMessage, i);
        buffer[i] = '\0';

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black background
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, cutscene, NULL, NULL);
        renderText(renderer, font, buffer, 50, 450);
        SDL_RenderPresent(renderer);
       // SDL_Delay(DELAY);
        SDL_Delay(0);

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }
    }

    // Wait for the Enter key to be pressed
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_RETURN) {
                    // Move to the next map or state
                    map = 4;
                    Mix_HaltMusic();
                    Mix_CloseAudio();
                    quit = 1;
                }
            }
        }
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}
//ekanto
void destroy_window()
{
    SDL_DestroyTexture(image_texture);
    SDL_DestroyTexture(kyo_texture);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}



// Main function
int main(int argc, char* args[]) {


    srand(time(NULL));
    // Initialize SDL
    initializeSDL();
    if (TTF_Init() != 0) {
        printf("SDL_ttf initialization failed: %s\n", TTF_GetError());
        SDL_Quit();
        return 0;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        SDL_Quit();
        return 0;
    }




    // Create window and renderer
    window = SDL_CreateWindow("Game Map Rendering", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    game_is_running = start_screen(renderer);
    //   if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
      //     printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        //   return 1;
//}
    load_map_texture();
    set_map1();

    // sprite_texture = IMG_LoadTexture(renderer, "spritesheet_1-ezgif.com-crop.png");
    load_map2_texture();

    setmap2();
    load_map3_texture();
    setmap3();
    load_sprite_texture();
    loadObstacle();

    obstacle.x = rand() % (SCREEN_WIDTH - 50);
    obstacle1.x = rand() % (SCREEN_WIDTH - 50);
    obstacle2.x = rand() % (SCREEN_WIDTH - 50);
    obstacle3.x = rand() % (SCREEN_WIDTH - 50);
    // obstacle4.x = SCREEN_WIDTH;

    SDL_Texture* background = IMG_LoadTexture(renderer, "bg.png");
    SDL_Texture* background1 = IMG_LoadTexture(renderer, "bg3.jpeg");
    SDL_Texture* background2 = IMG_LoadTexture(renderer, "bg2.png");
    game_Over = IMG_LoadTexture(renderer, "end.jpg");
    Uint32 map2StartTime = 0;
    Mix_Music* bg1Music = Mix_LoadMUS("lvl1.wav");
    Mix_Music* bg2Music = Mix_LoadMUS("lvl1.wav");
    Mix_Music* bg3Music = Mix_LoadMUS("lvl3.wav");
    Mix_Music* fightMusic = Mix_LoadMUS("fight.wav");

    // jump = Mix_LoadWAV("jump.wav");

    Mix_VolumeMusic(MIX_MAX_VOLUME/2);

    Mix_PlayMusic(bg1Music, -1);
    /*/if (bg1Music == NULL) {
        printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
        return 1;
    }
    if (!Mix_PlayingMusic()) {
        Mix_VolumeMusic(MIX_MAX_VOLUME / 8);
        Mix_PlayMusic(bg1Music, -1);
    }
    */

    // Initialize camera position
    if (map != 3) {

        while (!quit) {
            Uint32 currentTime = SDL_GetTicks();
            process_input1();

            // Clear screen
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderClear(renderer);

            // renderSprite(renderer, sprite_texture);

             // Render game map

            if (map == 0) {
                //   SDL_RenderCopy(renderer, background, NULL, NULL);
                if (game_over == 0) {


                    //  handleMovementInput();
                    SDL_RenderCopy(renderer, background, NULL, NULL);
                    updateAnimation(currentTime);
                    renderMap(renderer, gameMap1, textures1, cameraX);
                    renderSprite();

                }
                // renderMap(renderer, gameMap, textures1, cameraX);
                // renderSprite(renderer, sprite_texture);
                if (game_over == 1) {

                    SDL_RenderCopy(renderer, game_Over, NULL, NULL);
                }
            }
            if (map == 1) {
                if (game_over == 0) {

                    //     handleMovementInput();
                    SDL_RenderCopy(renderer, background1, NULL, NULL);
                    updateAnimation(currentTime);
                    renderMap2(renderer, gameMap2, textures2, cameraX);
                    renderSprite();

                }
                if (game_over == 1) {
                    SDL_RenderCopy(renderer, game_Over, NULL, NULL);
                }
            }
            if (map == 2) {
                if (difficulty == 0) {
                    OBSTACLE_SPEED = 4;
                }
                else  if (difficulty == 1) {
                    OBSTACLE_SPEED = 7;
                }
                else  if (difficulty == 2) {
                    OBSTACLE_SPEED = 10;
                }
                if (game_over == 0) {
                    SDL_RenderCopy(renderer, background2, NULL, NULL);
                    //     handleMovementInput();
                    updateAnimation(currentTime);
                    renderMap2(renderer, gameMap3, textures3, cameraX);
                    renderSprite();
                    SDL_RenderCopy(renderer, obstacleTexture, NULL, &obstacle);
                    SDL_RenderCopy(renderer, obstacleTexture, NULL, &obstacle1);
                    SDL_RenderCopy(renderer, obstacleTexture, NULL, &obstacle2);
                    SDL_RenderCopy(renderer, obstacleTexture, NULL, &obstacle3);
                    //  SDL_RenderCopy(renderer, obstacle2Texture, NULL, &obstacle4)

                    if (movingRight && sprite.x == SCREEN_WIDTH / 2) {
                        obstacle.x -= MOVEMENT_SPEED;
                        obstacle1.x -= MOVEMENT_SPEED;
                        obstacle2.x -= MOVEMENT_SPEED;
                        obstacle3.x -= MOVEMENT_SPEED;
                    }
                    if (movingLeft && sprite.x == SCREEN_WIDTH / 2) {
                        obstacle.x += MOVEMENT_SPEED;
                        obstacle1.x += MOVEMENT_SPEED;
                        obstacle2.x += MOVEMENT_SPEED;
                        obstacle3.x += MOVEMENT_SPEED;
                    }
                    obstacle.y += OBSTACLE_SPEED;
                    obstacle1.y += OBSTACLE_SPEED;
                    obstacle2.y += OBSTACLE_SPEED;
                    obstacle3.y += OBSTACLE_SPEED;



                    //  obstacle4.x -= OBSTACLE_SPEED;

                    if (obstacle.y > SCREEN_HEIGHT && !game_over) {
                        obstacle.y = 0;
                        obstacle.x = rand() % (SCREEN_WIDTH - obstacle.w);
                    }
                    if (obstacle1.y > SCREEN_HEIGHT && !game_over) {
                        obstacle1.y = 0;
                        obstacle1.x = rand() % (SCREEN_WIDTH - obstacle1.w);
                    }
                    if (obstacle2.y > SCREEN_HEIGHT && !game_over) {
                        obstacle2.y = 0;
                        obstacle2.x = rand() % (SCREEN_WIDTH - obstacle2.w);
                    }
                    if (obstacle3.y > SCREEN_HEIGHT && !game_over) {
                        obstacle3.y = 0;
                        obstacle3.x = rand() % (SCREEN_WIDTH - obstacle3.w);
                    }
                    // if (obstacle4.x < 0) {
                   //      obstacle4.x = 0;
                   //      obstacle4.x = SCREEN_WIDTH;

                   //  }

                     // Check collision
                    if (SDL_HasIntersection(&(SDL_Rect) { sprite.x, sprite.y, sprite.w, sprite.h },
                        & (SDL_Rect) {
                        obstacle.x, obstacle.y, obstacle.w, obstacle.h
                    })) {
                        game_over = 1;
                    }
                    if (SDL_HasIntersection(&(SDL_Rect) { sprite.x, sprite.y, sprite.w, sprite.h },
                        & (SDL_Rect) {
                        obstacle1.x, obstacle1.y, obstacle1.w, obstacle1.h
                    })) {
                        game_over = 1;
                    }
                    if (SDL_HasIntersection(&(SDL_Rect) { sprite.x, sprite.y, sprite.w, sprite.h },
                        & (SDL_Rect) {
                        obstacle2.x, obstacle2.y, obstacle2.w, obstacle2.h
                    })) {
                        game_over = 1;
                    }
                    if (SDL_HasIntersection(&(SDL_Rect) { sprite.x, sprite.y, sprite.w, sprite.h },
                        & (SDL_Rect) {
                        obstacle3.x, obstacle3.y, obstacle3.w, obstacle3.h
                    })) {
                        game_over = 1;
                    }

                }

                if (game_over == 1) {
                    SDL_RenderCopy(renderer, game_Over, NULL, NULL);
                }
                if (sprite.x + sprite.w >= SCREEN_WIDTH) {
                    sprite.x = SCREEN_WIDTH - sprite.w;
                    map = 3;
                    for (int i = 0; i < 4; i++) {
                        SDL_DestroyTexture(textures1[i]);
                    }
                    SDL_DestroyRenderer(renderer);
                    SDL_DestroyWindow(window);
                    break;
                }

                //  if (SDL_HasIntersection(&(SDL_Rect) { sprite.x, sprite.y, sprite.w, sprite.h },
               //       & (SDL_Rect) {
               //       obstacle4.x, obstacle4.y, obstacle4.w, obstacle4.h
               //   })) {
               //       game_over = 1;
               //   }
             // }



            }
            if (game_over) {
                Mix_HaltMusic();
            }
            if (map == 1 && music == 0) {
                Mix_HaltMusic();
                Mix_VolumeMusic(MIX_MAX_VOLUME / 2);

                Mix_PlayMusic(bg2Music, -1);
                music++;
            }
            if (map == 2 && music == 1) {
                Mix_HaltMusic();
                Mix_VolumeMusic(MIX_MAX_VOLUME / 10);

                Mix_PlayMusic(bg3Music, -1);
                music++;
            }


            // Update screen
            SDL_RenderPresent(renderer);

        }
    }
    if (map == 3) {
        Mix_HaltMusic();
        Mix_VolumeMusic(MIX_MAX_VOLUME);

        Mix_PlayMusic(fightMusic, 1);
        intermediate_screen();

    }
    if (map == 4) {

        initialize_window();
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
            printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
            SDL_Quit();
            return 0;
        }
        Mix_Music* final = Mix_LoadMUS("final.wav");
        Mix_Music* final_stage = Mix_LoadMUS("final_stage.wav");
        effect = Mix_LoadWAV("Effects.wav");
        iori_effect = Mix_LoadWAV("iori_.wav");
        Mix_VolumeMusic(MIX_MAX_VOLUME/2);
        Mix_PlayMusic(final, -1);

        game_Over1 = IMG_LoadTexture(renderer, "game_over_00000.png");
        game_Win = IMG_LoadTexture(renderer, "iori_win_00000.png");

        image_process();
        setup();
        // Mix_PlayMusic(bg1Music, -1);

         //printf("x tex =%d, y tex =%d\n", texture_destination.h, texture_destination.y);
       //  Mix_VolumeMusic(MIX_MAX_VOLUME / 10);

         //Mix_PlayMusic(final, -1);
        while (game_is_running)
        {
            //printf("restrict keypress= %d\n", restrict_keypress);
            static int flagger = 0;
            if (!flagger)
            {

                //activateKyoSprite(4);
                flagger++;
            }
                process_input();
                update();
                render();
                if (iori_lost && death!=100) {
                    death++;
                }
                if (iori_won && halt_flag==4 && death != 100) {
                    death++;
                }
                if (iori_lost && death==100) {
                    game_is_running=false;
                }
                if (iori_won && halt_flag ==4 && death ==100) {
                   game_is_running = false;
                }
                if (kyo_sp_sprite5) {
                    Mix_HaltMusic();
                    Mix_VolumeChunk(effects, MIX_MAX_VOLUME / 2);
                    Mix_PlayChannel(-1, effect, 0);

                }
                if (sp_sprite5) {
                    Mix_HaltMusic();
                    Mix_VolumeChunk(iori_effect, MIX_MAX_VOLUME / 2);
                    Mix_PlayChannel(-1, iori_effect, 0);
              }
                if (orochi_saga) {
                    Mix_HaltMusic();
                    Mix_VolumeMusic(MIX_MAX_VOLUME /2);
                    Mix_PlayMusic(final_stage, -1);

                }



            //printf("Damage by Iori: %d\n",iori_hit_sum);
            // printf("Damage by Kyo: %d\n",kyo_hit_sum);
            //printf("interaction end =%d\n", interaction_end_frame13);
          //  SDL_RenderPresent(renderer);



        }
        Mix_HaltMusic();
        SDL_RenderClear(renderer);
        while (!game_is_running) {
            if (iori_lost) {
                SDL_RenderCopy(renderer, game_Over1, NULL, NULL);
                SDL_RenderPresent(renderer);
            }
            else if (iori_won && halt_flag ==4) {
                SDL_RenderCopy(renderer, game_Win, NULL, NULL);
                SDL_RenderPresent(renderer);
            }

        }


        SDL_RenderPresent(renderer);

        // Delay to control frame rate
        SDL_Delay(10);
    }



    // Cleanup
    destroy_window();





    // Cleanup
    return 0;

}
SDL_Texture* initialize_texture_from_file(const char* file_name, SDL_Renderer* renderer)
{
    SDL_Surface* image = IMG_Load(file_name); // load image from file
    SDL_Texture* image_texture = SDL_CreateTextureFromSurface(renderer, image); //create texture from surface
    SDL_FreeSurface(image); // free the surface as it is no longer needed
    return image_texture;
}
