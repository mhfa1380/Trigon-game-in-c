#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>


// Copyright (C) 2020 Mohammad Hossein Fadavi Amiri - All Rights Reserved



int left=93,ups=92,right=91;//color of pen
int pos_bar=0;//barriers
int score=0;//score

//Colored pencil printing
int pen(int side_c1,int side_c2, int side_c3)
{
    printf("\033[3;40;%dm\033[%d;%dH%c\033[0m",side_c3, 24, 53, '>');
    for (int j =55; j<=100; j+=2)
    {
        printf("\033[3;40;%dm\033[%d;%dH%c\033[0m",side_c3, 24, j, '>');
    }
    printf("\033[3;40;%dm\033[%d;%dH%c\033[0m",side_c2, 22, 50, '^');
    printf("\033[3;40;%dm\033[%d;%dH%c\033[0m",side_c2, 23, 50, '^');
    printf("\033[3;40;%dm\033[%d;%dH%c\033[0m",side_c2, 24, 50, 'O');
    printf("\033[3;40;%dm\033[%d;%dH%c\033[0m",side_c1, 24, 47, '<');
    for (int j =45; j>=0; j-=2)
    {
        printf("\033[3;40;%dm\033[%d;%dH%c\033[0m",side_c1, 24, j, '<');
    }
}

//Print color moving barriers
int barrier(int num_c,int position)
{
    delay(100-3*position);
    pos_bar++;
    if (position!=0)
    {
        printf("\033[3;0;97m\033[%d;%dH%s\033[0m", position-1, 0, "                                                                                                      ");
    }
    printf("\033[3;%d;97m\033[%d;%dH%s\033[0m",num_c, position, 0, "                                                                                                      ");

}

//Increase or decrease the speed of the game
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

//Check the key entered on the keyboard
void input()
{
    //Runs when a keyboard button is pressed
    if(_kbhit())
    {
        if (_getch() == 32)
        {
            //Change the color of the pencil
            int em=left;
            left=right;
            right=ups;
            ups=em;
            pen(left,ups,right);
        }
    }
}

int main()
{
    //Clear the screen.
    //To print in color on the console, this line must be called once At First.
    system("@cls||clear");//
    srand(time(0));//rndom number for barriers color
    int col_rnd = (rand() % 3)+101;
    pen(left,ups,right);

    while (1)
    {
        input();

        if (pos_bar==23)//if barriers position == Pencil tip
        {
            if (col_rnd == ups+10)//if barriers color == Pencil tip color - win
            {
                score++;
                printf("\033[3;0;97m\033[%d;%dH%s%d\033[0m", 27, 10, "Score : ", score);
                printf("\033[3;0;97m\033[%d;%dH%s\033[0m", pos_bar-1, 0, "                                                                                                      ");
                pos_bar=0;
                col_rnd = (rand() % 3)+101;
                pen(left,ups,right);
            }
            else//if barriers color != Pencil tip color - lose
            {
                system("@cls||clear");
                printf("\n\n You Lose !\n\n\n\n Play Again? (N to exit. or press any key to continue)\t");

                if (tolower(_getch())=='n')
                {
                    system("@cls||clear");
                    printf("\n\n Bye Bye !");
                    break;
                }
                system("@cls||clear");
                score=0;
                pos_bar=0;
                col_rnd = (rand() % 3)+101;
                pen(left,ups,right);
            }
        }
        barrier(col_rnd,pos_bar);
    }
    //Stay on the screen until I press a button
    _getch();


    return 0;
}
