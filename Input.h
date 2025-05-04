#define FALSE 0
#define TRUE 1
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FPS 24
#define FRAME_TARGET_TIME (1000 / FPS)


void process_input()
{
    ///SA
    printf("groundboundary flag= %d\n", ground_boundary_flag);
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        game_is_running = FALSE;
        break;

    case SDL_KEYDOWN:
        switch (event.key.keysym.scancode)
        {
        case SDL_SCANCODE_ESCAPE:
            game_is_running = FALSE; // Exit the game only if the escape key is pressed
            break;
        case SDL_SCANCODE_W:
        case SDL_SCANCODE_UP:  // Ensure character is not already jumping
        {
            if(!orochi_saga)
            {
                if(!sp_sprite5 && !up && up_flag && !input_to_physics_tick)
                {
                    up = 1;
                    left_mov_sprite3=0;
                    right_mov_sprite2=0;
                    up_mov_sprite4=1;
                    stand_sprite1=0;
                    up_flag=0;
                    ground_boundary_flag=1;

                }
            }

        }
        break;
        case SDL_SCANCODE_A:
        case SDL_SCANCODE_LEFT:
        {
            if(!sp_sprite5 && !ground_boundary_flag)
                left = 1;
            if(!up && !sp_sprite5 && !ground_boundary_flag )
            {
                stand_sprite1=0;
                left_mov_sprite3=1;
                right_mov_sprite2=0;
                up_mov_sprite4=0;


            }

        }
        break;
        //stand_sprite1, left_mov_sprite3, right_mov_sprite2, up_mov_sprite4, sp_sprite5

        case SDL_SCANCODE_D:
        case SDL_SCANCODE_RIGHT:
        {
            if(!sp_sprite5 && !ground_boundary_flag)
                right = 1;
            if(!up && !sp_sprite5  && !ground_boundary_flag)
            {
                stand_sprite1=0;
                left_mov_sprite3=0;
                right_mov_sprite2=1;
                up_mov_sprite4=0;
            }

        }

        break;
        }
        break;


    ////
    case SDL_KEYUP:
        switch (event.key.keysym.scancode)
        {
        case SDL_SCANCODE_W:
        case SDL_SCANCODE_UP:
            if(!input_to_physics_tick && !orochi_saga)
            {
                up_flag=1;
            }
            break;

        case SDL_SCANCODE_A:
        case SDL_SCANCODE_LEFT:
            left = 0;
            if(!sp_sprite5 && !ground_boundary_flag)
            {

                x_vel=0;
                if(!up && !right)
                    stand_sprite1=1;
                left_mov_sprite3=0;
            }

            break;
        case SDL_SCANCODE_V:
            if(!sp_sprite5 && !ground_boundary_flag && !orochi_saga)
            {
                stand_sprite1=0;
                left_mov_sprite3=0;
                up_mov_sprite4=0;
                sp_sprite5=1;
                right_mov_sprite2=0;

            }
            break;

        case SDL_SCANCODE_D:
        case SDL_SCANCODE_RIGHT:
            right = 0;
            if(!sp_sprite5 && !ground_boundary_flag)
            {

                x_vel=0;
                if(!up && !left)
                    stand_sprite1=1;

                right_mov_sprite2=0;

            }
            break;

        }
        break;
    }
    //printf("up=%d\n\n", up);
    // printf("stand_sprite1=%d, left_mov_sprite3=%d, right_mov_sprite2=%d, up_mov_sprite4=%d, sp_sprite5=%d\n", stand_sprite1, left_mov_sprite3, right_mov_sprite2, up_mov_sprite4, sp_sprite5);

    crop_manip(stand_sprite1, right_mov_sprite2, left_mov_sprite3, up_mov_sprite4);

}
