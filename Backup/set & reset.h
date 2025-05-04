#define FALSE 0
#define TRUE 1
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FPS 24
#define FRAME_TARGET_TIME (1000 / FPS)


// Function to reset sprites
void resetSprites()
{
    stand_sprite1 = 0;
    left_mov_sprite3 = 0;
    right_mov_sprite2 = 0;
    up_mov_sprite4 = 0;
    sp_sprite5 = 0;
    running_sprite6 = 0;
    hit_combo1_sprite7 = 0;
    hit_combo2_sprite8 = 0;
    running_hit_combo3_sprite9 = 0;
    hurt_c1_sprite10 = 0;
    hurt_c2_sprite11 = 0;
    interaction_start_sprite12 = 0;
    interaction_end_sprite13 = 0;
    block_sprite14 = 0;
    combo_active=0;
    iori_buffer=0;
    iori_shinigami_sprite15=0;
    restrict_keypress = 0;

}

// Function to activate a specific sprite
void activateSprite(int sprite)
{
    resetSprites(); // Reset all sprites to 0

    // Activate the specified sprite
    switch (sprite)
    {
    case 1:
        stand_sprite1 = 1;
        break;
    case 2:
        right_mov_sprite2 = 1;
        break;
    case 3:
        left_mov_sprite3 = 1;
        break;
    case 4:
        up_mov_sprite4 = 1;
        break;
    case 5:
        sp_sprite5 = 1;
        break;
    case 6:
        running_sprite6 = 1;
        break;
    case 7:
        hit_combo1_sprite7 = 1;
        combo_active=1;
        iori_buffer=1;
        break;
    case 8:
        hit_combo2_sprite8 = 1;
        combo_active=1;
        iori_buffer=1;
        break;
    case 9:
        running_hit_combo3_sprite9 = 1;
        combo_active=1;
        iori_buffer=1;
        break;
    case 10:
        hurt_c1_sprite10 = 1;
        break;
    case 11:
        hurt_c2_sprite11 = 1;
        restrict_keypress=1;
        break;
    case 12:
        interaction_start_sprite12 = 1;
        restrict_keypress = 1;
        break;
    case 13:
        interaction_end_sprite13 = 1;
        restrict_keypress =1;
        break;
    case 14:
        block_sprite14 = 1;
        break;
    case 15:
        iori_shinigami_sprite15 = 1;
        restrict_keypress = 1;
        activate_effects_sprite(1);
        break;
    default:
        printf("Invalid IORI sprite number!\n");
        break;
    }
}

void resetKyoSprites()
{
    kyo_stand_sprite1 = 0;
    kyo_left_mov_sprite3 = 0;
    kyo_right_mov_sprite2 = 0;
    kyo_up_mov_sprite4 = 0;
    kyo_running_sprite6 = 0;
    kyo_hit_combo1_sprite7 = 0;
    kyo_hit_combo2_sprite8 = 0;
    kyo_running_hit_combo3_sprite9 = 0;
    kyo_hurt_c1_sprite10 = 0;
    kyo_hurt_c2_sprite11 = 0;
    kyo_interaction_start_sprite12 = 0;
    kyo_interaction_end_sprite13 = 0;
    kyo_block_sprite14 = 0;
    kyo_shinigami_sprite15=0;
    kyo_sp_sprite5=0;
}

// Function to activate a specific sprite
void activateKyoSprite(int sprite)
{
    resetKyoSprites(); // Reset all sprites to 0

    // Activate the specified sprite
    switch (sprite)
    {
    case 1:
        kyo_stand_sprite1 = 1;
        break;
    case 2:
        kyo_right_mov_sprite2 = 1;
        break;
    case 3:
        kyo_left_mov_sprite3 = 1;
        break;
    case 4:
        kyo_up_mov_sprite4 = 1;
        break;
    case 5:
        kyo_sp_sprite5 = 1;
        restrict_keypress=1;
        break;
    case 6:
        kyo_running_sprite6 = 1;
        break;
    case 7:
        kyo_hit_combo1_sprite7 = 1;
        break;
    case 8:
        kyo_hit_combo2_sprite8 = 1;
        break;
    case 9:
        kyo_running_hit_combo3_sprite9 = 1;
        break;
    case 10:
        kyo_hurt_c1_sprite10 = 1;
        break;
    case 11:
        kyo_hurt_c2_sprite11 = 1;
        break;
    case 12:
        kyo_interaction_start_sprite12 = 1;
        restrict_keypress=1;
        break;
    case 13:
        kyo_interaction_end_sprite13 = 1;
        break;
    case 14:
        kyo_block_sprite14=1;
        break;
    case 15:
        kyo_shinigami_sprite15=1;
        kyo_activate_effects_sprite(1);
        break;
    default:
        printf("Invalid KYO sprite number! Check break properly\n");
        break;
    }
}


void reset_iori_frame()
{
    stand_frame1=0, left_right_frame2=0, up_frame3=0, sp_frame4=0, run_frame5=0, hit_combo1_frame7=0, hit_combo2_frame8=0,
    running_hit_combo3_frame9=0, hurt_c1_frame10=0, hurt_c2_frame11=0, interaction_start_frame12=13, interaction_end_frame13=13;

}

void reset_kyo_frame()
{
    kyo_stand_frame1=0, kyo_left_right_frame2=0, kyo_up_frame3=0, kyo_sp_frame5=0, kyo_run_frame5=0, kyo_hit_combo1_frame7=0,
    kyo_hit_combo2_frame8=0, kyo_running_hit_combo3_frame9=0, kyo_hurt_c1_frame10=0, kyo_hurt_c2_frame11=0, kyo_interaction_start_frame12=0;
}

void reset_effects_sprites()
{
    iori_hand_effects_sprite1=0, iori_ground_effects_sprite2=0, iori_fin_effects_sprite3=0, hit_effect_sprite4=0;
}

// Function to activate a specific sprite
void activate_effects_sprite(int sprite)
{
    reset_effects_sprites(); // Reset all sprites to 0

    // Activate the specified sprite
    switch (sprite)
    {
    case 1:
        iori_hand_effects_sprite1=1;
        iori_sp_texture_destination.x=texture_destination.x+30;
        iori_sp_texture_destination.y=texture_destination.y-170;
        //printf("xpos =%d, y pos = %d\n", texture_destination.x, texture_destination.y);
        break;
    case 2:
        iori_ground_effects_sprite2=1;
        activateKyoSprite(11);
        break;
    case 3:
        iori_fin_effects_sprite3=1;
        iori_sp_texture_destination.x=texture_destination.x+30;
        iori_sp_texture_destination.y=texture_destination.y-120;
        break;
    case 4:
        hit_effect_sprite4=1;
        iori_sp_texture_destination.x = kyo_texture_destination.x-20;
        iori_sp_texture_destination.y = kyo_texture_destination.y-200;
        break;
    default:
        printf("Invalid sprite number!\n");
        break;
    }
}

void reset_effects_frame()
{
    iori_hand_effects_frame1=0, iori_ground_effects_frame2=0, iori_fin_effects_frame3=0, hit_effect_frame4=0;
}

void kyo_reset_effects_sprites()
{
    kyo_hand_effects_sprite1=0, kyo_ground_effects_sprite2=0, kyo_fin_effects_sprite3=0, kyo_hit_effect_sprite4=0;
}

// Function to activate a specific sprite
void kyo_activate_effects_sprite(int sprite)
{
    kyo_reset_effects_sprites(); // Reset all sprites to 0

    // Activate the specified sprite
    switch (sprite)
    {
    case 1:
        kyo_hand_effects_sprite1=1;
        kyo_sp_texture_destination.x=kyo_texture_destination.x+10;
        kyo_sp_texture_destination.y=kyo_texture_destination.y-160;
        //printf("xpos =%d, y pos = %d\n", texture_destination.x, texture_destination.y);
        break;
    case 2:
        kyo_ground_effects_sprite2=1;
        activateSprite(11);
        break;
    case 3:
        kyo_fin_effects_sprite3=1;
        kyo_sp_texture_destination.x=kyo_texture_destination.x;
        kyo_sp_texture_destination.y=kyo_texture_destination.y-120;
        break;
    case 4:
        kyo_hit_effect_sprite4=1;
        kyo_sp_texture_destination.x = texture_destination.x+30;
        kyo_sp_texture_destination.y = texture_destination.y-200;
        break;

    default:
        printf("Invalid sprite number!\n");
        break;
    }
}

void kyo_reset_effects_frame()
{
    kyo_hand_effects_frame1=0, kyo_ground_effects_frame2=0, kyo_fin_effects_frame3=0, kyo_hit_effect_frame4=0;
}

void reset_map()
{
    map1=0, map2=0, map3_sprite=0;
}
void map_activator(int sprite)
{
    reset_map();
    switch (sprite)
    {
    case 1:
        map1=1;
        break;
    case 2:
        map2=1;
        break;
    case 3:
        map3_sprite=1;
        break;
    }

}
