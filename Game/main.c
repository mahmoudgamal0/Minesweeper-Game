#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include "sweeper.h"
#define MAX 32
cell grid [MAX][MAX];
int main()
{
    int height, width;
    system("COLOR F1");
    clock_t start_t, end_t;
    int exitCount = 0;
    /*Passing the addresses to sweepers.c*/
    pass(&exitCount,&start_t,&height,&width);
    /*Greeting the user*/
    welcome();
    /*Generating the random range using time function*/
    srand(time(NULL));
    /*Initializing menu*/
    menu();
    /*Scanning the user's choice*/
    printf("\t\t\t\t\tMake your choice :");
    int usersChoice ;
    char enter;
    usersChoice = intScanner('u');
    /*Do-while loop of the game*/
    do
    {
        /*The game will continue unless the user requests to exit*/
        if (exitCount == 1)
        {
            clear();
            menu();
            printf("\t\t\t\t\tMake your choice :");
            usersChoice = intScanner('u');
            exitCount = 0;
        }
        /*New game or load game directs here*/
        if (usersChoice==1 || usersChoice == 2)
        {
            /*Variable to control the choice between new game or load game*/
            int loadSwitch;
            if(usersChoice == 2)
            {
                loadSwitch = 1;
            }
            else
            {
                loadSwitch = 0;
            }
            exitCount=0;
            int minesNumber;
            /*Starting a new game*/
            if(loadSwitch == 0)
            {
                /*Choosing the dimensions of the grid*/
                printf("\t\t\t\t\t**Enter height and width**\n");
                printf("\t\t\t\t\tPlease enter a height between 2 and 30 :");
                while((scanf(" %d",&height) != 1)||(height > 30 || height < 2)||getchar() != '\n' )
                {
                    printf("\t\t\t\t\tPlease enter a height between 2 and 30 :");
                    while(getchar() != '\n');
                }
                fflush(stdin);
                printf("\t\t\t\t\tPlease enter a width  between 2 and 30 :");
                while((scanf(" %d",&width) != 1)||(width > 30 || width < 2)||getchar() != '\n')
                {
                    printf("\t\t\t\t\tPlease enter a width  between 2 and 30 :");
                    while(getchar() != '\n');
                }
                fflush(stdin);
                minesNumber = 1 + (height*width)/10; /*Generating mines number*/
                initialize(grid,height,width); /*Initializing the cells of the grid with its values*/
                clear(); /*clearing the command prompt*/
                draw(grid,height,width);/*drawing the grid*/
                firstMove(grid,height,width);/*indicates the first move*/
                logger(grid,height,width);/*logger which maps the mines to help debugging*/
                start_t = clock() / CLOCKS_PER_SEC; /*calculating the starting time of the game*/
            }
            else
            {
                /*Loading a previous game*/
                int *heightForLoad, *widthForLoad;
                char* name;
                name = malloc(100);
                loadSwitch = 1;
                do
                {
                    clear();
                    printf("\t\t\t\t\tEnter the save name for your game\n"); /*Getting the name of the saved game*/
                    printf("\t\t\t\t\t(@ to exit): ");
                    do
                    {
                        if(strlen(name)>20)
                        {
                            printf("\t\t\t\t\tVery long name. Try again: ");
                        }
                        else if(!strcmp(name,"") || name[0] == ' ')
                        {
                            printf("\t\t\t\t\tInvalid input! Try again: ");
                        }
                        gets(name);
                    }while(strlen(name)>20 || !strcmp(name,"") || name[0] == ' ');
                    if(*name == '@' && strlen(name) == 1)
                    {
                        exitCount = 1;
                        loadSwitch = 0;
                        break;
                    }
                }while(loadChecker(name));
                if(loadSwitch == 1) /*if the file name is in directory*/
                {
                    load(grid,name); /*loads the game*/
                    logger(grid,height,width);
                    free(name);
                    minesNumber = 1 + (height*width)/10;
                    start_t = clock() / CLOCKS_PER_SEC; /*starts time*/
                }
            }

            while (exitCount==0) /*inner game loop which will continue till the user requests to exit*/
            {
                if(ifLose(grid,height,width)) /*check if the user have lost the game*/
                {
                    lose(grid,height,width);
                    usersChoice = intScanner('u');
                    break;
                }
                else if (ifWin(grid,height,width,minesNumber)) /*checks if the user have won the game*/
                {
                    win(grid,height,width);
                    usersChoice = intScanner('u');
                    break;
                }
                clear(); /*continuing the game if the user did not lose or win*/
                draw(grid,height,width);
                end_t = clock() / CLOCKS_PER_SEC;
                UI(start_t, end_t); /*user interface function to show the moves, flags, etc.*/
                checkmove(grid,height,width);
                logger(grid,height,width);
                if (exitCount ==1) /*exit request*/
                {
                    break;
                }
            }
        }
        else if (usersChoice == 3) /*loading the score sheet*/
        {
            char loadChoice;
            printf("\n");
            printf("\t\t\t\t\tL: Load C: Clear  :");
            loadChoice = charScanner(1);
            if(loadChoice == 'L' || loadChoice == 'l') /*Load the scores*/
            {
                scoresheetLoad();
            }
            else if(loadChoice == 'C' || loadChoice == 'c') /*clear the score sheet*/
            {
                clearScores();
            }
            else
            {
                printf("\t\t\t\t\tInvalid input!\n");
            }
            printf("\n\t\t\t\t\tPress enter to continue.");
            enter = charScanner(2);
            enter = '0';
            clear();
            menu();
            printf("\t\t\t\t\tMake your choice :");
            usersChoice = intScanner('u');
        }
        else if (usersChoice==4) /*in-game tutorial*/
        {
            clear();
            printf("Welcome to the tutorial :D\n\n\
Here are the symbols you will tackle in the game:\n\n 'X' means unopened box \n\n");
            printf(" '1' or '2' up till '8' indicates the number of mines surrounding this box\n\n\
 ' ' means the at there are no mines in the perimeter of this box\n\n");
            printf(" '*' means unexploded flagged mine\n\n '!' means an exploded mine\n\n\
 'M' means missed mine\n\n 'F' means flag\n\n\ '?' means suspicious\n\n '-' means missed flag\n\nHave Fun :D ;)\n\n");
            printf("\t\t\t\t\tPress enter to continue.");
            enter = charScanner(2);
            enter = '0';
            clear();
            menu();
            printf("\t\t\t\t\tMake your choice :");
            usersChoice = intScanner('u');
        }
        else if (usersChoice==5)/*exiting the game*/
        {
            printf("\t\t\t\t\tDo you really want to exit?\n\t\t\t\t\tY : yes\tN : no\n\t\t\t\t\tYour choice :");
            char exitChoice;
            exitChoice = charScanner(1);
            if(exitChoice == 'Y' || exitChoice == 'y')
            {
                goodBye();
                return 0;
            }
            else if (exitChoice == 'N' || exitChoice == 'n')
            {
                clear();
                menu();
                printf("\t\t\t\t\tMake your choice :");
                usersChoice = intScanner('u');
            }
            else
            {
                clear();
                printf("\t\t\t\t\tYour input is not valid \n\t\t\t\t\tRetry\n");
                menu();
                printf("\t\t\t\t\tMake your choice :");
                usersChoice = intScanner('u');
            }

        }
        else
        {
            printf("\t\t\t\t\tYour input is not valid please retry:");
            usersChoice = intScanner('u');
        }
    }
    while (1);
}
