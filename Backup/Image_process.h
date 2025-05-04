#define FALSE 0
#define TRUE 1
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FPS 24
#define FRAME_TARGET_TIME (1000 / FPS)

void sprite_animation_MC()
{
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

    if(!orochi_saga)
    {
        ///MAP
        lvl_4_map_texture = initialize_texture_from_file("MAP 1_00000.png", renderer);
        lvl_4_map_texture2 = initialize_texture_from_file("MAP 2_00000.png", renderer);
        lvl_4_map_texture3 = initialize_texture_from_file("rain final stage.png", renderer);




        kyo_texture = initialize_texture_from_file("Kyo.png", renderer);

        iori_sp_texture = initialize_texture_from_file("iori sp_00000.png", renderer);

        kyo_sp_texture = initialize_texture_from_file("kyo effects_00000.png", renderer);

        ///HEALTH
        iori_health_texture = initialize_texture_from_file("iori health bar.png", renderer);
        kyo_health_texture = initialize_texture_from_file("kyo health bar.png", renderer);

        ///FACE

        iori_face_texture = initialize_texture_from_file("IORI FACE_00000.png", renderer);
        kyo_face_texture = initialize_texture_from_file("KYO FACE_00000.png", renderer);
        orochi_iori_face_texture = initialize_texture_from_file("OROCHI IORI FACE_00000.png", renderer);


    }

    ///PLAYERS
    if(!orochi_saga)
    {
        image_texture = initialize_texture_from_file("Iori.png", renderer);
    }

    if(orochi_saga)
            image_texture = initialize_texture_from_file("Orochi Iori.png", renderer);



    crop_manip();
}



