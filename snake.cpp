#include <ncurses.h> // Include the core ncurses header
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    // 1. Initialize the screen buffer and memory allocation
    initscr();            
    
    // 2. Configure terminal behavior
    cbreak();             // Line buffering disabled, pass on everything
    noecho();             // Don't echo user keyboard inputs to the screen
    curs_set(0);          // Make the mouse/text cursor invisible

    keypad(stdscr, TRUE);



    // 3. Render content to the frame buffer (y, x coordinates)


    int player_x=5;
    int player_y=5;

    int apple_x=7;
    int apple_y=7;

    int direction=2;

    int segment_x[400];
    int segment_y[400];
    segment_x[0]=player_x;
    segment_y[0]=player_y;

    int pointer=0;
    int level=0;

    int nocolision = 0;

    int input;

    int ms = 100;

    int pause = 0;

    srand(time(NULL));


    nodelay(stdscr, TRUE);
    
    while (1==1)
    {   

        //  controls
        clear();
        input = getch();
        if((input=='w' || input == 259) && direction!= 3){
            direction=1;
        }
        if((input=='a' || input == 260) && direction!= 2){
            direction=4;
        }
        if((input=='s' || input == 258) && direction!= 1){
            direction=3;
        }
        if((input=='d' || input == 261) && direction!= 4){
            direction=2;
        }


        if(input==' '){
            if(pause==0){
                pause=1;
            }
            else{
                pause=0;
            }
        }


        if(input=='1'){
            ms=100;
        }
        if(input=='2'){
            ms=200;
        }


        if(input==27){
            break;
        }

        //logic
        
        if(pause==0){


            if(direction==1){
                player_y-=1;
            }
            if(direction==2){
                player_x+=1;
            }
            if(direction==3){
                player_y+=1;
            }
            if(direction==4){
                player_x-=1;
            }



            if(player_x>19){
                player_x=1;
            }
            if(player_y>10){
                player_y=1;
            }
            if(player_x<1){
                player_x=19;
            }
            if(player_y<1){
                player_y=10;
            }




            for(int i=0; i<=level; i++){
                if(segment_x[i] == player_x && segment_y[i] == player_y){
                    for(int i=0; i<=level; i++){
                    segment_x[0]=player_x;
                    segment_y[0]=player_y;
                    }
                    

                    player_x=5;
                    player_y=5;

                    apple_x=7;
                    apple_y=7;

                    direction=2;

                    segment_x[400];
                    segment_y[400];
                    

                    pointer=0;
                    level=0;
                    
                    break;
                }
            }
            
            segment_y[pointer]=player_y; segment_x[pointer]=player_x;
            pointer++;
            if(pointer>level){
                pointer=0;
            }

            


            nocolision=0;
            if(player_x==apple_x && player_y==apple_y){
                while (nocolision==0)
                {
                    apple_x = (rand() % 19) + 1;
                    apple_y = (rand() % 10) + 1;

                    if(apple_x != player_x && apple_y != player_y){
                        for(int i=0; i <=level; i++){
                            if(apple_x != segment_x[i] && apple_y != segment_y[i]){
                                nocolision=1;
                                break;
                            }
                        }
                    }
                    
                }
                
                
                level++;
                segment_x[level]=999;  // offscreen
            }



        }
        
        //          RENDER


        for(int x=0; x<=20;x++){
            mvprintw(0, x, "-");
            mvprintw(11, x, "-");
        }
        for(int y=0; y<=11;y++){
            mvprintw(y, 0, "|");
            mvprintw(y, 20, "|");
        }



        for(int i=0; i<=level; i++){
            mvprintw(segment_y[i], segment_x[i], "0");
        }
        mvprintw(player_y, player_x, "@");
        mvprintw(apple_y, apple_x, "Q");
        refresh();

        napms(ms);
    }
    


    // 4. Flush the changes from memory buffer to the physical terminal screen
    refresh();            

    // 5. Wait for a single keystroke before closing
    getch();              

    // 6. Deallocate memory and restore the terminal to its normal state
    endwin();             
    
    return 0;
}
