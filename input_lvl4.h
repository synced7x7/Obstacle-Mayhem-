#define FALSE 0
#define TRUE 1
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FPS 24
#define FRAME_TARGET_TIME (1000 / FPS)


void process_input()
{



    ///SA
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
        case SDL_SCANCODE_LSHIFT:
        {
            if(run_combine && !restrict_keypress)
                sprint_combine=1;
            if(!up && !sp_sprite5 && !ground_boundary_flag  && run_combine && !left_mov_sprite3 && !iori_buffer && !restrict_keypress && !end)
            {
                activateSprite(6);
                left=0;


            }

        }
        break;
        case SDL_SCANCODE_SPACE:  // Ensure character is not already jumping
        {
            if(!sp_sprite5 && !up && up_flag && !input_to_physics_tick && !iori_buffer && !restrict_keypress&& !end && !iori_normal_recoil)
            {
                up = 1;
                activateSprite(4);
                up_flag=0;
                ground_boundary_flag=1;


            }


        }
        break;

        case SDL_SCANCODE_S:  // Ensure character is not already jumping
        {
            if(!up && !sp_sprite5 && !ground_boundary_flag && !running_sprite6 && !iori_buffer && !iori_recoil&& !end && !restrict_keypress)
            {
                s_pressed=1;
            }


        }
        break;




        case SDL_SCANCODE_A:
        {
            //printf("h=%d h2= %d\n", hurt_c1_sprite10, hurt_c2_sprite11);
            if(!sp_sprite5 && !ground_boundary_flag && !running_sprite6 && !iori_buffer && !restrict_keypress&& !end && !hurt_c1_sprite10 &&  !hurt_c2_sprite11)
                left = 1;
            if(!up && !sp_sprite5 && !ground_boundary_flag && !running_sprite6 && !iori_buffer  && !restrict_keypress)
            {
                activateSprite(3);
                stand_frame1=0;


            }

        }
        break;
        //stand_sprite1, left_mov_sprite3, right_mov_sprite2, up_mov_sprite4, sp_sprite5


        case SDL_SCANCODE_D:
        {
            if(!sp_sprite5 && !ground_boundary_flag && !iori_buffer && !restrict_keypress&& !end  && !restrict_keypress && !hurt_c1_sprite10 &&  !hurt_c2_sprite11)
                right=1;
            if(!up && !sp_sprite5  && !ground_boundary_flag && !iori_buffer  && !restrict_keypress)
            {
                activateSprite(2);
                run_combine=1;
                stand_frame1=0;
            }
            if(s_pressed  && !restrict_keypress  && !iori_recoil)
                shinigami=1;


        }

        break;
        case SDL_SCANCODE_Q:
        {
            if(!sp_sprite5 && !up && !iori_buffer && !restrict_keypress&& !end  && !restrict_keypress && !iori_normal_recoil)
            {
                activateSprite(14);
                q_count=1;
            }
        }
        break;
        }






        break;


    ////



    case SDL_KEYUP:
        switch (event.key.keysym.scancode)
        {

        case SDL_SCANCODE_SPACE:
            if(!input_to_physics_tick && !iori_buffer  && !restrict_keypress)
            {
                up_flag=1;
            }
            break;

        case SDL_SCANCODE_A:
            left = 0;
            if(!sp_sprite5 && !ground_boundary_flag && !iori_buffer  && !restrict_keypress )
            {

                x_vel=0;
                if(!up && !right)
                    activateSprite(1);
                left_mov_sprite3=0;
                if(right)
                    activateSprite(2);
            }

            break;

        case SDL_SCANCODE_D:
            right = 0;
            run_combine=0;
            sprint_combine=0;
            s_pressed=0;
            shinigami=0;

            if(!sp_sprite5 && !ground_boundary_flag && !iori_buffer  && !restrict_keypress)
            {

                x_vel=0;
                if(!up && !left)
                    activateSprite(1);
                if(left)
                    activateSprite(3);

            }
            break;

            break;
        case SDL_SCANCODE_LSHIFT:
            sprint_combine=0;
            if(!sp_sprite5 && !ground_boundary_flag && !left_mov_sprite3 && !iori_buffer  && !restrict_keypress)
            {
                running_sprite6=0;
                if(!right)
                    run_combine=0;
                if(!right)
                    activateSprite(1);
                else if (right)
                    activateSprite(2);

            }
            break;


        case SDL_SCANCODE_K:
            if (!up && !left && !sp_sprite5 && !ground_boundary_flag && !running_sprite6 && !sprint_combine  && !restrict_keypress && !iori_normal_recoil)
            {
                right = 0;
                iori_buffer = 1;
                if(shinigami  && !iori_recoil)
                {
                    activateSprite(15);
                }
                else if(!combo_active )
                {
                    hit_combo1_frame7=0;
                    activateSprite(7);
                }
                else if (combo_active  )
                {
                    k_upped = 1;
                }



            }
            else if(!up && !left && !sp_sprite5 && !ground_boundary_flag && sprint_combine  && !restrict_keypress && !iori_normal_recoil)
            {
                right=0;
                iori_buffer = 1;
                if(!combo_active)
                {
                    running_hit_combo3_frame9=0;
                    activateSprite(9);
                }
                else
                {
                    k_upped = 1;
                }
            }




            break;
        case SDL_SCANCODE_S:  // Ensure character is not already jumping
            if(!restrict_keypress)
            {
                s_pressed=0;
                shinigami=0;
            }

            break;

        case SDL_SCANCODE_L:
            if (!up && !left && !sp_sprite5 && !ground_boundary_flag  && !restrict_keypress && !iori_normal_recoil)
            {
                right = 0;
                iori_buffer = 1;
                if(!combo_active)
                {
                    hit_combo2_frame8=0;
                    activateSprite(8);

                }
                else
                {
                    k_upped = 1;
                }

            }
            break;
        case SDL_SCANCODE_Q:
        {
            if(!sp_sprite5 && !up && !restrict_keypress && !iori_normal_recoil)
            {
                activateSprite(1);
                q_count=0;
            }
        }
        break;

        }

        break;
    }


    //printf("run_combine=%d sprint combine = %d\n", run_combine, sprint_combine);
    // printf("up=%d left = %d right = %d\n", up, left, right);
    //printf("stand_sprite1=%d, left_mov_sprite3=%d, right_mov_sprite2=%d, up_mov_sprite4=%d, sp_sprite5=%d\n", stand_sprite1, left_mov_sprite3, right_mov_sprite2, up_mov_sprite4, sp_sprite5);

    //crop_manip(stand_sprite1, right_mov_sprite2, left_mov_sprite3, up_mov_sprite4);

}
