#define FALSE 0
#define TRUE 1
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FPS 24
#define FRAME_TARGET_TIME (1000 / FPS)



void texture_destination_setup()
{
     //IORI Placement
    texture_destination.x=-140;
    texture_destination.y=300;
    texture_destination.w=frameWidth*1.1;///multiply both by any value to increase size without changing the aspect ratio
    texture_destination.h=frameHeight*1.1;

    ///KYO Placement
    //500
    kyo_texture_destination.x=500;
    kyo_texture_destination.y=300;
    kyo_texture_destination.w=frameWidth*1.1;///multiply both by any value to increase size without changing the aspect ratio
    kyo_texture_destination.h=frameHeight*1.1;


    //MAP 1
    lvl_4_map_texture_destination.x=0;
    lvl_4_map_texture_destination.y=0;
    lvl_4_map_texture_destination.w=lvl_4_frameWidth;
    lvl_4_map_texture_destination.h=lvl_4_frameHeight;

    //MAP 2
    lvl_4_map_texture_destination2.x=0;
    lvl_4_map_texture_destination2.y=0;
    lvl_4_map_texture_destination2.w=lvl_4_frameWidth;
    lvl_4_map_texture_destination2.h=lvl_4_frameHeight;

    //MAP 3
    lvl_4_map_texture_destination3.x=0;
    lvl_4_map_texture_destination3.y=0;
    lvl_4_map_texture_destination3.w=lvl_4_frameWidth;
    lvl_4_map_texture_destination3.h=lvl_4_frameHeight;

    ///EFFECTS IORI
    iori_sp_texture_destination.x=0;
    iori_sp_texture_destination.y=0;
    iori_sp_texture_destination.w=iori_sp_frame_width*1.1;
    iori_sp_texture_destination.h=iori_sp_frame_height*1.1;

    ///EFFECTS KYO
    kyo_sp_texture_destination.x=0;
    kyo_sp_texture_destination.y=0;
    kyo_sp_texture_destination.w=iori_sp_frame_width*1.1;
    kyo_sp_texture_destination.h=iori_sp_frame_height*1.1;

    ///IORI HEALTH BAR
    iori_health_texture_destination.x=140;
    iori_health_texture_destination.y=50;
    iori_health_texture_destination.w=health_width*2.5;
    iori_health_texture_destination.h=health_height*2.5;

    ///KYO HEALTH BAR
    kyo_health_texture_destination.x=420;
    kyo_health_texture_destination.y=50;
    kyo_health_texture_destination.w=health_width*2.5;
    kyo_health_texture_destination.h=health_height*2.5;


    ///IORI FACE

    iori_face_texture_destination.x=40;
    iori_face_texture_destination.y=50;
    iori_face_texture_destination.w=120;
    iori_face_texture_destination.h=120;

    ///OROCHI IORI FACE

    orochi_iori_face_texture_destination.x=-400;
    orochi_iori_face_texture_destination.y=50;
    orochi_iori_face_texture_destination.w=120;
    orochi_iori_face_texture_destination.h=120;




    ///KYO FACE
    kyo_face_texture_destination.x=650;
    kyo_face_texture_destination.y=50;
    kyo_face_texture_destination.w=120;
    kyo_face_texture_destination.h=120;

    ///IORI_SP_FACE
    iori_sp_back_texture_destination.x=-800;
    iori_sp_back_texture_destination.y=0;
    iori_sp_back_texture_destination.w=800;
    iori_sp_back_texture_destination.h=600;

    ///KYO SP FACE
    kyo_sp_back_texture_destination.x=800;
    kyo_sp_back_texture_destination.y=50;
    kyo_sp_back_texture_destination.w=800;
    kyo_sp_back_texture_destination.h=600;


}
