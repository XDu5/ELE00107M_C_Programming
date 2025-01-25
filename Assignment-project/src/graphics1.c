#include <stdio.h>
#include <math.h>
#include <graphics_lib.h>

/* Declare two variables for the x and y positions */
int x_position, y_position, x_position_2, y_position_2;
int initial_pos_x, initial_pos_y, initial_pos_x_2, initial_pos_y_2;//coordinate of the javelin tip when it was thrown
int o_pos_x_2, o_pos_y_2, pos_x_2, pos_y_2;
int o_pos_x, o_pos_y, pos_x, pos_y, Amount_of_change_y, Amount_of_change_x;//Initial coordinate of the javelin tip
int javelin_long = 84.85;// the length of the javelin
double radians = (45*M_PI)/180;
double t, vel_x, vel_y, gravity = 9.81;//javelin
char user_control, user_2_control;//user press keyboard value
int score, best_score = 0;;
int sum_of_score_player_1 = 0, sum_of_score_player_2 = 0;
int player_2_start;

int scores[10] = {10, 20, 30, 40, 50, 40, 30 ,20, 10, 40};
char scores_label[3], player_1_scores_label[3], player_2_scores_label[3], player_1_sum_of_scoures_label[3], player_2_sum_of_scoures_label[3];
char player_scores_label[3], player_BestScores_label[3];


//The main program
int main(void)
{

	/*Open the start menu */
	user_menu();

while(1)
{
	user_control = getch();

	switch(user_control)
	{
        case '1':
            closegraph();
            /*start single-player mode*/
            play_SinglePlayer_mode();
            break;
        case '2':
            closegraph();
            /*start multi-player mode*/
            play_MultiPlayer_mode();
            break;
        case '3':
            closegraph();
            /*open the instruction*/
            Instruction();
            break;
        case 'q':
            initwindow(640, 480);
            /*back to the start menu*/
            user_menu();
	}
}

    return 0;
}


/**********************************************************************************/
/* Below are the functions declaration*/

/* the game start menu*/
void user_menu(void)
{
    initwindow(640, 580);
    initfont();
    setcolor(GREEN);
    outtextxy(200, 150, "[1] Play game --> single-player mode");
    outtextxy(200, 250, "[2] Play game --> multi-player mode");
    outtextxy(200, 350, "[3] Instructions for new players");
    outtextxy(200, 450, "[4] Exit game");
    update_display();
}

/*display the instruction of the game */
void Instruction(void)
{
    initwindow(840, 580);
    initfont();
    setcolor(GREEN);
    outtextxy(200, 150, "single-player mode: Press 'd' to move the stick person");
     outtextxy(200,170, "Press 'w' to throw the javelin");
     outtextxy(200,190, "Press up and down keys to adjust the angle of javelin");
     outtextxy(200,210, "After throwing the javelin you will get a score, you have 6 times attempt");
    outtextxy(200, 250, "multi-player mode: press 'd' to move the stick person 1");
     outtextxy(200, 270, "press 'w' to throw the javelin 1");
     outtextxy(200, 290, "press 'l' to move the stick person 2");
     outtextxy(200, 310, "press 'i' to throw the javelin 2");
     outtextxy(200, 330, "Press up and down keys to adjust the angle of javelin 1&2");
     outtextxy(200, 350, "The program will calculate the sum of the score of your all attempt");
     outtextxy(200, 370, "And determine who is the winner");
     outtextxy(200, 400, "Press 'q' to return the menu");
     if (user_control == 'q')
     {
         closegraph();
     }
    update_display();
}

/* Play the single-player mode*/
void play_SinglePlayer_mode(void)
{
    initwindow(1280, 960);
    /* Set up some coordinates */
	x_position = 100;
	y_position = 340;

   /* draw the person*/
    stick_person();
   /* draw the ground*/
    draw_ground();
    draw_target();//draw and display the target
    update_display();

    user_control = ' ';
    user_2_control = ' ';

    while(1)
    {

        user_control = getch();

        /*control to move the stick person*/
        control_stick_person(user_control);
        /* set the angle of the javelin*/
        set_angle(user_control);
        /* drawing the javelin*/
        javelin();
        /* control to throw the javelin*/
        throw_javelin(user_control);

        game_over();
    }
}

void play_MultiPlayer_mode(void)
{
    initwindow(1280, 960);
    /* Set up some coordinates */
    /* the first player*/
	x_position = 100;
	y_position = 340;
	/* the second player*/
	x_position_2 = 100;
	y_position_2 = 740;

    stick_person();//draw the person
    stick_person_2();

    draw_ground_multiPlayer_mode();
    draw_target_multiPlayer_mode();//draw and display the target

    update_display();

    user_control = ' ';
    user_2_control = ' ';

    while(1)
    {
        user_control = getch();

        /*control to move the stick person*/
        control_stick_person(user_control);
        /* set the angle of the javelin*/
        set_angle(user_control);
        /* drawing the javelin*/
        javelin();
        /* player 1 to control to throw the javelin*/
        throw_javelin_person_1(user_control);
        game_over_Player_1();

        /* Determine if the player 2 start the game*/
        if(player_2_start == 1)
        {
            user_2_control = getch();
            /*control to move the stick person*/
            control_stick_person_2(user_2_control);
            /* set the angle of the javelin*/
            set_angle(user_2_control);
              /* drawing the javelin*/
            javelin_2();
            /* player 2 to control to throw the javelin*/
            throw_javelin_person_2(user_2_control);
            game_over_Player_2();
        }
        else
        {
            user_2_control = ' ';
        }

        /* exit th game*/
        if(user_2_control == 'q' || user_control == 'q')
        {
            closegraph();
        }

    }
}


//draw and display the target
void draw_target(void)
{
    int i;
    int target_position_x = 600;
    int target_position_y = 200;

    initfont();
    /* display the text*/
    outtextxy(200, 100, "Best Score: " );
    outtextxy(200, 130, "Current Score: " );

    for(i = 0; i< 10; i++)
    {
        setcolor(BLUE);
        /* Creating scoring areas*/
        line(target_position_x, target_position_y, target_position_x, target_position_y + 320, 2);

        /* print the score*/
        sprintf(scores_label, "%d", scores[i]);
        setcolor(RED);
        outtextxy(target_position_x, target_position_y, scores_label);
        /* the red line*/
        target_position_x = target_position_x + 50;
    }
}

void draw_target_multiPlayer_mode(void)
{
    int i;
    int target_position_x = 600;
    int target_position_y = 200;

    initfont();
    outtextxy(200, 100, "player 1 scores: " );
    outtextxy(200, 130, "player 2 scores: " );

    for(i = 0; i< 10; i++)
    {
        setcolor(BLUE);
 /* Creating scoring areas*/
        line(target_position_x, target_position_y, target_position_x, target_position_y + 640, 2);
 /* print the score*/
        sprintf(scores_label, "%d", scores[i]);
        setcolor(RED);
        outtextxy(target_position_x, target_position_y, scores_label);
  /* the red line*/
        target_position_x = target_position_x + 50;
    }
}

//Draw the ground
void draw_ground(void)
{
    setcolor(YELLOW);
    line(80, 520, 1000, 520, 2);//draw the bottom ground
    line(200, 200, 1120, 200, 2);//draw the top ground
    setcolor(RED);
    line(500, 200, 500, 520, 5);//draw a boundary
}

/* Drawing ground, multi-player mode*/
void draw_ground_multiPlayer_mode(void)
{
    setcolor(YELLOW);
    line(80, 520, 1000, 520, 2);//draw the bottom ground
    line(200, 200, 1120, 200, 2);//draw the top ground
    line(80, 840, 1000, 840, 2);
    setcolor(RED);
    line(500, 200, 500, 840, 5);//draw a boundary
}


/*draw and drive the stick person*/
void stick_person(void)
{
/* draw a circle on the screen buffer
 at x_position, y_position
 with radius 10 and line thickness 2 */
    setcolor(YELLOW);
    filled_circle(x_position, y_position, 10, YELLOW);//stick person's head
    //body of the stick person
    line(x_position, y_position + 10, x_position, y_position + 60, 2);
    line(x_position - 20, y_position + 20, x_position + 20, y_position + 20, 2);
    line(x_position, y_position + 60, x_position -20, y_position + 80, 2);
    line(x_position, y_position + 60, x_position + 20, y_position + 80, 2);
    javelin();
    update_display();
}
/*draw and drive the stick person, player 2*/
void stick_person_2(void)
{
    setcolor(RED);
    filled_circle(x_position_2, y_position_2, 10, YELLOW);//stick person's head
    //body of the stick person 2
    line(x_position_2, y_position_2 + 10, x_position_2, y_position_2 + 60, 2);
    line(x_position_2 - 20, y_position_2 + 20, x_position_2 + 20, y_position_2 + 20, 2);
    line(x_position_2, y_position_2 + 60, x_position_2 -20, y_position_2 + 80, 2);
    line(x_position_2, y_position_2 + 60, x_position_2 + 20, y_position_2 + 80, 2);
    javelin_2();
    update_display();
}

/* control to move the stick person*/
void control_stick_person(char user_control)
{
    /* clear the previous frame */
    clear_person_1_pre_frame();
    /* player 1 move forward*/
    if(user_control == 'd'){
            x_position = x_position + 3;
            /* Increase the speed of the stick person   */
            if(x_position >200 && x_position < 300)
            {
                x_position = x_position + 5;
            }
            /* Increase the speed of the stick person   */
               if(x_position >300)
            {
                x_position = x_position + 8;
            }
    }
    else
    if(user_control == 'a'){
        x_position = x_position - 3;
    }
/* draw a circle on the screen buffer
 at x_position, y_position
 with radius 10 and line thickness 2 */
    setcolor(YELLOW);
    filled_circle(x_position, y_position, 10, YELLOW);//stick person's head
    //body of the stick person
    line(x_position, y_position + 10, x_position, y_position + 60, 2);
    line(x_position - 20, y_position + 20, x_position + 20, y_position + 20, 2);
    line(x_position, y_position + 60, x_position -20, y_position + 80, 2);
    line(x_position, y_position + 60, x_position + 20, y_position + 80, 2);
    //javelin();
    update_display();
}

/* control to move the stick person, player 2*/
void control_stick_person_2(char user_2_control)
{
    /* clear the previous frame */
    clear_person_2_pre_frame();
    /* player 2 move forward*/
    if(user_2_control == 'l'){
        x_position_2 = x_position_2 + 3;
        /* Increase the speed of the stick person   */
        if(x_position_2 >200 && x_position_2 < 300)
        {
            x_position_2 = x_position_2 + 5;
        }
        /* Increase the speed of the stick person   */
       if(x_position_2 >300)
        {
            x_position_2 = x_position_2 + 8;
        }
    }
    else
    if(user_2_control == 'j'){
        x_position_2 = x_position_2 - 3;
    }
/* draw a circle on the screen buffer
 at x_position_2, y_position_2
 with radius 10 and line thickness 2 */
    setcolor(RED);
    filled_circle(x_position_2, y_position_2, 10, RED);//stick person's head
    //body of the stick person
    line(x_position_2, y_position_2 + 10, x_position_2, y_position_2 + 60, 2);
    line(x_position_2 - 20, y_position_2 + 20, x_position_2 + 20, y_position_2 + 20, 2);
    line(x_position_2, y_position_2 + 60, x_position_2 -20, y_position_2 + 80, 2);
    line(x_position_2, y_position_2 + 60, x_position_2 + 20, y_position_2 + 80, 2);
    //javelin();
    update_display();
}

/* clear the stick person 1 previous frame*/
void clear_person_1_pre_frame(void)
{
    setcolor(BLACK);
    filled_circle(x_position, y_position, 10, BLACK);
    line(x_position,y_position + 10, x_position, y_position + 60, 2);
    line(x_position - 20, y_position + 20, x_position + 20, y_position + 20, 2);
    line(x_position, y_position + 60, x_position - 20, y_position + 80, 2);
    line(x_position, y_position + 60, x_position + 20, y_position + 80, 2);
    javelin_clear();
    update_display();
}
/* clear the stick person 2 previous frame*/
void clear_person_2_pre_frame(void)
{
    setcolor(BLACK);
    filled_circle(x_position_2, y_position_2, 10, BLACK);
    line(x_position_2, y_position_2 + 10, x_position_2, y_position_2 + 60, 2);
    line(x_position_2 - 20, y_position_2 + 20, x_position_2 + 20, y_position_2 + 20, 2);
    line(x_position_2, y_position_2 + 60, x_position_2 - 20, y_position_2 + 80, 2);
    line(x_position_2, y_position_2 + 60, x_position_2 + 20, y_position_2 + 80, 2);
    javelin_clear_2();
    update_display();
}

int long_x, long_y;//The base and height of a triangle
//draw the javelin
//long of the javelin = 84.85
void javelin(void)
{
    o_pos_x = x_position + 40 ;
    o_pos_y = y_position - 40 ;
    pos_x = o_pos_x + Amount_of_change_x; //initial x = 140
    pos_y = o_pos_y + Amount_of_change_y; //initial y = 380
    setcolor(GREEN);
    line(pos_x, pos_y, o_pos_x - 60, o_pos_y + 60, 2);
    update_display();
}
void javelin_2(void)
{
    o_pos_x_2 = x_position_2 + 40 ;
    o_pos_y_2 = y_position_2 - 40 ;
    pos_x_2 = x_position_2 + 40 ; //initial x = 140
    pos_y_2 = y_position_2 - 40 ; //initial y = 380
    setcolor(GREEN);
    line(pos_x_2, pos_y_2, o_pos_x_2 - 60, o_pos_y_2 + 60, 2);
    update_display();
}

/*clear the previous frame of the javelin 1*/
void javelin_clear(void)
{
    o_pos_x = x_position + 40 ;
    o_pos_y = y_position - 40 ;
    pos_x = x_position + 40 + Amount_of_change_x;
    pos_y = y_position - 40 + Amount_of_change_y;
    setcolor(BLACK);
    line(pos_x, pos_y, o_pos_x - 60, o_pos_y + 60, 2);
    update_display();
}

/*clear the previous frame of the javelin 2*/
void javelin_clear_2(void)
{
    o_pos_x_2 = x_position_2 + 40 ;
    o_pos_y_2 = y_position_2 - 40 ;
    pos_x_2 = x_position_2 + 40 ;
    pos_y_2 = y_position_2 - 40 ;
    setcolor(BLACK);
    line(pos_x_2, pos_y_2, o_pos_x_2 - 60, o_pos_y_2 + 60, 2);
    update_display();
}


//user control the angle
//angle degree is in radians
void set_angle(char user_control)
{
    if(user_control == 72){
        javelin_clear();
        radians = radians + M_PI/180;
        long_x = javelin_long * cos(radians);
        long_y = javelin_long * sin(radians);
        if(radians < 1.57 && radians > 0)
        {
            Amount_of_change_y = - long_y ;
            Amount_of_change_x = - long_x;
        }
        else
        {
            Amount_of_change_y = 0 ;
            Amount_of_change_x = 0;
        }

    }
    else
    if(user_control == 80){
        javelin_clear();
        radians = radians - M_PI/180;
        long_x = javelin_long * cos(radians);
        long_y = javelin_long * sin(radians);
        if(radians < 1.57 && radians > 0)
        {
            Amount_of_change_y = long_y;
            Amount_of_change_x = long_x;
        }
        else
        {
            Amount_of_change_y = 0 ;
            Amount_of_change_x = 0;
        }
    }
}
void set_angle_2(char user_2_control)
{
    if(user_2_control == 72){
        javelin_clear_2();
        radians = radians + M_PI/180;
        long_x = javelin_long * cos(radians);
        long_y = javelin_long * sin(radians);
        if(radians < 1.57 && radians > 0)
        {
            Amount_of_change_y = - long_y ;
            Amount_of_change_x = - long_x;
        }
        else
        {
            Amount_of_change_y = 0 ;
            Amount_of_change_x = 0;
        }

    }
    else
    if(user_2_control == 80){
        javelin_clear_2();
        radians = radians - M_PI/180;
        long_x = javelin_long * cos(radians);
        long_y = javelin_long * sin(radians);
        if(radians < 1.57 && radians > 0)
        {
            Amount_of_change_y = long_y;
            Amount_of_change_x = long_x;
        }
        else
        {
            Amount_of_change_y = 0 ;
            Amount_of_change_x = 0;
        }
    }
}

int i = 0;
/* calculate the score*/
void calculate_score(void)
{
        int gap = 30;
        if(pos_x < 600)
        {
            score = 0;
            printf(" Your score is: %d\n" ,score);
        }
        if(pos_x >= 600 && pos_x < 650)
        {
            score = 10;
            printf(" Your score is: %d\n" ,score);
            if(best_score < score)
            {
                best_score = score;

            }
        }
        else
        if(pos_x >=650 && pos_x < 700)
        {
            score = 20;
            printf(" Your score is: %d\n" ,score);
            if(best_score < score)
            {
                best_score = score;
            }
        }
        else
        if(pos_x >= 700 && pos_x < 750)
        {
            score = 30;
            printf(" Your score is: %d\n" ,score);
            if(best_score < score)
            {
                best_score = score;
            }
        }
        else
        if(pos_x >= 750 && pos_x < 800)
        {
            score = 40;
            printf(" Your score is: %d\n" ,score);
            if(best_score < score)
            {
                best_score = score;
            }
        }
        else
        if(pos_x >= 800 && pos_x < 850)
        {
            score = 50;
            printf(" Your score is: %d\n" ,score);
            if(best_score < score)
            {
                best_score = score;
            }
        }
        else
            if(pos_x >= 850 && pos_x < 900)
            {
                score = 40;
                printf(" Your score is: %d\n" ,score);
                if(best_score < score)
                {
                    best_score = score;
                }
            }
        else
            if(pos_x >= 900 && pos_x < 950)
            {
                score = 30;
                printf(" Your score is: %d\n" ,score);
                if(best_score < score)
                {
                    best_score = score;
                }
            }
        else
            if(pos_x >= 950 && pos_x < 1000)
            {
                score = 20;
                printf(" Your score is: %d\n" ,score);
                if(best_score < score)
                {
                    best_score = score;
                }
            }
        else
            if(pos_x >=1000 && pos_x < 1500)
            {
                score = 10;
                printf(" Your score is: %d\n" ,score);
                if(best_score < score)
                {
                    best_score = score;
                }
            }
        else
            if(pos_x >=1500 && pos_x < 2000)
            {
                score = 40;
                printf(" Your score is: %d\n" ,score);
                if(best_score < score)
                {
                    best_score = score;
                }
            }

            /*print the score on the graphic window */
            /*If the player reach the maximum attempts of the game, then game over*/
            i = i + 1;
            if(i == 6){
                cleardevice();
                outtextxy(600, 300, "game over!");
                outtextxy(460, 320, "You have reached the maximum number of attempts!");
                outtextxy(460, 340, "Your best score is: ");
                outtextxy(640, 340, player_BestScores_label);
            }
            else{
                sprintf(player_scores_label, "%d", score);
                sprintf(player_BestScores_label, "%d", best_score);
                outtextxy(300 + i*gap, 130, player_scores_label);
                outtextxy(300 + i*gap, 100, player_BestScores_label);
                update_display();
            }

}

void calculate_score_Player_1(void)
{
        if(pos_x < 600)
        {
            score = 0;
        }
        if(pos_x >= 600 && pos_x < 650)
        {
            score = 10;
        }
        else
        if(pos_x >=650 && pos_x < 700)
        {
            score = 20;
        }
        else
        if(pos_x >= 700 && pos_x < 750)
        {
            score = 30;
        }
        else
        if(pos_x >= 750 && pos_x < 800)
        {
            score = 40;
        }
        else
        if(pos_x >= 800 && pos_x < 850)
        {
            score = 50;
        }
        else
            if(pos_x >= 850 && pos_x < 900)
            {
                score = 40;
            }
        else
            if(pos_x >= 900 && pos_x < 950)
            {
                score = 30;
            }
        else
            if(pos_x >= 950 && pos_x < 1000)
            {
                score = 20;
            }
        else
            if(pos_x >=1000 && pos_x < 1500)
            {
                score = 10;
            }
        else
            if(pos_x >=1500 && pos_x < 2000)
            {
                score = 40;
            }

        sum_of_score_player_1 = sum_of_score_player_1 + score;
}

void calculate_score_Player_2(void)
{
        if(pos_x_2 < 600)
        {
            score = 0;
        }
        if(pos_x_2 >= 600 && pos_x_2 < 650)
        {
            score = 10;
        }
        else
        if(pos_x_2 >=650 && pos_x_2 < 700)
        {
            score = 20;
        }
        else
        if(pos_x_2 >= 700 && pos_x_2 < 750)
        {
            score = 30;
        }
        else
        if(pos_x_2 >= 750 && pos_x_2 < 800)
        {
            score = 40;
        }
        else
        if(pos_x_2 >= 800 && pos_x_2 < 850)
        {
            score = 50;
        }
        else
            if(pos_x_2 >= 850 && pos_x_2 < 900)
            {
                score = 40;
            }
        else
            if(pos_x_2 >= 900 && pos_x_2 < 950)
            {
                score = 30;
            }
        else
            if(pos_x_2 >= 950 && pos_x_2 < 1000)
            {
                score = 20;
            }
        else
            if(pos_x_2 >=1000 && pos_x_2 < 1500)
            {
                score = 10;
            }
        else
            if(pos_x_2 >=1500 && pos_x_2 < 2000)
            {
                score = 40;
            }

        sum_of_score_player_2 = sum_of_score_player_2 + score;
}

/*print the score on the graphic window */
/*If the player reach the maximum attempts of the game, then game over*/
void print_player1_score(void)
{
    int gap_1 = 30;
    i = i + 1;
    if(i == 6)
    {
        player_2_start = 1;
        outtextxy(860, 100, "You have reached the maximum number of attempts!");
        outtextxy(860, 120, "Your best score is: ");
        outtextxy(1040, 100, player_1_sum_of_scoures_label);
        outtextxy(860, 140, "Now is the player 2 turn!");
    }
    else
    {
        sprintf(player_1_scores_label, "%d", score);
        sprintf(player_1_sum_of_scoures_label, "%d", sum_of_score_player_1);
        outtextxy(300 + i*gap_1, 100, player_1_sum_of_scoures_label);
        update_display();
    }
}
int j = 0;
void print_player2_score(void)
{
    int gap_2 = 30;
    j = j + 1;
    if(j == 6)
    {
        cleardevice();
        outtextxy(460, 100, "You have reached the maximum number of attempts!");
        outtextxy(460, 120, "Your best score is: ");
        outtextxy(640, 100, player_2_sum_of_scoures_label);

        if(sum_of_score_player_1 > sum_of_score_player_2)
        {
            outtextxy(460, 140, "The player 1 is winner!");
            outtextxy(460, 160, "press 'q' to go back the menu");
        }
        else
        if(sum_of_score_player_1 < sum_of_score_player_2)
        {
            outtextxy(460, 140, "The player 2 is winner!");
            outtextxy(460, 160, "press 'q' to go back the menu");
        }
        else
        if(sum_of_score_player_1 == sum_of_score_player_2)
        {
           outtextxy(460, 140, "Same score!");
           outtextxy(460, 160, "press 'q' to go back the menu");
        }
    }
    else
    {
        sprintf(player_2_scores_label, "%d", score);
        sprintf(player_2_sum_of_scoures_label, "%d", sum_of_score_player_2);
        outtextxy(300 + j*gap_2, 130, player_2_sum_of_scoures_label);
    }
}

/* control to throw the javelin*/
void throw_javelin(char user_control)
{
    if(user_control == 'w'){
        initial_pos_x = pos_x;
        initial_pos_y = pos_y;
        moveto(initial_pos_x, initial_pos_y);

        /* set the velocity of the javelin*/
        if(x_position > 100 && x_position < 200)
        {
              vel_x = 15;
              vel_y = 15;
        }
        else
        if(x_position > 200 && x_position < 300)
        {
             vel_x = 30;
             vel_y = 30;
        }
        else
        if(x_position > 300)
        {
             vel_x = 45;
             vel_y = 45;
        }
        /* draw the arc*/
        do
        {
            t = (pos_x - initial_pos_x) /  vel_x;
            pos_y = (int)(initial_pos_y - vel_y* t + (gravity * t * t)/2);
            lineto(pos_x, pos_y, 1);
            update_display();
            pos_x++;
        }
        while(pos_y < 420);//reach the ground
        calculate_score();

        /* wait for 1 second*/
        Sleep(1000);
        /* clear frame*/
        clear_person_1_pre_frame();
        x_position = 100;
        y_position = 340;
        stick_person();
    }
}

/* control to throw the javelin, player 1*/
void throw_javelin_person_1(char user_1_control)
{
     if(user_control == 'w'){
        initial_pos_x = pos_x;
        initial_pos_y = pos_y;
        moveto(initial_pos_x, initial_pos_y);
        /* set the velocity of the javelin*/
        if(x_position > 100 && x_position < 200)
        {
              vel_x = 15;
              vel_y = 15;
        }
        else
        if(x_position > 200 && x_position < 300)
        {
             vel_x = 30;
             vel_y = 30;
        }
        else
        if(x_position > 300)
        {
             vel_x = 45;
             vel_y = 45;
        }

        do
        {
            t = (pos_x - initial_pos_x) /  vel_x;
            pos_y = (int)(initial_pos_y - vel_y* t + (gravity * t * t)/2);
            lineto(pos_x, pos_y, 1);
            update_display();
            pos_x++;
        }
        while(pos_y < 420);//reach the ground
        calculate_score_Player_1();
        print_player1_score();

          /* wait for 1 second*/
        Sleep(1000);
        clear_person_1_pre_frame();
        x_position = 100;
        y_position = 340;
        stick_person();
    }
}

/* control to throw the javelin, player 2*/
void throw_javelin_person_2(char user_2_control)
{
    if(user_2_control == 'i'){
        initial_pos_x_2 = pos_x_2;
        initial_pos_y_2 = pos_y_2;
        moveto(initial_pos_x_2, initial_pos_y_2);
        /* set the velocity of the javelin*/
        if(x_position_2 > 100 && x_position_2 < 200)
        {
              vel_x = 15;
              vel_y = 15;
        }
        else
        if(x_position_2 > 200 && x_position_2 < 300)
        {
             vel_x = 30;
             vel_y = 30;
        }
        else
        if(x_position_2 > 300)
        {
             vel_x = 45;
             vel_y = 45;
        }

        do
        {
            t = (pos_x_2 - initial_pos_x_2) /  vel_x;
            pos_y_2 = (int)(initial_pos_y_2 - vel_y* t + (gravity * t * t)/2);
            lineto(pos_x_2, pos_y_2, 1);
            update_display();
            pos_x_2++;
        }
        while(pos_y_2 < 820);//reach the ground
        calculate_score_Player_2();
        print_player2_score();

        Sleep(1000);
        clear_person_2_pre_frame();
        x_position_2 = 100;
        y_position_2 = 740;
        stick_person_2();
    }
}

//illegal or game over
void game_over(void)
{
    initfont();
    /* If the stick person reach the red line, illegal*/
    if(x_position >= 500)
    {
        cleardevice();
        outtextxy(600, 300, "game over! Because of the illegal!");
        outtextxy(460, 320, "You are beyond the red line! Press 'q' to exist game.");
        if(user_control == 'q')
        {
            closegraph();
        }
    }
}

/*illegal or game over, in the multi-player mode*/
void game_over_Player_1(void)
{
    initfont();
      /* If the stick person 1 reach the red line, illegal*/
    if(x_position >= 500)
    {
        cleardevice();
        outtextxy(860, 100, "game over! Because of the illegal!");
        outtextxy(860, 120, "You are beyond the red line! You have no choice.");
    }
}

/*illegal or game over, in the multi-player mode*/
void game_over_Player_2(void)
{
    initfont();
      /* If the stick person 2 reach the red line, illegal*/
    if(x_position_2 >= 500)
    {
        cleardevice();
        outtextxy(860, 100, "game over! Because of the illegal!");
        outtextxy(860, 120, "You are beyond the red line! You have no choice.");
        outtextxy(860, 140, "The winner is player 1.");
    }
}


