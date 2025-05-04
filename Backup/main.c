/*
#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Variables.h"
#include "input_lvl4.h"
#include "sprite animation.h"
#include "Sprite_render.h"
#include "collision.h"


///constants
#define FALSE 0
#define TRUE 1
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FPS 24
#define FRAME_TARGET_TIME (1000 / FPS)


///
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

    //IORI Placement
    texture_destination.x=0;
    texture_destination.y=300;
    texture_destination.w=frameWidth*1.1;///multiply both by any value to increase size without changing the aspect ratio
    texture_destination.h=frameHeight*1.1;

    ///KYO Placement

    kyo_texture_destination.x=100;
    kyo_texture_destination.y=300;
    kyo_texture_destination.w=frameWidth*1.1;///multiply both by any value to increase size without changing the aspect ratio
    kyo_texture_destination.h=frameHeight*1.1;

    ///Mini Iori Placement
    mini_iori_texture_destination.x=0;
    mini_iori_texture_destination.y=300;
    mini_iori_texture_destination.w=mini_iori_frame_width*1.1;///multiply both by any value to increase size without changing the aspect ratio
    mini_iori_texture_destination.h=mini_iori_frame_height*1.1;





}

void tilemap()
{

    SDL_Surface* tile_map_surface = SDL_LoadBMP("tile.bmp");
    tile_texture = SDL_CreateTextureFromSurface(renderer, tile_map_surface);
    SDL_FreeSurface(tile_map_surface);
    SDL_Surface* tile_map_surface2 = SDL_LoadBMP("til2.bmp");
    tile_texture2 = SDL_CreateTextureFromSurface(renderer, tile_map_surface2);
    SDL_FreeSurface(tile_map_surface2);
}

void update()
{
    // Sleep the execution until we reach the frame time in ms
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time); // no of ms elapsed to after the SDL library was installed
    //Uint32 ticks = SDL_GetTicks();
    //printf("Ticks since SDL initialization: %d, last frame time = %d\n", ticks,  last_frame_time);
    //printf("Time to wait = %d\n", time_to_wait);
    // Only call delay if we are too fast to process this frame
    //frame target time = 41.67  time to wait = 37
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
    // printf("frametime = %d\n", frameTime);

    kyo_frametime++;


    if(!orochi_saga && !mini_iori)
    {
        iori_sprite_animation();
    }


    kyo_sprite_animation();


    if(orochi_saga && !mini_iori)
    {
        orochi_iori_sprite_animation();
    }

    if(mini_iori)
    {
        mini_iori_sprite_animation();
    }









//printf("stand = %d, leftright =%d up= %d sp =%d\n", stand_frame1, left_right_frame2, up_frame3, sp_frame4);



///Collsion properties
collision();



///Physics properties (Abrar)
    x_vel = y_vel = 0;

// Determine velocity
    if (up)
    {
        y_vel = -speed;
    }


    if (down)
        y_vel = speed;
    if (left && !right)
        x_vel = -speed;
    if (!left && right)
        x_vel = speed;

// Update position at 1/30th of a second
    if(!mini_iori)
    {


        texture_destination.x += x_vel / 30;
        texture_destination.y += y_vel / 30;
    }
    else if (mini_iori)
    {


        mini_iori_texture_destination.x += x_vel / 30;
        mini_iori_texture_destination.y += y_vel / 30;
    }

    offsetX += (float)x_vel / 90;
// if (texture_destination.x >2* offsetX) {
//  texture_destination.x -= 200;
//}


// Ensure boundaries

    if(!mini_iori)
    {


        if (texture_destination.x <= 0-offset_collisionx)
            texture_destination.x = 0-offset_collisionx;
        if (texture_destination.y <= 200 && up) //sky boundary //capping jump
        {
            texture_destination.y = 200;
            y_vel = -y_vel;
            up = 0;
            down = 1;
        }
        if (texture_destination.y >= 300 && down) //Ground boundary
        {
            texture_destination.y = 300;
            y_vel = y_vel;
            down = 0;
            ground_boundary_flag=0;
            stand_sprite1=0;
            input_to_physics_tick=0;
            if(!left && !right && !up)
                stand_sprite1=1;
            else if(left)
            {
                left_mov_sprite3=1;
                stand_sprite1=0;
            }

            else if(right)
            {
                right_mov_sprite2=1;
                stand_sprite1=0;
            }
            else if(up)
            {

                up_mov_sprite4=1;
            }

            else
            {
                up_mov_sprite4=0;

            }


        }

        if (texture_destination.x >= WINDOW_WIDTH - texture_destination.w+offset_collisionx-10)
            texture_destination.x = WINDOW_WIDTH - texture_destination.w+offset_collisionx-10;
        if (texture_destination.y >= WINDOW_HEIGHT - texture_destination.h)
            texture_destination.y = WINDOW_HEIGHT - texture_destination.h;

// if (offsetX < 0) {
//   offsetX = 0;
//}
//if (offsetX > 180) {
// offsetX = 180;
//}

// Set position in struct
        texture_destination.y = (int)texture_destination.y;
        texture_destination.x = (int)texture_destination.x;
    }

    else if(mini_iori)
    {


        if (mini_iori_texture_destination.x <= 0)
            mini_iori_texture_destination.x = 0;
        if (mini_iori_texture_destination.y <= 200 && up) //sky boundary //capping jump
        {
            mini_iori_texture_destination.y = 200;
            y_vel = -y_vel;
            up = 0;
            down = 1;
        }
        if (mini_iori_texture_destination.y >= 300 && down) //Ground boundary
        {
            mini_iori_texture_destination.y = 300;
            y_vel = y_vel;
            down = 0;
            ground_boundary_flag=0;
            stand_sprite1=0;
            input_to_physics_tick=0;
            up_mov_sprite4=0;

            if(!left && !right && !up)
                stand_sprite1=1;
            else if(left)
            {
                left_mov_sprite3=1;
                stand_sprite1=0;
            }

            else if(right)
            {
                right_mov_sprite2=1;
                stand_sprite1=0;
            }
            else if(up)
            {

                up_mov_sprite4=1;
            }

            else
            {
                up_mov_sprite4=0;

            }


        }
        if (mini_iori_texture_destination.x >= WINDOW_WIDTH - mini_iori_texture_destination.w)
            mini_iori_texture_destination.x = WINDOW_WIDTH - mini_iori_texture_destination.w;
        if (mini_iori_texture_destination.y >= WINDOW_HEIGHT - mini_iori_texture_destination.h)
            mini_iori_texture_destination.y = WINDOW_HEIGHT - mini_iori_texture_destination.h;

// if (offsetX < 0) {
//   offsetX = 0;
//}
//if (offsetX > 180) {
// offsetX = 180;
//}

// Set position in struct
        mini_iori_texture_destination.y = (int)mini_iori_texture_destination.y;
        mini_iori_texture_destination.x = (int)mini_iori_texture_destination.x;
    }
}


void image_process()
{
    sprite_animation_MC();
}



void render()
{
    SDL_SetRenderDrawColor(renderer, 237, 234, 222, 0);
    SDL_RenderClear(renderer);

    for (int x = 0; x < 2000; x += 2)
    {
        for (int y = 7; y < 15; y++)
        {
            SDL_Rect destRect = { (x - offsetX) * 40, y * 40, 40, 40 };
            SDL_RenderCopy(renderer, tile_texture, &select_tile, &destRect);
        }
    }
    for (int x = 1; x < 2000; x += 2)
    {
        for (int y = 7; y < 15; y++)
        {
            SDL_Rect destRect = { (x - offsetX) * 40, y * 40, 40, 40 };
            SDL_RenderCopy(renderer, tile_texture2, &select_tile, &destRect);
        }
    }
    //  SDL_RenderPresent(renderer);

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
                //workflow
                tilemap();
                process_input();
                update();
                render();
            }
        }
        SDL_RenderPresent(renderer);

        // Delay to control frame rate
        SDL_Delay(10);
    }

    // Cleanup
    destroy_window();

    return 0;

}




SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer *renderer)
{
    SDL_Surface *image = IMG_Load(file_name); // load image from file
    SDL_Texture *image_texture = SDL_CreateTextureFromSurface(renderer, image); //create texture from surface
    SDL_FreeSurface(image); // free the surface as it is no longer needed
    return image_texture;
}*/
