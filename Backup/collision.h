#define FALSE 0
#define TRUE 1
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FPS 24
#define FRAME_TARGET_TIME (1000 / FPS)


void collision()
{
    ///187 pixel inside for kyo
    ///260 pixel inside for iori
    iori_collision_range=texture_destination.x+262;
    kyo_collision_range=kyo_texture_destination.x+180;
    //if(iori_collision_range>=kyo_collision_range)
    // printf("players contact\n");
    if(iori_collision_range>=kyo_collision_range)
    {
        texture_destination.x = kyo_texture_destination.x + 180 - 262;
        collide=1;

    }
    else
        collide=0;

    if(collide==1 && (hit_combo1_sprite7+hit_combo2_sprite8+running_hit_combo3_sprite9)>0)
        activate_effects_sprite(4);

    if(collide==1 && (kyo_hit_combo1_sprite7+kyo_hit_combo2_sprite8+kyo_running_hit_combo3_sprite9)>0)
        kyo_activate_effects_sprite(4);

    if(iori_recoil)
        iori_recoil--;
    if(iori_normal_recoil)
        iori_normal_recoil--;

        printf("iori_recoil = %d, iori_normal_recoil = %d\n", iori_recoil, iori_normal_recoil );


}
