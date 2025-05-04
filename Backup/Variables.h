#define FALSE 0
#define TRUE 1
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FPS 24
#define FRAME_TARGET_TIME (1000 / FPS)

int game_is_running = 0;
int last_frame_time = 0;
int image_width, image_height;
int frameWidth, frameHeight;
float frameTime = 0;
int currentFrame = 0; // Track the current frame of animation
int up, down, left, right;
float x_vel, y_vel;
int speed = 300;
int jumpForce = -500; // Adjust as needed
int gravity = 800;    // Adjust as needed

///sprite animation iori & orochi iori linked
int stand_sprite1=1, left_mov_sprite3=0, right_mov_sprite2=0, up_mov_sprite4=0, sp_sprite5=0, running_sprite6=0, hit_combo1_sprite7=0, hit_combo2_sprite8=0, running_hit_combo3_sprite9=0, hurt_c1_sprite10=0, hurt_c2_sprite11=0,
    interaction_start_sprite12=0, interaction_end_sprite13=0, block_sprite14=0, iori_shinigami_sprite15=0;
//

int count=0, count_offset=0;
int cap, cap1=1;
float offsetX = 1;
int offset_collisionx=187;
int i=0;
float speed_controller=6;
int sp_flag=0;
const int FONT_SIZE_TITLE = 90;
const int FONT_SIZE_PRESS_TO_START = 60;
const SDL_Color TEXT_COLOR = { 255, 255, 255, 255 }; // White
const char* TITLE_TEXT = "OBSTACLE MAYHEM";
const char* PRESS_TO_START_TEXT = "Press Enter To Start";
int iori_collision_range, kyo_collision_range;
//frame controller iori & orochi iori
int stand_frame1=0, left_right_frame2=0, up_frame3=0, sp_frame4=0, run_frame5=0, hit_combo1_frame7=0, hit_combo2_frame8=0, running_hit_combo3_frame9=0, hurt_c1_frame10=0, hurt_c2_frame11=0, interaction_start_frame12=9,
    interaction_end_frame13=13,block_frame14=0, iori_shinigami_frame15=0;
int iori_buffer=0;
int iori_c1_hit=0;
int left_consistent=0, right_consistent=0;
///
//COMBO
//Variables by abrar
int fast_run=0;
int collide=0;
int hurt_frame=0;
int q_count=0;
int restrict_keypress=0;
int fight_frame=0;
int end=0;
int iori_lost=0;
int iori_won=0;
int iori_recoil =100;
int iori_normal_recoil=0;


///

//orochi iori
int orochi_saga=0;

///input controller
int up_flag=0, ground_boundary_flag=0, input_to_physics_tick=0, run_combine=0, k_upped=0, combo_active=0, sprint_combine=0, combo_recoil=3;// will be updated later




///SDL_image (IORI / OROCHI IORI)

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* image_texture = NULL;
SDL_Rect texture_destination;
SDL_Texture* tile_texture = NULL;
SDL_Texture* tile_texture2 = NULL;
SDL_Rect select_tile = { 0,0,40,40 };

///KYO
SDL_Texture* kyo_texture = NULL;
int kyo_image_width, kyo_image_height;
int kyo_saga=1;
SDL_Rect kyo_texture_destination;


///sprite animation kyo
int kyo_stand_sprite1=1, kyo_left_mov_sprite3=0, kyo_right_mov_sprite2=0, kyo_up_mov_sprite4=0, kyo_sp_sprite5=0, kyo_running_sprite6=0,
    kyo_hit_combo1_sprite7=0, kyo_hit_combo2_sprite8=0, kyo_running_hit_combo3_sprite9=0, kyo_hurt_c1_sprite10=0, kyo_hurt_c2_sprite11=0, kyo_interaction_start_sprite12=0, kyo_interaction_end_sprite13=0,
    kyo_block_sprite14=0, kyo_shinigami_sprite15=0;

///KYO FRAME
int kyo_stand_frame1=0, kyo_left_right_frame2=0, kyo_up_frame3=0, kyo_sp_frame5=0, kyo_run_frame5=0, kyo_hit_combo1_frame7=0,
    kyo_hit_combo2_frame8=0, kyo_running_hit_combo3_frame9=0, kyo_hurt_c1_frame10=0, kyo_hurt_c2_frame11=0, kyo_interaction_start_frame12=0, kyo_interaction_end_frame13=13, kyo_block_frame14=12, kyo_shinigami_frame15=0;
int kyo_action_frame;
float kyo_frametime=0;
int rightmove = 0, leftmove = 1;



//MAP1
SDL_Texture * lvl_4_map_texture = NULL;
SDL_Rect lvl_4_map_texture_destination;
int lvl_4_frameWidth, lvl_4_frameHeight;
int map1=0;


//MAP2
SDL_Texture * lvl_4_map_texture2 = NULL;
SDL_Rect lvl_4_map_texture_destination2;
int map2=1;

//MAP3
SDL_Texture * lvl_4_map_texture3 = NULL;
SDL_Rect lvl_4_map_texture_destination3;
int map3_sprite=0;
int rain_frame=0;
int worldmap_frameTime=0;


///iori sp sprite
SDL_Texture* iori_sp_texture = NULL;
int iori_sp_frame_width, iori_sp_frame_height;
SDL_Rect iori_sp_texture_destination;


///KEY VARIABLES for shinigami;
int s_pressed = 0, shinigami=0;

///EFFECTS SPRITE & FRAME IORI
int iori_hand_effects_sprite1=0, iori_ground_effects_sprite2=0, iori_fin_effects_sprite3=0, hit_effect_sprite4=0;
int iori_hand_effects_frame1=0, iori_ground_effects_frame2=0, iori_fin_effects_frame3=0, hit_effect_frame4=0;
float iori_effects_frameTime=0;

///EFFECTS SPRITE & FRAME KYO
int kyo_hand_effects_sprite1=0, kyo_ground_effects_sprite2=0, kyo_fin_effects_sprite3=0, kyo_hit_effect_sprite4=0;
int kyo_hand_effects_frame1=0, kyo_ground_effects_frame2=0, kyo_fin_effects_frame3=0, kyo_hit_effect_frame4=0;
float kyo_effects_frameTime=0;


///KYO SP SPRITE
SDL_Texture* kyo_sp_texture = NULL;
int kyo_sp_frame_width, kyo_sp_frame_height;
SDL_Rect kyo_sp_texture_destination;


///IORI HEALTH BAR
SDL_Texture * iori_health_texture = NULL;
SDL_Rect iori_health_texture_destination;
int iori_health_sprite=1;
float iori_health_frame=0;
float iori_health_frameTime=0;

///HEALTH FRAMES
int health_width, health_height;

///KYO HEALTH BAR
SDL_Texture * kyo_health_texture = NULL;
SDL_Rect kyo_health_texture_destination;
int kyo_health_sprite=1;
int kyo_health_frame=0;
int kyo_health_frameTime=0;


///IORI FACE BOX
SDL_Texture * iori_face_texture = NULL;
SDL_Rect iori_face_texture_destination;
int face_frameWidth, face_frameHeight;


///KYO FACE BOX
SDL_Texture * kyo_face_texture = NULL;
SDL_Rect kyo_face_texture_destination;


///OROCHI IORI FACE BOX
SDL_Texture * orochi_iori_face_texture = NULL;
SDL_Rect orochi_iori_face_texture_destination;
int orochi_face_sprite=0;


///updated 6/6/24 2:21AM
