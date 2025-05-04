#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <time.h>
#include "Variables.h"
#include "input_lvl4.h"
#include "sprite animation.h"
#include "Sprite_render.h"
#include "collision.h"
#include "kyo_algorithm.h"
#include "iori_fight.h"
#include "kyo_algorithm_hard.h"
#include "set & reset.h"
#include "texture_destination_setup.h"

///constants
#define FALSE 0
#define TRUE 1
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FPS 24
#define FRAME_TARGET_TIME (1000 / FPS)
#include <time.h>

SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer *renderer);
#include "Image_process.h"
///
int initialize_window(void)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) !=0)
    {
        fprintf(stderr, "Error initializing SDL.\n");
        return FALSE;
    }

    window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS);
    if(!window)
    {
        fprintf(stderr, "Error creating SDL Window\n");
        return FALSE;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); //cal the refresh rate of the monitor
    if(!renderer)
    {
        fprintf(stderr, "Error creating SDL renderer.\n");
        return FALSE;
    }

    return TRUE;

}
void setup()
{

    texture_destination_setup();


}

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



    if(orochi_saga)
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



        kyo_algorithm_hard();

}

void image_process()
{
    sprite_animation_MC();
}

void render()
{
    SDL_SetRenderDrawColor(renderer, 237, 234, 222, 0);
    SDL_RenderClear(renderer);

    // Set the source rectangle to render the current frame
    animation_render_crop_controller();

    SDL_RenderPresent(renderer);
}

void destroy_window()
{
    SDL_DestroyTexture(image_texture);
    SDL_DestroyTexture(kyo_texture);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return;
    }

    if (TTF_Init() != 0)
    {
        printf("SDL_ttf initialization failed: %s\n", TTF_GetError());
        SDL_Quit();
        return;
    }

    // Create window and renderer
    SDL_Window* window = SDL_CreateWindow("Obstacle Mayhem", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
    {
        printf("Failed to create window: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return;
    }

    // Load background texture
    SDL_Texture* backgroundTexture = IMG_LoadTexture(renderer, "background.jpg");
    if (!backgroundTexture)
    {
        printf("Failed to load background texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return;
    }

    // Load font
    TTF_Font* fontTitle = TTF_OpenFont("Honk-Regular-VariableFont_MORFSHLN.ttf", FONT_SIZE_TITLE);
    TTF_Font* fontPressToStart = TTF_OpenFont("Micro5-Regular.ttf", FONT_SIZE_PRESS_TO_START);
    if (!fontTitle || !fontPressToStart)
    {
        printf("Failed to load font: %s\n", TTF_GetError());
        SDL_DestroyTexture(backgroundTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return;
    }

    // Create title text surface and texture
    SDL_Surface* titleSurface = TTF_RenderText_Solid(fontTitle, TITLE_TEXT, TEXT_COLOR);
    if (!titleSurface)
    {
        printf("Failed to render title text: %s\n", TTF_GetError());
        TTF_CloseFont(fontTitle);
        TTF_CloseFont(fontPressToStart);
        SDL_DestroyTexture(backgroundTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return;
    }

    SDL_Texture* titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);
    if (!titleTexture)
    {
        printf("Failed to create texture from title surface: %s\n", SDL_GetError());
        SDL_FreeSurface(titleSurface);
        TTF_CloseFont(fontTitle);
        TTF_CloseFont(fontPressToStart);
        SDL_DestroyTexture(backgroundTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return;
    }

    SDL_FreeSurface(titleSurface);

    // Create "Press Enter to Start Game" text surface and texture
    SDL_Surface* pressToStartSurface = TTF_RenderText_Solid(fontPressToStart, PRESS_TO_START_TEXT, TEXT_COLOR);

    if (!pressToStartSurface)
    {
        printf("Failed to render text: %s\n", TTF_GetError());
        TTF_CloseFont(fontTitle);
        TTF_CloseFont(fontPressToStart);
        SDL_DestroyTexture(titleTexture);
        SDL_DestroyTexture(backgroundTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return;
    }

    SDL_Texture* pressToStartTexture = SDL_CreateTextureFromSurface(renderer, pressToStartSurface);

    if (!pressToStartTexture)
    {
        printf("Failed to create texture from surface: %s\n", SDL_GetError());
        SDL_FreeSurface(pressToStartSurface);
        TTF_CloseFont(fontTitle);
        TTF_CloseFont(fontPressToStart);
        SDL_DestroyTexture(titleTexture);
        SDL_DestroyTexture(backgroundTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return;
    }

    SDL_FreeSurface(pressToStartSurface);

    TTF_CloseFont(fontTitle);
    TTF_CloseFont(fontPressToStart);

    // Get texture width and height
    int titleWidth = 0, titleHeight = 0;
    SDL_QueryTexture(titleTexture, NULL, NULL, &titleWidth, &titleHeight);

    int pressToStartWidth = 0, pressToStartHeight = 0;
    SDL_QueryTexture(pressToStartTexture, NULL, NULL, &pressToStartWidth, &pressToStartHeight);
    bool quit = false;
    while (!quit)
    {
        // Event handling
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN && !game_is_running)
            {
                game_is_running = true;
                SDL_DestroyTexture(titleTexture); // Remove the title texture after starting the game
                SDL_DestroyTexture(pressToStartTexture); // Remove the press to start texture after starting the game
                quit = true;
            }
        }
        SDL_RenderClear(renderer);

        // Render background
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

        // Render title text
        SDL_Rect titleRect = { (WINDOW_WIDTH - titleWidth) / 2, 50, titleWidth, titleHeight };
        SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);

        // Render "Press Enter to Start Game" text if the game hasn't started yet
        if (!game_is_running)
        {
            SDL_Rect pressToStartRect = { (WINDOW_WIDTH - pressToStartWidth) / 2, WINDOW_HEIGHT / 2, pressToStartWidth, pressToStartHeight };
            SDL_RenderCopy(renderer, pressToStartTexture, NULL, &pressToStartRect);
            SDL_RenderPresent(renderer);

            // Delay to control frame rate
            SDL_Delay(10);
        }
        else
        {
            SDL_DestroyTexture(titleTexture);
            SDL_DestroyTexture(pressToStartTexture);
            SDL_DestroyTexture(backgroundTexture);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            TTF_Quit();
            SDL_Quit();
            initialize_window();
            image_process();
            setup();
            //printf("x tex =%d, y tex =%d\n", texture_destination.h, texture_destination.y);

            while (game_is_running)
            {
                //printf("restrict keypress= %d\n", restrict_keypress);
                static int flagger=0;
                if(!flagger)
                {
                    //activateKyoSprite(4);
                    flagger++;
                }
                process_input();
                update();
                render();


                //printf("right =%d, left =%d\n", right, left);
                //printf("interaction end =%d\n", interaction_end_frame13);
               // printf("iori recoil = %d\n", iori_recoil);
               // printf("iori normal recoil = %d\n", iori_normal_recoil);



            }
        }
        SDL_RenderPresent(renderer);

        // Delay to control frame rate
        SDL_Delay(10);
    }

    destroy_window();

    return 0;

}

SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer *renderer)
{
    SDL_Surface *image = IMG_Load(file_name); // load image from file
    SDL_Texture *image_texture = SDL_CreateTextureFromSurface(renderer, image); //create texture from surface
    SDL_FreeSurface(image); // free the surface as it is no longer needed
    return image_texture;
}

