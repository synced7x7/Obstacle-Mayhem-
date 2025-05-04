#include <time.h>
int kyo_fastmove=0;
int kyo_hitting=0;
int iori_hurt=0;
int interaction_count=0;
int start_end=0;//Variable to check if sprite is at start or end of a frameset
int random_block=0;
int hit=0;
int kyo_lag=0;
int block=0;
int block_delay=0;
int stance_generate=1;
int random_number=7;
int collide_lag=0;
int fight_lag=0;
int block_range=70;
int easy_attack=5;//increase for easier attack
int block_prone=1;//Increase for more ky blocks
int boundary=0;
int boundary_delay=0;
int special_prone=3;//Decrease for more frequent specials
int general_frame=0;
int general_count=0;
int memory=0;
int random_jump=0;

int kyo_recognised = 0;

void kyo_algorithm_hard()
{


        if(kyo_hurt_c2_sprite11)
            leftmove=0, rightmove=0;
        if(kyo_hurt_c2_sprite11==0 && !rightmove && !leftmove && !end && !block && boundary!=special_prone)
        {
            rightmove=1;
        }



        // Window Boundary
        if (kyo_texture_destination.x <= 0 - offset_collisionx)
        {
            kyo_texture_destination.x = 0 - offset_collisionx;
            leftmove = 0; // Stop left movement if at left boundary
            rightmove=1;
        }
        if (kyo_texture_destination.y >= WINDOW_HEIGHT - kyo_texture_destination.h) {
            kyo_texture_destination.y = WINDOW_HEIGHT - kyo_texture_destination.h;
        }

        if (kyo_texture_destination.x >= WINDOW_WIDTH - kyo_texture_destination.w + offset_collisionx + 10)
        {
            kyo_texture_destination.x = WINDOW_WIDTH - kyo_texture_destination.w + offset_collisionx + 10;
            rightmove = 0; // Stop right movement if at right boundary
            if(!kyo_shinigami_sprite15)
                leftmove = 1; // Ensure kyo stops moving after reaching the boundary
        }


        //Automated movement




        if(abs(kyo_texture_destination.x-texture_destination.x)<=300)
        {
            kyo_fastmove=0;
        }
        if(abs(kyo_texture_destination.x-texture_destination.x)>450)
        {
            kyo_fastmove=1;
            //removing these 2 following conditions will make the character sprint only after reaching righmost end
            if(!kyo_shinigami_sprite15)
            leftmove=1;
            rightmove = 0;
        }
        //printf("fire %d\n",kyo_sp_texture_destination.x);
        //printf("distance %d\n",kyo_texture_destination.x-texture_destination.x);


        //printf("kyo_stand left right delay: %d %d %d %d\n",kyo_stand_sprite1,leftmove,rightmove,kyo_lag);
        if(kyo_stand_sprite1==1)
        {
            kyo_lag++;
            if(kyo_lag>40)
            {
                kyo_hitting=0;
                rightmove=1;
                leftmove=0;
                kyo_lag=0;
            }
        }
        if(kyo_hit_combo1_sprite7 + kyo_hit_combo2_sprite8+ kyo_running_hit_combo3_sprite9==0)
        {
            restrict_keypress=0;
        }
        if(kyo_running_hit_combo3_frame9>=10)
        {
            activateKyoSprite(1);
            hit=0;
        }
        if(hurt_c2_sprite11 || end==1)
        {
            restrict_keypress=1;
            //printf("BUG\n");
        }
        if(hurt_c2_sprite11==0 && collide==0)
            restrict_keypress=0;
        if(hurt_c2_frame11==9 || hurt_c2_frame11==10)
        {
            speed=0;
        }
        if(hurt_c2_frame11!=9 || hurt_c2_frame11!=10)
        {
            speed=300;
        }


        block_delay++;
        if(block_delay>100)
            block_delay=0;
        srand(time(NULL));
        int min = 0;
        int max = block_prone;
        int range1 = max - min + 1;
        random_block = rand() % range1 + min;



            //printf("Kyo iori: %d %d\n",kyo_texture_destination.x,texture_destination.x);

        if(kyo_texture_destination.x-texture_destination.x>82+70)
        {
            stance_generate=1;
            block_delay=0;
        }

        //printf(" distance %d\n",kyo_texture_destination.x-texture_destination.x);

        if(kyo_texture_destination.x-texture_destination.x<=82+70)
        {
            //printf("WORKING\n");
            if(stance_generate==1)
            {
                if(random_block)
                {
                    block=1;//Will block
                    block_delay=0;
                    //printf("W\n");
                }
                else
                {
                    block=0;//Move to attacking position
                }
            }
            stance_generate=0;
            //printf("%d %d\n",kyo_texture_destination.x-texture_destination.x,block_delay);
            //Collision Sprite Generation
            if(collide==1 && block==1 && block_delay<block_range)
            {
                activateKyoSprite(14);
                block_delay++;
            }
            if(block_delay>=block_range)
            {
                block=0;
            }


            //kyo basicccc

            srand(time(NULL));
            int mn = 7;
            int mx = 9;
            int range = mx - mn + 1;
            random_number = rand() % range + mn;
            //printf("interaction startend %d %d\n",interaction_count,start_end);
            //Collision Sprite Generation
            if (collide==1 && interaction_count==1)
            {
                //printf("left kyo %d\n",kyo_right_mov_sprite2);
                if(kyo_right_mov_sprite2==1)
                {
                    collide_lag++;
                    if(collide_lag>3)
                        start_end=1;
                }
                if(start_end==1)
                    activateKyoSprite(random_number);
            }
            if(collide==1 && (kyo_hit_combo2_frame8>=3)||(kyo_hit_combo1_frame7>=3)||(kyo_running_hit_combo3_frame9>=3))
            {
                if(kyo_running_hit_combo3_sprite9)
                {
                    hit=1;
                    activateSprite(11);
                    restrict_keypress=1;
                    texture_destination.x -=80*hurt_frame;
                }
                if((kyo_hit_combo2_sprite8 || kyo_hit_combo1_sprite7) && q_count==0)
                {
                    activateSprite(10);
                }
                if((kyo_hit_combo2_sprite8 || kyo_hit_combo1_sprite7) && q_count==1)
                {
                    activateSprite(14);
                }
                if((kyo_hit_combo1_sprite7 || kyo_hit_combo2_sprite8 || kyo_running_hit_combo3_sprite9))
                {

                    fight_lag++;
                    if(fight_lag>easy_attack)//////DECREASE THIS 10 FOR HARDER
                    {
                        restrict_keypress=1;
                        //printf("WORKS %d\n",fight_lag);
                    }
                }
            }


            if(hit==1 && collide==0)
            {
                kyo_running_hit_combo3_frame9=0;// This is used to reset frames after collission=1 but residual frame=5 due to collssion=0 afterwards
                kyo_hit_combo1_frame7=0;
                kyo_hit_combo2_frame8=0;
            }

            if(collide==0 && kyo_running_hit_combo3_frame9>=10)
                kyo_running_hit_combo3_sprite9=0;

            if (collide == 1)
            {
                if(kyo_texture_destination.y!=300)
                    kyo_texture_destination.y=300;
                //The below 2 conditions are for generating random kyo hitting sprite when collision happens
                if(kyo_hit_combo2_frame8+kyo_hit_combo1_frame7+kyo_running_hit_combo3_frame9==0 && block==0)
                    start_end=1;
                else
                    start_end=0;


                leftmove = 0;  // Stop left movement
                rightmove = 0; // Start right movement
                kyo_hitting=1;
                iori_hurt=1;
                interaction_count=1;
                if(kyo_hit_combo2_frame8==33||kyo_hit_combo1_frame7==33||kyo_running_hit_combo3_frame9==10)//total 35 hit frames
                {
                    collide=0;
                    kyo_hit_combo1_frame7=0;
                    kyo_hit_combo2_frame8=0;
                    kyo_running_hit_combo3_frame9=0;
                    kyo_hitting=0;
                    rightmove=1;

                    hurt_c1_frame10=0;
                    iori_hurt=0;
                    activateSprite(1);
                    //printf("b\n");
                    //start_end=0;
                }
            }

            if(collide==0 && interaction_count==1)// If I try to move away when kyo is hitting, variables must be reset
            {
                kyo_hitting=0;
                iori_hurt=0;
                kyo_hit_combo1_frame7=0;
                kyo_hit_combo2_frame8=0;
                kyo_running_hit_combo3_frame9=0;
               // printf("c\n");
                interaction_count=0;
                start_end=0;
                fight_lag=0;
                if(texture_destination.x<120)
                {
                    leftmove=0;
                    rightmove=1;
                }
                else if(texture_destination.x>=120)
                {
                    leftmove=1;
                    rightmove=0;
                }
            }
        }

        //printf("kyo health frame =%d\n", kyo_health_frame);
        if(kyo_health_frame>=120 && halt_flag==4)///champu
        {
            end=1;
            rightmove=0;
            leftmove=0;
            restrict_keypress=1;
            if(iori_lost+iori_won==0)
                kyo_interaction_end_frame13=13;
            iori_won=1;
            activateKyoSprite(13);
            activateSprite(13);
        }
        if(iori_health_frame>=120)///champu
        {
            end=1;
            rightmove=0;
            leftmove=0;
            restrict_keypress=1;
            if(iori_lost+iori_won==0)
                kyo_interaction_end_frame13=0;
            iori_lost=1;
            activateKyoSprite(13);
            activateSprite(11);
        }

        general_frame++;
        if(general_frame>5000)
            general_frame=0;
        if( collide ==0 && (rightmove==1 || general_count==1))
        {
            general_count=0;
            memory=general_frame;
        }
        if(collide==0 && rightmove ==0 && leftmove==1 && general_frame-memory==1 && kyo_texture_destination.x>120)
        {
            boundary++;
        }

        if(boundary==special_prone && general_frame-memory==1)
            boundary_delay=0;

        if(boundary==special_prone && boundary_delay==0 && kyo_texture_destination.x-texture_destination.x>100)
        {
            leftmove=0;
            rightmove=0;
            activateKyoSprite(15);
        }
        boundary_delay++;
        if(boundary_delay && boundary_delay<43 && boundary==special_prone)
        {
            rightmove=0;
            leftmove=0;
        }
        if(boundary_delay==43 && boundary==special_prone)
        {
             boundary_delay=0;
             boundary=0;
        }
        //printf("generate %d\n",stance_generate);
        //printf("ky hiy %d\n",hit_combo1_frame7);
        //printf("restrict %d\n",restrict_keypress);
        //printf("rightmove,leftmove,iori_hurt,kyo_hitting  %d %d %d %d\n",rightmove,leftmove,iori_hurt,kyo_hitting );
        //Automated movement








        if (rightmove && !kyo_hitting)//Automated right movement
        {
            kyo_texture_destination.x += 300 / 30;
            activateKyoSprite(3);
        }
        if (leftmove && !kyo_hitting)//Automated left movement
        {
            kyo_texture_destination.x -= 300 / (30-10 *kyo_fastmove);
            if(kyo_fastmove==0)
                activateKyoSprite(2);
            else
                activateKyoSprite(6);
        }

        //hit_effect_frame4=14
        //code by ekanto
        srand(time(NULL));
        int min3 = 0;
        int max3 = 1;
        int range3 = max3 - min3 + 1;
        random_jump = rand() % range3 + min;
        if (iori_fin_effects_sprite3 && random_jump)
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
//        printf("%d\n",kyo_texture_destination.y);
        if (kyo_up_mov_sprite4)
        {
            //printf("works\n");
            kyo_texture_destination.y -= velocity / 30;

            if (kyo_texture_destination.y <= 230) // sky boundary - capping jump
            {
                kyo_texture_destination.y = 230;
                velocity = -velocity;
            }
            if (kyo_texture_destination.y >= 300) // ground boundary
            {
                velocity=0;
                activateKyoSprite(1);
                kyo_texture_destination.y = 300;
            }
        }

        if(boundary>5)
            boundary=0;





}
