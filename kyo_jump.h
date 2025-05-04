int velocity = 300;
int kyo_recognised = 0;

void kyo_jump()
{
    //printf("kyo_recognised = %d diff = %d\n", kyo_recognised, kyo_texture_destination.x - texture_destination.x);

    if (iori_fin_effects_sprite3 && (kyo_texture_destination.x - texture_destination.x) > 200)
    {
        kyo_recognised = 1;

        if (kyo_recognised && (kyo_texture_destination.x - iori_sp_texture_destination.x) <= 130 && !kyo_shinigami_sprite15)
        {
            rightmove = 0;
            leftmove = 1;
            activateKyoSprite(4);
            kyo_recognised = 0;
        }
    }
    printf("%d\n",kyo_texture_destination.y);
    if (kyo_up_mov_sprite4)
    {
        //printf("works\n");
        kyo_texture_destination.y -= velocity / 30;

        if (kyo_texture_destination.y <= 200) // sky boundary - capping jump
        {
            kyo_texture_destination.y = 200;
            velocity = -velocity;
        }
        if (kyo_texture_destination.y >= 300) // ground boundary
        {
            velocity=0;
            activateKyoSprite(1);
            kyo_texture_destination.y = 300;
        }
    }
}
