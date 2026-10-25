#include <ncurses.h> // Include the core ncurses header
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void render(int segment_y[], int segment_x[], int player_y, int player_x, int apple_y, int apple_x, int level){
    for(int x=0; x<=20;x++){
        mvaddch(0, x, ACS_HLINE);
        mvaddch(11, x, ACS_HLINE);
    }
    for(int y=0; y<=11;y++){
        mvaddch(y, 0, ACS_VLINE);
        mvaddch(y, 20, ACS_VLINE);
    }
    mvaddch(0,0, ACS_ULCORNER);
    mvaddch(11,0, ACS_LLCORNER);
    mvaddch(11,20, ACS_LRCORNER);
    mvaddch(0,20, ACS_URCORNER);



    for(int i=0; i<=level; i++){
        mvaddch(segment_y[i], segment_x[i], '0');
    }
    mvaddch(player_y, player_x, '@');
    mvaddch(apple_y, apple_x, 'a');

    mvprintw(12, 10, "%d",level);
}



int main() {
    // 1. Initialize the screen buffer and memory allocation
    initscr();            
    
    // 2. Configure terminal behavior
    cbreak();             // Line buffering disabled, pass on everything
    noecho();             // Don't echo user keyboard inputs to the screen
    curs_set(0);          // Make the mouse/text cursor invisible

    keypad(stdscr, TRUE);



    


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

    int personal_best=0;


    srand(time(NULL));







    
for(int i=10;i>=0;i--){
    clear();
    mvprintw(2-i,2,"                  _        ");
    mvprintw(3-i,2,"  ___ _ __   __ _| | _____ ");
    mvprintw(4-i,2," / __| '_ \\ / _` | |/ / _ \\");
    mvprintw(5-i,2," \\__ \\ | | | (_| |   <  __/");
    mvprintw(6-i,2," |___/_| |_|\\__,_|_|\\_\\___|");
    
    refresh();
    napms(100);
}
for(int i=-20;i<=0;i++){
    clear();
    mvprintw(2,2,"                  _        ");
    mvprintw(3,2,"  ___ _ __   __ _| | _____ ");
    mvprintw(4,2," / __| '_ \\ / _` | |/ / _ \\");
    mvprintw(5,2," \\__ \\ | | | (_| |   <  __/");
    mvprintw(6,2," |___/_| |_|\\__,_|_|\\_\\___|");
    mvprintw(7,2+i,"Press");
    mvprintw(7,8+i,"any");
    mvprintw(7,12+i,"key");
    mvprintw(7,16+i,"to");
    mvprintw(7,19+i,"start");
    refresh();
    napms(60);
}
   
    getch();


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
                    
                    
                    
                    clear();
                    render(segment_y, segment_x, player_y, player_x, apple_y, apple_x, level);

                    for(int i=0;i<=6; i++){
                        render(segment_y, segment_x, player_y, player_x, apple_y, apple_x, level);
                        mvprintw(11-i, 0, "~~~~~~~~~~~~~~~~~~~~~");
                        mvprintw(0+i, 0, "~~~~~~~~~~~~~~~~~~~~~");
                        refresh();
                        napms(100);
                    }
                    for(int i=0;i<=6; i++){
                        render(segment_y, segment_x, player_y, player_x, apple_y, apple_x, level);
                        mvprintw(5-i, 0, "                     ");
                        mvprintw(6+i, 0, "                     ");
                        refresh();
                        napms(100);
                    }
                    
                        
                    
                    
                    
                    
                    for(int i=0; i<=level; i++){
                    segment_x[i]=0;
                    segment_y[i]=0;
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

                    nocolision=1;
                    if(apple_x == player_x && apple_y == player_y){
                        nocolision=0;
                    }
                    for(int i=0; i <=level; i++){
                        if(apple_x == segment_x[i] && apple_y == segment_y[i]){
                            nocolision=0;
                            break;
                        }
                    }
                }

                level++;
                segment_x[level]=999;  // offscreen
            }

            if(level>personal_best){
                personal_best=level;
            }

        }
        
        //          RENDER


        render(segment_y, segment_x, player_y, player_x, apple_y, apple_x, level);

        if(pause==1){
            for(int i=0;i<=10;i++){
                clear();
                mvprintw((-8)+i, 0, "                             _ ");
                mvprintw((-7)+i, 0, "  _ __  __ _ _  _ ___ ___ __| |");
                mvprintw((-6)+i, 0, " | '_ \\/ _` | || (_-</ -_) _` |");
                mvprintw((-5)+i, 0, " | .__/\\__,_|\\_,_/__/\\___\\__,_|");
                mvprintw((-4)+i, 0, " |_|                           ");
                mvprintw((-3)+i, 0, "Personal best - %d", personal_best);
                refresh();
                napms(50);
            }
            
            while (pause==1)
            {
                input=getch();
                if(input==' '){
                    pause=0;
                }
            }

            for(int i=0;i<=10;i++){
                clear();
                mvprintw(2-i, 0, "                             _ ");
                mvprintw(3-i, 0, "  _ __  __ _ _  _ ___ ___ __| |");
                mvprintw(4-i, 0, " | '_ \\/ _` | || (_-</ -_) _` |");
                mvprintw(5-i, 0, " | .__/\\__,_|\\_,_/__/\\___\\__,_|");
                mvprintw(6-i, 0, " |_|                           ");
                mvprintw(7+i, 0, "Personal best - %d", personal_best);
                refresh();
                napms(50);
            }
            

        }


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

