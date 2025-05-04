#define FALSE 0
#define TRUE 1
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FPS 24
#define FRAME_TARGET_TIME (1000 / FPS)


void crop_manip()///SA
{
    ///SA
    frameWidth= 440;
    frameHeight= 220;

    ///MAP
    lvl_4_frameWidth = 800, lvl_4_frameHeight = 600;

    ///IORI SP
    iori_sp_frame_width = 440, iori_sp_frame_height =312 ;

    ///
    health_width =100, health_height=13;

}


void animation_render_crop_controller()
{


    world_map();
    ///KYO
    if (kyo_stand_sprite1 || kyo_right_mov_sprite2 || kyo_left_mov_sprite3 || kyo_up_mov_sprite4 || kyo_sp_sprite5 || kyo_running_sprite6 ||
            kyo_running_sprite6 || kyo_hit_combo1_sprite7 || kyo_hit_combo2_sprite8 || kyo_running_hit_combo3_sprite9 || kyo_hurt_c1_sprite10 || kyo_hurt_c2_sprite11 ||  kyo_interaction_start_sprite12
            || kyo_interaction_end_sprite13 || kyo_block_sprite14 || kyo_shinigami_sprite15)
    {
        int offset_pixels = 0; // controls crop
        float source_row = 0;   // default to the first row
        if(kyo_stand_sprite1)
        {
            //printf("Working");

            source_row = 0.5;
            SDL_Rect source_rect = {(kyo_stand_frame1 * frameWidth), source_row * frameHeight, frameWidth, frameHeight};
            SDL_RenderCopy(renderer, kyo_texture, &source_rect, &kyo_texture_destination);
        }
        else if (kyo_right_mov_sprite2)
        {
            // If right movement, switch to the second row
            source_row = 1.9;
            SDL_Rect source_rect = {(kyo_left_right_frame2 * frameWidth), source_row * frameHeight, frameWidth, frameHeight};
            SDL_RenderCopy(renderer, kyo_texture, &source_rect, &kyo_texture_destination);
        }
        else if (kyo_left_mov_sprite3)
        {
            // If right movement, switch to the second row
            source_row =  3.3;
            SDL_Rect source_rect = {(kyo_left_right_frame2 * frameWidth), source_row * frameHeight, frameWidth, frameHeight};
            SDL_RenderCopy(renderer, kyo_texture, &source_rect, &kyo_texture_destination);
        }

        else if (kyo_up_mov_sprite4)
        {
            source_row = 4.7;
            SDL_Rect source_rect = {(kyo_up_frame3 * frameWidth) + offset_pixels, source_row * frameHeight, frameWidth, frameHeight};
            SDL_RenderCopy(renderer, kyo_texture, &source_rect, &kyo_texture_destination);
        }
        else if (kyo_sp_sprite5)
        {


            source_row = 6.1; // Stay in the same row
            SDL_Rect source_rect = {(kyo_sp_frame5 * frameWidth), source_row * frameHeight, frameWidth, frameHeight};
            SDL_RenderCopy(renderer, kyo_texture, &source_rect, &kyo_texture_destination);
        }
        else if (kyo_running_sprite6)
        {


            source_row = 7.52; // Stay in the same row
            SDL_Rect source_rect = {(kyo_run_frame5 * frameWidth), source_row * frameHeight, frameWidth, frameHeight};
            SDL_RenderCopy(renderer, kyo_texture, &source_rect, &kyo_texture_destination);
        }
        else if(kyo_hit_combo1_sprite7)
        {

            source_row = 8.905;
            SDL_Rect source_rect = {(kyo_hit_combo1_frame7 * frameWidth), source_row * frameHeight, frameWidth, frameHeight};
            SDL_RenderCopy(renderer, kyo_texture, &source_rect, &kyo_texture_destination);
        }
        else if(kyo_hit_combo2_sprite8)
        {
            source_row = 10.30;
            SDL_Rect source_rect = {(kyo_hit_combo2_frame8 * frameWidth), source_row * frameHeight, frameWidth, frameHeight};
            SDL_RenderCopy(renderer, kyo_texture, &source_rect, &kyo_texture_destination);
        }
        else if(kyo_running_hit_combo3_sprite9)
        {
            source_row = 11.7; //1.42 diff
            SDL_Rect source_rect = {(kyo_running_hit_combo3_frame9 * frameWidth), source_row * frameHeight, frameWidth, frameHeight};
            SDL_RenderCopy(renderer, kyo_texture, &source_rect, &kyo_texture_destination);
        }
        else if(kyo_hurt_c1_sprite10)
        {
            source_row = 13.1; //1.4 diff
            SDL_Rect source_rect = {(kyo_hurt_c1_frame10 * frameWidth), source_row * frameHeight, frameWidth, frameHeight};
            SDL_RenderCopy(renderer, kyo_texture, &source_rect, &kyo_texture_destination);
        }
        else if(kyo_hurt_c2_sprite11)
        {
            source_row = 14.5; //1.4 diff
            SDL_Rect source_rect = {(kyo_hurt_c2_frame11 * frameWidth), source_row * frameHeight, frameWidth, frameHeight};
            SDL_RenderCopy(renderer, kyo_texture, &source_rect, &kyo_texture_destination);
        }
        else if(kyo_interaction_start_sprite12)
        {
            source_row = 15.9; //1.4 diff
            SDL_Rect source_rect = {(kyo_interaction_start_frame12 * frameWidth), source_row * frameHeight, frameWidth, frameHeight};
            SDL_RenderCopy(renderer, kyo_texture, &source_rect, &kyo_texture_destination);
        }
        else if(kyo_interaction_end_sprite13)
        {
            source_row = 17.3; //1.4 diff
            SDL_Rect source_rect = {(kyo_interaction_end_frame13 * frameWidth), source_row * frameHeight, frameWidth, frameHeight};
            SDL_RenderCopy(renderer, kyo_texture, &source_rect, &kyo_texture_destination);
        }
        else if(kyo_block_sprite14)
        {
            source_row = 17.3; //1.4 diff
            SDL_Rect source_rect = {(kyo_block_frame14 * frameWidth), source_row * frameHeight, frameWidth, frameHeight};
            SDL_RenderCopy(renderer, kyo_texture, &source_rect, &kyo_texture_destination);
        }
        else if(kyo_shinigami_sprite15)
        {
            source_row = 18.7; //1.4 diff
            SDL_Rect source_rect = {(kyo_shinigami_frame15 * frameWidth), source_row * frameHeight, frameWidth, frameHeight};
            SDL_RenderCopy(renderer, kyo_texture, &source_rect, &kyo_texture_destination);
        }
    }

    ///SA
    ///IORI & OROCHI IORI
    if (stand_sprite1 || right_mov_sprite2 || left_mov_sprite3 || up_mov_sprite4 || sp_sprite5 || running_sprite6 || hit_combo1_sprite7 || hit_combo2_sprite8 || running_hit_combo3_sprite9 || hurt_c1_sprite10 ||
            hurt_c2_sprite11 || interaction_start_sprite12 || interaction_end_sprite13 || block_sprite14 || iori_shinigami_sprite15)
    {
        int offset_pixels = 0; // controls crop
        float source_row = 0;   // default to the first row
        if(stand_sprite1)
        {
            source_row = 0.5;
            SDL_Rect source_rect = {(stand_frame1 * frameWidth), source_row * frameHeight, frameWidth, frameHeight};
            SDL_RenderCopy(renderer, image_texture, &source_rect, &texture_destination);
        }
        else if (right_mov_sprite2)
        {
            source_row = 1.9;
            SDL_Rect source_rect = {(left_right_frame2 * frameWidth), source_row * frameHeight, frameWidth, frameHeight};
            SDL_RenderCopy(renderer, image_texture, &source_rect, &texture_destination); // Manually Tested!!!!(Don't change)
        }
        else if (left_mov_sprite3)
        {
            source_row =  3.3;
            SDL_Rect source_rect = {(left_right_frame2 * frameWidth), source_row * frameHeight, frameWidth, frameHeight};
            SDL_RenderCopy(renderer, image_texture, &source_rect, &texture_destination); // Manually Tested!!!!(Don't change)
        }

        else if (up_mov_sprite4)
        {
            source_row = 4.7;
            SDL_Rect source_rect = {(up_frame3 * frameWidth), source_row * frameHeight, frameWidth, frameHeight};
            SDL_RenderCopy(renderer, image_texture, &source_rect, &texture_destination);
        }
        else if (sp_sprite5)
        {


            source_row = 6.1;
            SDL_Rect source_rect = {(sp_frame4 * frameWidth), source_row * frameHeight, frameWidth, frameHeight};
            SDL_RenderCopy(renderer, image_texture, &source_rect, &texture_destination);
        }
        else if (running_sprite6)
        {


            source_row = 7.52;
            SDL_Rect source_rect = {(run_frame5 * frameWidth), source_row * frameHeight, frameWidth, frameHeight};
            SDL_RenderCopy(renderer, image_texture, &source_rect, &texture_destination);
        }

        else if(hit_combo1_sprite7)
        {

            source_row = 8.905;
            SDL_Rect source_rect = {(hit_combo1_frame7 * frameWidth), source_row * frameHeight, frameWidth, frameHeight};
            SDL_RenderCopy(renderer, image_texture, &source_rect, &texture_destination);
        }
        else if(hit_combo2_sprite8)
        {
            source_row = 10.30;
            SDL_Rect source_rect = {(hit_combo2_frame8 * frameWidth), source_row * frameHeight, frameWidth, frameHeight};
            SDL_RenderCopy(renderer, image_texture, &source_rect, &texture_destination);
        }
        else if(running_hit_combo3_sprite9)
        {
            source_row = 11.7; //1.42 diff
            SDL_Rect source_rect = {(running_hit_combo3_frame9 * frameWidth), source_row * frameHeight, frameWidth, frameHeight};
            SDL_RenderCopy(renderer, image_texture, &source_rect, &texture_destination);
        }
        else if(hurt_c1_sprite10)
        {
            source_row = 13.1; //1.4 diff
            SDL_Rect source_rect = {(hurt_c1_frame10 * frameWidth), source_row * frameHeight, frameWidth, frameHeight};
            SDL_RenderCopy(renderer, image_texture, &source_rect, &texture_destination);
        }
        else if(hurt_c2_sprite11)
        {
            source_row = 14.5; //1.4 diff
            SDL_Rect source_rect = {(hurt_c2_frame11 * frameWidth), source_row * frameHeight, frameWidth, frameHeight};
            SDL_RenderCopy(renderer, image_texture, &source_rect, &texture_destination);
        }
        else if(interaction_start_sprite12)
        {
            source_row = 15.9; //1.4 diff
            SDL_Rect source_rect = {(interaction_start_frame12 * frameWidth), source_row * frameHeight, frameWidth, frameHeight};
            SDL_RenderCopy(renderer, image_texture, &source_rect, &texture_destination);
        }
        else if(interaction_end_sprite13)
        {
            source_row = 17.3; //1.4 diff
            SDL_Rect source_rect = {(interaction_end_frame13 * frameWidth), source_row * frameHeight, frameWidth, frameHeight};
            SDL_RenderCopy(renderer, image_texture, &source_rect, &texture_destination);
        }
        else if(block_sprite14)
        {
            source_row = 17.3; //1.4 diff
            SDL_Rect source_rect = {(13 * frameWidth), source_row * frameHeight, frameWidth, frameHeight};
            SDL_RenderCopy(renderer, image_texture, &source_rect, &texture_destination);
        }
        else if(iori_shinigami_sprite15)
        {
            source_row = 18.7; //1.4 diff
            SDL_Rect source_rect = {(iori_shinigami_frame15 * frameWidth), source_row * frameHeight, frameWidth, frameHeight};
            SDL_RenderCopy(renderer, image_texture, &source_rect, &texture_destination);
        }
    }

    effects();
    kyo_effects();
    health_render();
    face_render();

}

void face_render()
{
    if(!orochi_saga)
        SDL_RenderCopy(renderer, iori_face_texture, NULL, &iori_face_texture_destination);
    else
        SDL_RenderCopy(renderer, orochi_iori_face_texture, NULL, &orochi_iori_face_texture_destination);
    ///Kyo
    SDL_RenderCopy(renderer, kyo_face_texture, NULL, &kyo_face_texture_destination);
}

void world_map()
{
    ///MAP 1
    if (map1)
    SDL_RenderCopy(renderer, lvl_4_map_texture, NULL, &lvl_4_map_texture_destination);

    ///MAP 2
    else if(map2)
    SDL_RenderCopy(renderer, lvl_4_map_texture2, NULL, &lvl_4_map_texture_destination2);

    ///MAP 3
    else if (map3_sprite)
    {
    SDL_Rect source_rect = {(rain_frame * lvl_4_frameWidth), 0, lvl_4_frameWidth, lvl_4_frameHeight};
    SDL_RenderCopy(renderer, lvl_4_map_texture3, &source_rect, &lvl_4_map_texture_destination3);
    }


}


void effects()
{
    if (iori_hand_effects_sprite1)
    {
        float source_row = 0;
        SDL_Rect source_rect = {(iori_hand_effects_frame1 * iori_sp_frame_width), source_row * iori_sp_frame_height, iori_sp_frame_width, iori_sp_frame_height};
        SDL_RenderCopy(renderer, iori_sp_texture, &source_rect, &iori_sp_texture_destination);

    }
    if (iori_ground_effects_sprite2)
    {
        float source_row = 1;
        SDL_Rect source_rect = {(iori_ground_effects_frame2 * iori_sp_frame_width), source_row * iori_sp_frame_height, iori_sp_frame_width, iori_sp_frame_height};
        SDL_RenderCopy(renderer, iori_sp_texture, &source_rect, &iori_sp_texture_destination);

    }
    if(iori_fin_effects_sprite3)
    {
        float source_row = 2;
        SDL_Rect source_rect = {(iori_fin_effects_frame3 * iori_sp_frame_width), source_row * iori_sp_frame_height, iori_sp_frame_width, iori_sp_frame_height};
        SDL_RenderCopy(renderer, iori_sp_texture, &source_rect, &iori_sp_texture_destination);
    }
    if(hit_effect_sprite4)
    {
        float source_row = 3;
        SDL_Rect source_rect = {(hit_effect_frame4 * iori_sp_frame_width), source_row * iori_sp_frame_height, iori_sp_frame_width, iori_sp_frame_height};
        SDL_RenderCopy(renderer, iori_sp_texture, &source_rect, &iori_sp_texture_destination);
    }
}

void kyo_effects()
{
    if (kyo_hand_effects_sprite1)
    {
        float source_row = 0;
        SDL_Rect source_rect = {(kyo_hand_effects_frame1 * iori_sp_frame_width), source_row * iori_sp_frame_height, iori_sp_frame_width, iori_sp_frame_height};
        SDL_RenderCopy(renderer, kyo_sp_texture, &source_rect, &kyo_sp_texture_destination);

    }
    if (kyo_ground_effects_sprite2)
    {
        float source_row = 1;
        SDL_Rect source_rect = {(kyo_ground_effects_frame2 * iori_sp_frame_width), source_row * iori_sp_frame_height, iori_sp_frame_width, iori_sp_frame_height};
        SDL_RenderCopy(renderer, kyo_sp_texture, &source_rect, &kyo_sp_texture_destination);

    }
    if(kyo_fin_effects_sprite3)
    {
        float source_row = 2;
        SDL_Rect source_rect = {(kyo_fin_effects_frame3 * iori_sp_frame_width), source_row * iori_sp_frame_height, iori_sp_frame_width, iori_sp_frame_height};
        SDL_RenderCopy(renderer, kyo_sp_texture, &source_rect, &kyo_sp_texture_destination);
    }
    if(kyo_hit_effect_sprite4)
    {
        float source_row = 3;
        SDL_Rect source_rect = {(kyo_hit_effect_frame4 * iori_sp_frame_width), source_row * iori_sp_frame_height, iori_sp_frame_width, iori_sp_frame_height};
        SDL_RenderCopy(renderer, kyo_sp_texture, &source_rect, &kyo_sp_texture_destination);
    }
}

void health_render()
{
    if(iori_health_sprite )
    {
        SDL_Rect source_rect = {(iori_health_frame * health_width), 0, health_width, health_height};
        SDL_RenderCopy(renderer, iori_health_texture, &source_rect, &iori_health_texture_destination);
    }
    if(kyo_health_sprite)
    {
        SDL_Rect source_rect = {(kyo_health_frame * health_width), 0, health_width, health_height};
        SDL_RenderCopy(renderer, kyo_health_texture, &source_rect, &kyo_health_texture_destination);
    }
}
