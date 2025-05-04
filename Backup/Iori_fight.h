int fight=0;

void iori_fight()
{
     x_vel = y_vel = 0;

// Determine velocity
    if (up)
        y_vel = -speed;
    if (down)
        y_vel = speed;
    if (left && !right)
        x_vel = -speed;
    if (!left && right)
        x_vel = speed;

// Update position at 1/30th of a second
    texture_destination.x += x_vel / (30-sprint_combine*13);
    texture_destination.y += y_vel / 30;

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
            up_mov_sprite4=1;
        else
            up_mov_sprite4=0;
    }

        if (texture_destination.x >= WINDOW_WIDTH - texture_destination.w+offset_collisionx-10)
            texture_destination.x = WINDOW_WIDTH - texture_destination.w+offset_collisionx-10;
        if (texture_destination.y >= WINDOW_HEIGHT - texture_destination.h)
            texture_destination.y = WINDOW_HEIGHT - texture_destination.h;

        if(hit_combo1_sprite7 && hit_combo1_frame7<33 && kyo_texture_destination.x-texture_destination.x<90 && !kyo_block_sprite14)
        {
            activateKyoSprite(10);

        }
        if(hit_combo2_sprite8 && hit_combo2_frame8<33 && kyo_texture_destination.x-texture_destination.x<115 && !kyo_block_sprite14)
        {
            activateKyoSprite(10);

        }
        if(running_hit_combo3_sprite9 && running_hit_combo3_frame9<16 && kyo_texture_destination.x-texture_destination.x<90 && !kyo_block_sprite14)
        {
            activateKyoSprite(10);

        }

}
