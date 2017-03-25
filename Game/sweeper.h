
#include <stdio.h>
#define MAX 32
typedef struct
{
    int mine;
    int open ;
    int banned;
    int question;
    int flag;
    int minesArround;
    int mineExplode;
} cell;/*the Grid of the game consists of cells each one contains certain information expressed by a group of variables
mine    : if this contain a mine it takes the value 1 and else 0
open    :the cell is opened or not
Banned  :we surrounded the grid with 2 extra rows and columns as not to exceed the limits of the grid so banned means it is a padding
question:if the user placed a question
flag    :if the user placed a flag
minesarround :the number of mines surrounding the cell
mineExplode : if the mine is opened and exploded or not */
void welcome (void);
/*A function that greets the user*/
void menu(void);
/*A function that prints the available choices for the user in the main menu*/
int initialize (cell arr[MAX][MAX],int height,int width);
/*Used to initialize the value of the components of each cell while starting a new game*/
void draw (cell arr[MAX][MAX],int height,int width);
/*draws the game grid*/
void clear(void);
/*clears the command prompt*/
void checkmove(cell arr[MAX][MAX],int height,int width);
/*checks the validity of the user's attempted move and carry it out if possible*/
void save(cell arr[MAX][MAX],int height,int width,char* name);
/*saving the .txt file*/
void saveAttrib(cell arr[MAX][MAX],int height,int width, char* name);
/*saving the .csv file*/
void load(cell arr[MAX][MAX], char* name);
/*loading a previously existing game*/
int ifWin(cell arr[MAX][MAX],int height,int width,int minesNumber);/*the function checks if the user won it returns 1 otherwise it returns 0*/
void win(cell grid[MAX][MAX],int height,int width);/*clears the screen and view the score of the user after taking the name*/
int ifLose(cell arr[MAX][MAX],int height,int width);/*Checks if the user lost if yes it returns 1 otherwise it returns 0*/
void lose(cell grid[MAX][MAX],int height,int width);/*informs the user that (s)he lost*/
void firstMove(cell arr[MAX][MAX],int height,int width);
/*users first move*/
void openCell(cell arr[MAX][MAX],int height,int width,int x,int y);
/*it opens a certain cell and  if it has no mines around it it opens the cells surrounding it using recursion*/
void flagOpen(cell arr[MAX][MAX],int height,int width,int x,int y);
/*when the user open an opened cell it and the flags surrounding the cell is equal or more than to the
number of mines around it opens all the unflagged cells around the original one*/
void UI(clock_t s, clock_t e);
/*during the game it shows the number of flags placed ,flags remaining , placed questions ,moves done and the time */
void pass(int *p,clock_t* q, int*s, int*r);
/*The purpose of this function is to pass the address of 2 variable from the main to the library*/
void logger(cell arr[MAX][MAX],int height,int width);
/*prints the off grid to help debugging*/
void scoresheetSave(int height, int width);
/*manages the score sheet*/
void scoresheetLoad(void);
/*loading the score sheet to the user*/
void scoresheetSorter(void);
/*sorts the score sheet form in a decreasing manner*/
void colorRed(void);
/*changes the color of the text into red with a white background*/
void colorBlue(void);
/*changes the color of the text into blue with a white background*/
void colorBlack(void);
/*changes the color of the text into black with a white background*/
void colorPurple(void);
/*changes the color of the text into purple with a white background*/
void colorGreen(void);
/*changes the color of the text into white with a green background*/
void colorGray(void);
/*changes the color of the text into red with a gray background*/
void colorExplode(void);
/*changes the color of the text into black with a red background*/
void *timerCheckMove(cell arr[MAX][MAX]);
/*a function pointer used in multi threading to refresh the screen each 60 sec when the
 user is idle and is used while scanning the move type from the user*/
void *timerRow(cell arr[MAX][MAX]);
/*a function pointer used in multi threading to refresh the screen each 60 sec when the
 user is idle and is used while scanning the row number from the user*/
void *timerColumn(cell arr[MAX][MAX]);
/*a function pointer used in multi threading to refresh the screen each 60 sec when the
user is idle and is used while scanning the column number from the user*/
int saveChecker(char* name);
/*checks the save directory for the given name*/
int loadChecker(char* name);
/*checks the directory for the files*/
void clearScores();
/*clears the score sheet*/
char charScanner(int modeOfScan);
/*scans characters*/
int intScanner(char modeOfScan);
/*scans an integer form the user*/
void goodBye(void); /*prints a good bye greeting to the user*/
