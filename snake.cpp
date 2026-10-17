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



    // 3. Render content to the frame buffer (y, x coordinates)
    int row = 20;
    int col = 20;

    int player_x=10;
    int player_y=10;

    int apple_x=20;
    int apple_y=20;

    int direction=2;

    int segment_x[400];
    int segment_y[400];
    segment_x[0]=player_x;
    segment_y[0]=player_y;

    int pointer=0;
    int level=0;

    char input;

    srand(time(NULL));

    mvprintw(row, col, "Hello, World from Ncurses C++!");
    nodelay(stdscr, TRUE);
    
    while (1==1)
    {   
        clear();
        input = getch();
        if(input=='w'){
            direction=1;
        }
        if(input=='a'){
            direction=4;
        }
        if(input=='s'){
            direction=3;
        }
        if(input=='d'){
            direction=2;
        }

        
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
        for(int i=0; i<=level; i++){
            if(segment_x[i] == player_x && segment_y[i] == player_y){
                for(int i=0; i<=level; i++){
                 segment_x[0]=player_x;
                segment_y[0]=player_y;
                }
                

                player_x=10;
                 player_y=10;

                 apple_x=20;
                 apple_y=20;

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




        if(player_x==apple_x && player_y==apple_y){
            level++;
            apple_x = (rand() % 20) + 1;
            apple_y = (rand() % 20) + 1;

        }

        





        for(int i=0; i<=level; i++){
            mvprintw(segment_y[i], segment_x[i], "0");
        }
        mvprintw(player_y, player_x, "@");
        mvprintw(apple_y, apple_x, "Q");
        refresh();

        napms(100);
    }
    


    // 4. Flush the changes from memory buffer to the physical terminal screen
    refresh();            

    // 5. Wait for a single keystroke before closing
    getch();              

    // 6. Deallocate memory and restore the terminal to its normal state
    endwin();             
    
    return 0;
}
