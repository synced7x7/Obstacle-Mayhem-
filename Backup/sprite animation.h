#define FALSE 0
#define TRUE 1
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FPS 24
#define FRAME_TARGET_TIME (1000 / FPS)



void iori_sprite_animation ()
{

    if (frameTime >= FPS / 7 && stand_sprite1 == 1) /// FPS/x (increase x to give more speed in animation)
    {
        frameTime = 0;
        //  printf("Stand frame = %d\n", stand_frame1);
        stand_frame1++; // Move to the next frame

        if (stand_frame1 >= 9) /// Change this if there aresse more frames ///det how much frames the sprite will run
        {
            stand_frame1 = 0; //Reset to the first frame
        }
    }
    else if (right_mov_sprite2 == 1 || left_mov_sprite3 ==1)
    {
        frameTime++;
        if (frameTime >= FPS / 7) /// FPS/x (increase x to give more speed in animation)
        {
            frameTime = 0;
            left_right_frame2++; // Move to the next frame
            // printf("lr frame = %d\n", left_right_frame2);
            if (left_right_frame2 >=12) /// Change this if there are more frames ///det how much frames the sprite will run
            {
                left_right_frame2 = 0; //Reset to the first frame
            }
        }
    }
    else if (up_mov_sprite4)
    {
        frameTime++;
        if (frameTime >= FPS / 8) /// FPS/x (increase x to give more speed in animation)
        {
            frameTime = 0;
            up_frame3++; // Move to the next frame
            input_to_physics_tick=1;
            if (up_frame3 >=10) /// Change this if there are more frames ///det how much frames the sprite will run
            {

                up_frame3=0;
                up_mov_sprite4=0;
                if(right)
                    right_mov_sprite2=1;
                else if(left)
                    left_mov_sprite3=1;
                else
                    stand_sprite1=1;


            }
        }
    }
    else if (sp_sprite5)
    {
        static int stopper = 0;
        frameTime++;
        static int repeat_count = 0;

        // Increment frame time
//        printf("orochi_face= %d\n", orochi_face_sprite);
        orochi_face_sprite=1;
        if (frameTime >= FPS / speed_controller)
        {
            frameTime = 0;

            // Control animation frames
            if (sp_frame4 == 7 && stopper < 4)
            {
                sp_frame4 = 6;
                stopper++;
            }
            else if (sp_frame4 == 6 || sp_frame4 == 5 || sp_frame4 == 4)
            {
                // Move back between frames 7, 6, and 5 for 3 to 4 repeats
                if (sp_frame4 == 5)
                    repeat_count++;

                if (repeat_count >= 3 && repeat_count <= 4)
                    sp_frame4--;
                else
                    sp_frame4++;
            }
            else
            {
                sp_frame4++;
            }

            // move back to frame 8 after repeating 7, 6, and 5
            if (stopper >= 3 && sp_frame4 == 5)
                sp_frame4 = 9;

            // Decrease speed_controller until the 8th frame
            if (sp_frame4 < 8 && speed_controller > 3)
                speed_controller -= 0.5;
            else if (sp_frame4 >= 8)
                speed_controller = 6;

            // Check if animation reached its end
            if (sp_frame4 >= 24)
            {
                orochi_face_sprite=1;
                stand_sprite1 = 1;
                sp_sprite5 = 0;
                orochi_saga=1;
                ///
                orochi_iori_face_texture_destination.x=40;
                orochi_iori_face_texture_destination.y=50;
                orochi_iori_face_texture_destination.w=120;
                orochi_iori_face_texture_destination.h=120;
                ///
                image_process();
                SDL_DestroyTexture(iori_face_texture);

            }
        }
    }

    else if (running_sprite6)
    {
        frameTime++;
        if (frameTime >= FPS / 7) /// FPS/x (increase x to give more speed in animation)
        {
            frameTime = 0;
            run_frame5++; // Move to the next frame
            if (run_frame5 >=6) /// Change this if there are more frames ///det how much frames the sprite will run
            {
                run_frame5 = 0; //Reset to the first frame
            }
        }
    }

    else if (hit_combo1_sprite7)
    {
        frameTime++;
        if (frameTime >= FPS / 7) /// FPS/x (increase x to give more speed in animation)
        {
            frameTime = 0;
            if(combo_active)
                hit_combo1_frame7++;

            if(hit_combo1_frame7==4 && !k_upped)
            {
                activateSprite(1);
                reset_iori_frame();
                reset_kyo_frame();
                activateKyoSprite(1);

            }
            else if(hit_combo1_frame7==4 && k_upped)
            {
                k_upped = 0;
            }
            else if(hit_combo1_frame7==9 && !k_upped)
            {
                activateSprite(1);
                reset_iori_frame();
                reset_kyo_frame();
                activateKyoSprite(1);

            }
            else if(hit_combo1_frame7==9 && k_upped)
            {
                k_upped = 0;
            }
            else if(hit_combo1_frame7==16 && !k_upped)
            {
                activateSprite(1);
                reset_iori_frame();
                reset_kyo_frame();
                activateKyoSprite(1);

            }
            else if(hit_combo1_frame7==16 && k_upped)
            {
                k_upped = 0;
            }
            else if(hit_combo1_frame7==24 && !k_upped)
            {
                activateSprite(1);
                reset_iori_frame();
                reset_kyo_frame();
                activateKyoSprite(1);

            }
            else if(hit_combo1_frame7==24 && k_upped)
            {
                k_upped = 0;
            }
            else if(hit_combo1_frame7==33)
            {
                k_upped = 0;
                activateSprite(1);
                reset_iori_frame();
                iori_normal_recoil = 80;
            }
            if(hit_combo1_frame7==27 && kyo_texture_destination.x-texture_destination.x<90)
            {
                activateKyoSprite(11);
                kyo_texture_destination.x +=80;
            }
            //printf("Iori combo 7 frame: %d\n", hit_combo1_frame7);
            //printf("hit_combo1_frame7=%d || k_upped=%d || combo_active=%d || iori buffer =%d\n", hit_combo1_frame7, k_upped, combo_active, iori_buffer);
        }
    }
    else if (hit_combo2_sprite8)
    {
        frameTime++;
        {
            if (frameTime >= FPS / 7) /// FPS/x (increase x to give more speed in animation)
            {
                frameTime = 0;
                if(combo_active)
                    hit_combo2_frame8++;

                if(hit_combo2_frame8==6 && !k_upped)
                {
                    activateSprite(1);
                    reset_iori_frame();
                    reset_kyo_frame();
                    activateKyoSprite(1);
                }
                else if(hit_combo2_frame8==6 && k_upped)
                {
                    k_upped = 0;
                }
                else if(hit_combo2_frame8==16 && !k_upped)
                {
                    activateSprite(1);
                    reset_iori_frame();
                    reset_kyo_frame();
                    activateKyoSprite(1);
                }
                else if(hit_combo2_frame8==16 && k_upped)
                {
                    k_upped = 0;
                }
                else if(hit_combo2_frame8==27)
                {
                    k_upped = 0;
                    reset_iori_frame();
                    activateSprite(1);
                    iori_normal_recoil = 80;

                }
                if(hit_combo2_frame8==21 && kyo_texture_destination.x-texture_destination.x<115)
                {
                    activateKyoSprite(11);
                    kyo_texture_destination.x +=80;
                }
            }
        }
    }
    else if (running_hit_combo3_sprite9)
    {
        frameTime++;
        if (frameTime >= FPS / 6) /// FPS/x (increase x to give more speed in animation)
        {
            frameTime = 0;
            if(combo_active)
                running_hit_combo3_frame9++;
            if(running_hit_combo3_frame9==8 && !k_upped)
            {
                activateSprite(1);
                reset_iori_frame();
                reset_kyo_frame();
                activateKyoSprite(1);
            }
            else if(running_hit_combo3_frame9==8 && k_upped)
            {
                k_upped = 0;
            }
            else if(running_hit_combo3_frame9==14 && !k_upped)
            {
                activateSprite(1);
                reset_iori_frame();
                reset_kyo_frame();
                activateKyoSprite(1);
            }
            else if(running_hit_combo3_frame9==14 && k_upped)
            {
                k_upped = 0;
            }
            else if(running_hit_combo3_frame9==21)
            {
                k_upped = 0;
                activateSprite(1);
                reset_iori_frame();
                iori_normal_recoil = 100;
            }
            if(running_hit_combo3_frame9==16 && kyo_texture_destination.x-texture_destination.x<90)
            {
                activateKyoSprite(11);
                kyo_texture_destination.x +=80;
            }
        }
    }
    else if (hurt_c1_sprite10)
    {
        frameTime++;
        if (frameTime >= FPS / 4) /// FPS/x (increase x to give more speed in animation)
        {
            frameTime = 0;
            hurt_c1_frame10++; // Move to the next frame
            if (hurt_c1_frame10 >= 11) /// Change this if there are more frames ///det how much frames the sprite will run
            {
                hurt_c1_frame10 = 0; //Reset to the first frame
                activateSprite(1);
            }
        }
    }
    else if (hurt_c2_sprite11)
    {
        if(iori_lost)
        {
            frameTime++;

            if (frameTime >= FPS / 5) /// FPS/x (increase x to give more speed in animation)
            {
                frameTime = 0;
                hurt_c2_frame11++; // Move to the next frame
                restrict_keypress=1;
                if (hurt_c2_frame11 >= 10) /// Change this if there are more frames ///det how much frames the sprite will run
                {
                    hurt_c2_frame11 = 10; //Reset to the first frame
                }
            }
        }
        else
        {
            frameTime++;

            if (frameTime >= FPS / 5) /// FPS/x (increase x to give more speed in animation)
            {
                frameTime = 0;
                hurt_frame=1;
                hurt_c2_frame11++; // Move to the next frame
                if(hurt_c2_sprite11)
                    restrict_keypress=1;
                else
                    restrict_keypress=0;
                if (hurt_c2_frame11 >= 16) /// Change this if there are more frames ///det how much frames the sprite will run
                {
                    hurt_c2_frame11 = 0; //Reset to the first frame
                    hurt_frame=0;
                    activateSprite(1);
                }
            }
        }
    }
    else if (interaction_start_sprite12)
    {
        frameTime++;
        if (frameTime >= FPS / 4) /// FPS/x (increase x to give more speed in animation)
        {
            frameTime = 0;
            if(interaction_start_frame12)
                interaction_start_frame12--;
            else
            {
                activateSprite(1);
            }



        }
    }
    else if (interaction_end_sprite13)
    {
        frameTime++;
        if (frameTime >= FPS / 4) /// FPS/x (increase x to give more speed in animation)
        {
            frameTime = 0;
            if(interaction_end_frame13)
                interaction_end_frame13--; // Move to the next frame

        }
    }
    else if (block_sprite14)
    {
        frameTime++;
        if (frameTime >= FPS / 6) /// FPS/x (increase x to give more speed in animation)
        {
            frameTime = 0;
            block_frame14++; // Move to the next frame
            if (block_frame14 >= 13) /// Change this if there are more frames ///det how much frames the sprite will run
            {
                block_frame14 = 0; //Reset to the first frame
            }
        }
    }
    else if (iori_shinigami_sprite15)
    {
        iori_recoil = 300;
        frameTime++;
        if (frameTime >= FPS / 5) /// FPS/x (increase x to give more speed in animation)
        {
            frameTime = 0;
            iori_shinigami_frame15++; // Move to the next frame
            //printf("iori shinigami = %d, shinigami sprite =%d \n", iori_shinigami_frame15, iori_shinigami_sprite15);
            if (iori_shinigami_frame15 >=10) /// Change this if there are more frames ///det how much frames the sprite will run
            {
                activateSprite(1);
                iori_shinigami_frame15=0;

                s_pressed=0;
                shinigami=0;
                // reset_effects_frame();
            }
        }
    }





}

void  orochi_iori_sprite_animation()
{
    if (frameTime >= FPS / 7 && stand_sprite1 == 1) /// FPS/x (increase x to give more speed in animation)
    {
        frameTime = 0;
        stand_frame1++; // Move to the next frame
        //printf("Stand frame = %d\n", stand_frame1);
        if (stand_frame1 >= 7) /// Change this if there are more frames ///det how much frames the sprite will run
        {
            stand_frame1 = 0; //Reset to the first frame
        }
    }
    else if (right_mov_sprite2 == 1 || left_mov_sprite3 ==1)
    {
        frameTime++;
        if (frameTime >= FPS / 7) /// FPS/x (increase x to give more speed in animation)
        {
            frameTime = 0;
            left_right_frame2++; // Move to the next frame
            //printf("lr frame = %d\n", left_right_frame2);
            //printf("frame= %d\n", left_right_frame2);
            if (left_right_frame2 >=12) /// Change this if there are more frames ///det how much frames the sprite will run
            {
                left_right_frame2 = 0; //Reset to the first frame
            }
        }
    }
    else if (up_mov_sprite4)
    {
        frameTime++;
        if (frameTime >= FPS / 8) /// FPS/x (increase x to give more speed in animation)
        {
            frameTime = 0;
            up_frame3++; // Move to the next frame
            input_to_physics_tick=1;
            if (up_frame3 >=10) /// Change this if there are more frames ///det how much frames the sprite will run
            {

                up_frame3=0;
                up_mov_sprite4=0;
                if(right)
                    right_mov_sprite2=1;
                else if(left)
                    left_mov_sprite3=1;
                else
                    stand_sprite1=1;


            }
        }
    }
    else if (running_sprite6)
    {
        frameTime++;
        if (frameTime >= FPS / 7) /// FPS/x (increase x to give more speed in animation)
        {
            frameTime = 0;
            run_frame5++; // Move to the next frame
            if (run_frame5 >=6) /// Change this if there are more frames ///det how much frames the sprite will run
            {
                run_frame5 = 0; //Reset to the first frame
            }
        }
    }
    else if (hit_combo1_sprite7)
    {
        right=0;
        left=0;
        frameTime++;
        if (frameTime >= FPS / 7) /// FPS/x (increase x to give more speed in animation)
        {
            frameTime = 0;
            if(combo_active)
                hit_combo1_frame7++;

            if(hit_combo1_frame7==4 && !k_upped)
            {
                activateSprite(1);
                reset_iori_frame();
                reset_kyo_frame();
                activateKyoSprite(1);

            }
            else if(hit_combo1_frame7==4 && k_upped)
            {
                k_upped = 0;
            }
            else if(hit_combo1_frame7==9 && !k_upped)
            {
                activateSprite(1);
                reset_iori_frame();
                reset_kyo_frame();
                activateKyoSprite(1);

            }
            else if(hit_combo1_frame7==9 && k_upped)
            {
                k_upped = 0;
            }
            else if(hit_combo1_frame7==16 && !k_upped)
            {
                activateSprite(1);
                reset_iori_frame();
                reset_kyo_frame();
                activateKyoSprite(1);

            }
            else if(hit_combo1_frame7==16 && k_upped)
            {
                k_upped = 0;
            }
            else if(hit_combo1_frame7==24 && !k_upped)
            {
                activateSprite(1);
                reset_iori_frame();
                reset_kyo_frame();
                activateKyoSprite(1);

            }
            else if(hit_combo1_frame7==24 && k_upped)
            {
                k_upped = 0;
            }
            else if(hit_combo1_frame7==33)
            {
                k_upped = 0;
                activateSprite(1);
                reset_iori_frame();
            }
            if(hit_combo1_frame7==27 && kyo_texture_destination.x-texture_destination.x<90)
            {
                activateKyoSprite(11);
                kyo_texture_destination.x +=80;
            }
            //printf("Iori combo 7 frame: %d\n", hit_combo1_frame7);
            //printf("hit_combo1_frame7=%d || k_upped=%d || combo_active=%d || iori buffer =%d\n", hit_combo1_frame7, k_upped, combo_active, iori_buffer);
        }
    }
    else if (hit_combo2_sprite8)
    {
        right=0;
        left=0;
        frameTime++;
        {
            if (frameTime >= FPS / 7) /// FPS/x (increase x to give more speed in animation)
            {
                frameTime = 0;
                if(combo_active)
                    hit_combo2_frame8++;

                if(hit_combo2_frame8==6 && !k_upped)
                {
                    activateSprite(1);
                    reset_iori_frame();
                    reset_kyo_frame();
                    activateKyoSprite(1);
                }
                else if(hit_combo2_frame8==6 && k_upped)
                {
                    k_upped = 0;
                }
                else if(hit_combo2_frame8==16 && !k_upped)
                {
                    activateSprite(1);
                    reset_iori_frame();
                    reset_kyo_frame();
                    activateKyoSprite(1);
                }
                else if(hit_combo2_frame8==16 && k_upped)
                {
                    k_upped = 0;
                }
                else if(hit_combo2_frame8==27)
                {
                    k_upped = 0;
                    reset_iori_frame();
                    activateSprite(1);

                }
                if(hit_combo2_frame8==21 && kyo_texture_destination.x-texture_destination.x<115)
                {
                    activateKyoSprite(11);
                    kyo_texture_destination.x +=80;
                }
            }
        }
    }
    else if (running_hit_combo3_sprite9)
    {
        frameTime++;
        if (frameTime >= FPS / 6) /// FPS/x (increase x to give more speed in animation)
        {
            frameTime = 0;
            if(combo_active)
                running_hit_combo3_frame9++;
            if(running_hit_combo3_frame9==8 && !k_upped)
            {
                activateSprite(1);
                reset_iori_frame();
                reset_kyo_frame();
                activateKyoSprite(1);
            }
            else if(running_hit_combo3_frame9==8 && k_upped)
            {
                k_upped = 0;
            }
            else if(running_hit_combo3_frame9==14 && !k_upped)
            {
                activateSprite(1);
                reset_iori_frame();
                reset_kyo_frame();
                activateKyoSprite(1);
            }
            else if(running_hit_combo3_frame9==14 && k_upped)
            {
                k_upped = 0;
            }
            else if(running_hit_combo3_frame9==21)
            {
                k_upped = 0;
                activateSprite(1);
                reset_iori_frame();
            }
            if(running_hit_combo3_frame9==16 && kyo_texture_destination.x-texture_destination.x<90)
            {
                activateKyoSprite(11);
                kyo_texture_destination.x +=80;
            }
        }
    }
    else if (hurt_c1_sprite10)
    {
        frameTime++;
        right=0;
        left=0;
        if (frameTime >= FPS / 4) /// FPS/x (increase x to give more speed in animation)
        {
            frameTime = 0;
            hurt_c1_frame10++; // Move to the next frame
            if (hurt_c1_frame10 >= 11) /// Change this if there are more frames ///det how much frames the sprite will run
            {
                hurt_c1_frame10 = 0; //Reset to the first frame
                activateSprite(1);
            }
        }
    }
    else if (hurt_c2_sprite11)
    {
        right=0;
        left=0;
        if(iori_lost)
        {
            frameTime++;

            if (frameTime >= FPS / 5) /// FPS/x (increase x to give more speed in animation)
            {
                frameTime = 0;
                hurt_c2_frame11++; // Move to the next frame
                restrict_keypress=1;
                if (hurt_c2_frame11 >= 10) /// Change this if there are more frames ///det how much frames the sprite will run
                {
                    hurt_c2_frame11 = 10; //Reset to the first frame
                }
            }
        }
        else
        {
            frameTime++;

            if (frameTime >= FPS / 5) /// FPS/x (increase x to give more speed in animation)
            {
                frameTime = 0;
                hurt_frame=1;
                hurt_c2_frame11++; // Move to the next frame
                if(hurt_c2_sprite11)
                    restrict_keypress=1;
                else
                    restrict_keypress=0;
                if (hurt_c2_frame11 >= 16) /// Change this if there are more frames ///det how much frames the sprite will run
                {
                    hurt_c2_frame11 = 0; //Reset to the first frame
                    hurt_frame=0;
                    activateSprite(1);
                }
            }
        }
    }
    else if (interaction_start_sprite12)
    {
        frameTime++;
        if (frameTime >= FPS / 4) /// FPS/x (increase x to give more speed in animation)
        {
            frameTime = 0;
            if(interaction_start_frame12)
                interaction_start_frame12--;
            else
            {
                activateSprite(1);
            }



        }
    }
    else if (interaction_end_sprite13)
    {
        frameTime++;
        if (frameTime >= FPS / 4) /// FPS/x (increase x to give more speed in animation)
        {
            frameTime = 0;
            if(interaction_end_frame13)
                interaction_end_frame13--; // Move to the next frame

        }
    }
    else if (block_sprite14)
    {
        frameTime++;
        if (frameTime >= FPS / 6) /// FPS/x (increase x to give more speed in animation)
        {
            frameTime = 0;
            block_frame14++; // Move to the next frame
            if (block_frame14 >= 13) /// Change this if there are more frames ///det how much frames the sprite will run
            {
                block_frame14 = 0; //Reset to the first frame
            }
        }
    }
    else if (iori_shinigami_sprite15)
    {
        frameTime++;
        if (frameTime >= FPS / 5) /// FPS/x (increase x to give more speed in animation)
        {
            frameTime = 0;
            iori_shinigami_frame15++; // Move to the next frame
            //printf("iori shinigami = %d, shinigami sprite =%d \n", iori_shinigami_frame15, iori_shinigami_sprite15);
            if (iori_shinigami_frame15 >=10) /// Change this if there are more frames ///det how much frames the sprite will run
            {
                activateSprite(1);
                iori_shinigami_frame15=0;
                iori_recoil = 10;
                s_pressed=0;
                shinigami=0;
                // reset_effects_frame();
            }
        }
    }






}

void kyo_sprite_animation()
{
    if (kyo_frametime >= FPS / 7 && kyo_stand_sprite1 == 1) /// FPS/x (increase x to give more speed in animation)
    {
        kyo_frametime = 0;
        //  printf("Stand frame = %d\n", stand_frame1);
        kyo_stand_frame1++; // Move to the next frame

        if (kyo_stand_frame1 >= 8) /// Change this if there are more frames ///det how much frames the sprite will run
        {
            kyo_stand_frame1 = 0; //Reset to the first frame
        }
    }
    else if (kyo_right_mov_sprite2 == 1 || kyo_left_mov_sprite3 ==1)
    {
        kyo_frametime++;
        if (kyo_frametime >= FPS / 7) /// FPS/x (increase x to give more speed in animation)
        {
            kyo_frametime = 0;
            kyo_left_right_frame2++; // Move to the next frame
            // printf("lr frame = %d\n", left_right_frame2);
            if (kyo_left_right_frame2 >=8) /// Change this if there are more frames ///det how much frames the sprite will run
            {
                kyo_left_right_frame2 = 0; //Reset to the first frame
            }
        }
    }
    else if (kyo_up_mov_sprite4)
    {
        kyo_frametime++;
        if (kyo_frametime >= FPS / 7) /// FPS/x (increase x to give more speed in animation)
        {
            kyo_frametime = 0;
            kyo_up_frame3++; // Move to the next frame
            // input_to_physics_tick=1;
            //printf("kyo_up_frame= %d\n", kyo_up_frame3);
            if (kyo_up_frame3 >=12) /// Change this if there are more frames ///det how much frames the sprite will run
            {
                if(rightmove)
                    activateKyoSprite(2);
                else if(leftmove)
                    activateKyoSprite(3);
                else
                    activateKyoSprite(1);


            }
        }
    }


    else if (kyo_sp_sprite5)
    {
        kyo_frametime++;
        if (kyo_frametime >= FPS / 7) /// FPS/x (increase x to give more speed in animation)
        {
            kyo_frametime = 0;
            kyo_sp_frame5++; // Move to the next frame
            // printf("lr frame = %d\n", left_right_frame2);
            if(kyo_sp_frame5==22)
                kyo_activate_effects_sprite(1);

            if (kyo_sp_frame5 >=32)
            {
                activateKyoSprite(1);
                kyo_sp_frame5  = 0;




            }
        }
    }

    else if (kyo_running_sprite6)
    {
        kyo_frametime++;
        if (kyo_frametime >= FPS / 7) /// FPS/x (increase x to give more speed in animation)
        {
            kyo_frametime = 0;
            kyo_run_frame5++; // Move to the next frame
            if (kyo_run_frame5 >=6) /// Change this if there are more frames ///det how much frames the sprite will run
            {
                kyo_run_frame5 = 0; //Reset to the first frame
            }
        }
    }
    else if (kyo_hit_combo1_sprite7)
    {
        kyo_frametime++;
        if (kyo_frametime >= FPS / 7) /// FPS/x (increase x to give more speed in animation)
        {
            kyo_frametime = 0;
            kyo_hit_combo1_frame7++;
            if(kyo_hit_combo1_frame7 >=35 )
            {
                kyo_hit_combo1_frame7=0;
                activateKyoSprite(1);
            }
        }
    }
    else if (kyo_hit_combo2_sprite8)
    {
        kyo_frametime++;
        {
            if (kyo_frametime >= FPS / 7) /// FPS/x (increase x to give more speed in animation)
            {
                kyo_frametime = 0;
                kyo_hit_combo2_frame8++;
                if(kyo_hit_combo2_frame8>=36)
                {
                    kyo_hit_combo2_frame8=0;
                    activateKyoSprite(1);
                }
            }
        }
    }
    else if (kyo_running_hit_combo3_sprite9)
    {
        kyo_frametime++;
        if (kyo_frametime >= FPS / 7) /// FPS/x (increase x to give more speed in animation)
        {
            kyo_frametime = 0;
            kyo_running_hit_combo3_frame9++;
            if(kyo_running_hit_combo3_frame9==36)
            {
                kyo_running_hit_combo3_frame9=0;
                activateKyoSprite(1);
            }

        }
    }
    else if (kyo_hurt_c1_sprite10)
    {
        kyo_frametime++;
        if (kyo_frametime >= FPS / 5) /// FPS/x (increase x to give more speed in animation)
        {
            kyo_frametime = 0;
            kyo_hurt_c1_frame10++; // Move to the next frame
            //printf("kyo hurt c1 frame = %d\n", kyo_hurt_c1_frame10);
            if (kyo_hurt_c1_frame10 >= 12) /// Change this if there are more frames ///det how much frames the sprite will run
            {
                kyo_hurt_c1_frame10 = 0; //Reset to the first frame
                activateKyoSprite(1);
            }
        }
    }
    else if (kyo_hurt_c2_sprite11)
    {
        printf("working\n");
        kyo_frametime++;
        if (kyo_frametime >= FPS / 5) /// FPS/x (increase x to give more speed in animation)
        {
            kyo_frametime = 0;
            kyo_hurt_c2_frame11++; // Move to the next frame
            //printf("kyofall =%d\n", kyo_hurt_c2_frame11);
            if (kyo_hurt_c2_frame11 >= 17) /// Change this if there are more frames ///det how much frames the sprite will run
            {
                kyo_hurt_c2_frame11 = 0; //Reset to the first frame
                activateKyoSprite(1);
            }
        }
    }
    else if (kyo_interaction_start_sprite12)
    {
        kyo_frametime++;
        if (kyo_frametime >= FPS / 5) /// FPS/x (increase x to give more speed in animation)
        {
            kyo_frametime = 0;
            kyo_interaction_start_frame12++; // Move to the next frame
            if (kyo_interaction_start_frame12 >= 22) /// Change this if there are more frames ///det how much frames the sprite will run
            {
                kyo_interaction_start_frame12 = 0; //Reset to the first frame
            }
        }
    }
    else if (kyo_interaction_end_sprite13)
    {
        if(iori_lost)
        {
            kyo_frametime++;
            if (kyo_frametime >= FPS / 7) /// FPS/x (increase x to give more speed in animation)
            {
                kyo_frametime = 0;
                kyo_interaction_end_frame13++; // Move to the next frame
                if (kyo_interaction_end_frame13 >= 12) /// Change this if there are more frames ///det how much frames the sprite will run
                {
                    kyo_interaction_end_frame13=12;
                }
            }
        }
        if(iori_won)
        {
            kyo_frametime++;
            if (kyo_frametime >= FPS / 4) /// FPS/x (increase x to give more speed in animation)
            {
                kyo_frametime = 0;
                kyo_interaction_end_frame13++; // Move to the next frame
                if (kyo_interaction_end_frame13 >= 16) /// Change this if there are more frames ///det how much frames the sprite will run
                {
                    kyo_interaction_end_frame13=16;
                }
            }
        }

    }
    else if (kyo_block_sprite14)
    {
        kyo_frametime++;
        if (kyo_frametime >= FPS / 6) /// FPS/x (increase x to give more speed in animation)
        {
            kyo_frametime = 0; // Move to the next frame
            kyo_block_frame14=17;
        }
    }
    else if (kyo_shinigami_sprite15)
    {
        kyo_frametime++;
        if (kyo_frametime >= FPS / 4.5) /// FPS/x (increase x to give more speed in animation)
        {
            kyo_frametime = 0;
            kyo_shinigami_frame15++; // Move to the next frame
            //printf("kyo shinigami = %d, kyo shinigami sprite =%d \n", kyo_shinigami_frame15, kyo_shinigami_sprite15);
            if (kyo_shinigami_frame15 >=9) /// Change this if there are more frames ///det how much frames the sprite will run
            {
                activateKyoSprite(1);
                kyo_shinigami_frame15=0;
            }
        }
    }


}


void world_map_animation()
{
    worldmap_frameTime++;
    if (worldmap_frameTime >= FPS / 6) /// FPS/x (increase x to give more speed in animation)
    {

        worldmap_frameTime=0;
        rain_frame++;
        //printf("rain frame =%d\n", rain_frame);

        if (rain_frame >= 5) /// Change this if there are more frames ///det how much frames the sprite will run
        {
            rain_frame = 0;
        }
    }
}

void effects_animation()
{
    //printf("iori_hand_effects_sprite1=%d\n", iori_hand_effects_sprite1);
    if(iori_hand_effects_sprite1)
    {
        iori_effects_frameTime++;
        if (iori_effects_frameTime >= FPS / 11) /// FPS/x (increase x to give more speed in animation)
        {

            iori_effects_frameTime=0;
            iori_hand_effects_frame1++;
            //printf("hand_frame =%d\n", iori_hand_effects_frame1);

            if ( iori_hand_effects_frame1 >= 9) /// Change this if there are more frames ///det how much frames the sprite will run
            {
                reset_effects_frame();
                activate_effects_sprite(3);

            }
        }
    }
    else if(iori_ground_effects_sprite2)
    {
        iori_effects_frameTime++;
        if (iori_effects_frameTime >= FPS / 11) /// FPS/x (increase x to give more speed in animation)
        {

            iori_effects_frameTime=0;
            iori_ground_effects_frame2++;
            //printf("hand_frame =%d\n", iori_hand_effects_frame1);

            if ( iori_ground_effects_frame2 >= 12) /// Change this if there are more frames ///det how much frames the sprite will run
            {
                reset_effects_sprites();
            }
        }
    }
    else if(iori_fin_effects_sprite3)
    {
        iori_sp_texture_destination.x+=10;
        iori_effects_frameTime++;
        if (iori_effects_frameTime >= FPS / 11) /// FPS/x (increase x to give more speed in animation)
        {

            iori_effects_frameTime=0;
            iori_fin_effects_frame3++;
            if(iori_sp_texture_destination.x >= kyo_texture_destination.x-40 && iori_sp_texture_destination.x <= kyo_texture_destination.x+40 && iori_sp_texture_destination.y == kyo_texture_destination.y-120)
            {
                reset_effects_frame();
                activate_effects_sprite(2);
            }
            //printf("kyoposx=%d kyoposy = %d\n", kyo_texture_destination.x, kyo_texture_destination.y);
            //printf("finx=%d, finy = %d\n", iori_sp_texture_destination.x, iori_sp_texture_destination.y);
            if ( iori_fin_effects_frame3 >= 8) /// Change this if there are more frames ///det how much frames the sprite will run
            {
                reset_effects_frame();
                //if(collide)
            }
        }
    }
    else if(hit_effect_sprite4)
    {

        iori_effects_frameTime++;

        if (iori_effects_frameTime >= FPS / 12 ) /// FPS/x (increase x to give more speed in animation)
        {
            iori_effects_frameTime=0;
            //printf("hit_effect_frame4=%d\n", hit_effect_frame4);
            hit_effect_frame4++;
            if(hit_combo2_frame8>8)
                hit_effect_sprite4=0;
            if ( hit_effect_frame4 >= 8 ) /// Change this if there are more frames ///det how much frames the sprite will run
            {
                reset_effects_frame();
                hit_effect_sprite4=0;
            }
        }


    }
}

void kyo_effects_animation()
{

    if(kyo_hand_effects_sprite1)
    {
        kyo_hand_effects_frame1++;
        //printf("hand_frame =%d\n", iori_hand_effects_frame1);

        if ( kyo_hand_effects_frame1 >= 26) /// Change this if there are more frames ///det how much frames the sprite will run
        {
            kyo_reset_effects_frame();
            kyo_activate_effects_sprite(3);
        }

    }
    else if(kyo_ground_effects_sprite2)
    {
        kyo_effects_frameTime++;
        if (kyo_effects_frameTime >= FPS / 11) /// FPS/x (increase x to give more speed in animation)
        {

            kyo_effects_frameTime=0;
            kyo_ground_effects_frame2++;

            //printf("hand_frame =%d\n", iori_hand_effects_frame1);

            if ( kyo_ground_effects_frame2 >= 24) /// Change this if there are more frames ///det how much frames the sprite will run
            {
                kyo_reset_effects_sprites();
            }
        }
    }
    else if(kyo_fin_effects_sprite3)
    {
        kyo_sp_texture_destination.x-=20;
        kyo_effects_frameTime++;
        if (kyo_effects_frameTime >= FPS / 11) /// FPS/x (increase x to give more speed in animation)
        {

            kyo_effects_frameTime=0;
            kyo_fin_effects_frame3++;
            if(kyo_sp_texture_destination.x >= texture_destination.x-40 && kyo_sp_texture_destination.x <= texture_destination.x+40 && kyo_sp_texture_destination.y == texture_destination.y-120)
            {
                kyo_reset_effects_frame();
                kyo_activate_effects_sprite(2);
            }
            if ( kyo_fin_effects_frame3 >= 4) /// Change this if there are more frames ///det how much frames the sprite will run
            {
                kyo_reset_effects_frame();
                //if(collide)
            }

        }
    }
    else if(kyo_hit_effect_sprite4)
    {
        kyo_effects_frameTime++;
        if (kyo_effects_frameTime >= FPS / 12) /// FPS/x (increase x to give more speed in animation)
        {

            kyo_effects_frameTime=0;
            //printf("hit_effect_frame4=%d\n", hit_effect_frame4);
            kyo_hit_effect_frame4++;
            if ( kyo_hit_effect_frame4 >= 8) /// Change this if there are more frames ///det how much frames the sprite will run
            {
                kyo_reset_effects_frame();
                kyo_hit_effect_sprite4=0;
            }

        }
    }

}

void health_bar_animation()
{

    if (iori_health_sprite)
    {

        iori_health_frameTime++;
        if (iori_health_frameTime >= FPS / 7) /// FPS/x (increase x to give more speed in animation)
        {
            iori_health_frameTime = 0;

            if(collide==1 && (kyo_hit_combo1_sprite7+kyo_hit_combo2_sprite8+kyo_running_hit_combo3_sprite9)>0 && q_count==0 && !block_sprite14) //&&!blcok
                iori_health_frame++;
            else if (kyo_ground_effects_sprite2)
                iori_health_frame+=3;
            if (iori_health_frame >=121) /// Change this if there are more frames ///det how much frames the sprite will run
            {
                iori_health_frame = 121; //Reset to the first frame
            }
        }
    }
    if (kyo_health_sprite)
    {
        kyo_health_frameTime++;
        if (kyo_health_frameTime >= FPS / 7) /// FPS/x (increase x to give more speed in animation)
        {
            kyo_health_frameTime = 0;
            //printf("kyo_health_bar frame =%d\n", kyo_health_frame);

            if(collide==1 && (hit_combo1_sprite7+hit_combo2_sprite8+running_hit_combo3_sprite9)>0 && q_count==0 && !kyo_block_sprite14) //&&!block
                kyo_health_frame++;
            else if (iori_ground_effects_sprite2)
                kyo_health_frame+=2;
            if (kyo_health_frame >=121) /// Change this if there are more frames ///det how much frames the sprite will run
            {
                kyo_health_frame = 0; //Reset to the first frame
            }
        }
    }
}

