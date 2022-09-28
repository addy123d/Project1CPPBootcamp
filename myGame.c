#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <windows.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

#pragma comment(lib, "WinMM.lib")

int cheat = 1, sound = 1, beep = 1, difficulty = 2;

// create matrix 4*4
void createMatrix(int arr[][4])
{
    int n = 15;
    int num[n], i, j;
    for (i = 0; i < 15; i++) // These 1-15 number will be in th matrix
        num[i] = i + 1;

    srand(time(NULL)); // for random number generation

    int lastIndex = n - 1, index;

    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
        {
            if (lastIndex >= 0)
            {
                index = rand() % (lastIndex + 1); // idea : performing % operation by (lastIndex+1)
                arr[i][j] = num[index];           // will give index , so put that num[index] number in matrix
                num[index] = num[lastIndex--];    // and replace last number with this indexed positioned number
            }                                     // and finally lastIndex--
        }
    arr[i - 1][j - 1] = 0; // last number is zero
}

// showing matrix
void showMatrix(int arr[][4])
{
    int i, j;
    printf("--------------------\n");
    for (i = 0; i < 4; i++)
    {
        printf("|");
        for (j = 0; j < 4; j++)
        {
            if (arr[i][j] != 0)
                printf("%2d | ", arr[i][j]);
            else
                printf("   | ");
        }
        printf("\n");
    }

    printf("--------------------\n");
}

// winning check by this function
int winner(int arr[][4])
{
    int i, j, k = 1;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++, k++)
            if (arr[i][j] != k && k != 16)
                break;
        if (j < 4)
            break;
    }

    if (j < 4)
        return 0;
    return 1;
}

// swap function to swap two numbers
void swap(int *x, int *y)
{
    *x = *x + *y;
    *y = *x - *y;
    *x = *x - *y;
    printf("");
}

// Reads the user input character and return ascii value of that
int readEnteredKey()
{
    char c;
    c = _getch();
    if (c == -32)
        c = _getch();
    if (beep == 1 && sound == 1)
    {
        Beep(550, 100);
        beep = 0;
        return c;
    }
    beep = 1;
    return c;
}
int readEnteredKey2(int index)
{
    char c;
    c = _getch();
    if (c == -32)
        c = _getch();
    if (beep == 1 && sound == 1)
    {
        Beep(200 + (100 * (index + 1)), 200);
        beep = 0;
        return c;
    }
    beep = 1;
    return c;
}

// shift up function
int shiftUp(int arr[][4])
{
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
            if (arr[i][j] == 0)
                break;
        if (j < 4)
            break;
    }
    if (i == 3) // shifting not possible
        return 0;

    // Successfully swapped two numbers !
    swap(&arr[i][j], &arr[i + 1][j]);
    return 1; // Success
}

int shiftDown(int arr[][4])
{
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
            if (arr[i][j] == 0)
                break;
        if (j < 4)
            break;
    }
    if (i == 0) // shifting not possible
        return 0;
    swap(&arr[i][j], &arr[i - 1][j]); // swap numbers

    return 1; // shift up success
}

int shiftRight(int arr[][4])
{
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
            if (arr[i][j] == 0)
                break;
        if (j < 4)
            break;
    }
    if (j == 0) // shifting not possible
        return 0;

    swap(&arr[i][j], &arr[i][j - 1]);

    return 1; // shift up success
}

int shiftLeft(int arr[][4])
{
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
            if (arr[i][j] == 0)
                break;
        if (j < 4)
            break;
    }

    if (j == 3) // shifting not possible
        return 0;

    swap(&arr[i][j], &arr[i][j + 1]);
    return 1; // shift up success
}

// Game rules
void gameRule()
{
    system("cls");

    int i, j, k = 1;

    printf("\t\t  MATRIX PUZZLE\n");
    printf("\n");
    printf(ANSI_COLOR_RED "                 RULE OF THIS GAME                 \n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_RED "\n1.You can move only 1 step at a time by arrow key " ANSI_COLOR_RESET);
    printf("\n\tMove Up   : by Up arrow key ");
    printf("\n\tMove Down : by Down arrow key");
    printf("\n\tMove Left : by Left arrow key");
    printf("\n\tMove Right: by Right arrow key");

    printf(ANSI_COLOR_RED "\n2.You can move number at empty position only " ANSI_COLOR_RESET);
    printf("\n");
    printf(ANSI_COLOR_RED "\n3. For each valid move : your total number of move will decreased by 1 \n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_RED "4. Wining situation : " ANSI_COLOR_RESET);
    printf(ANSI_COLOR_RED " Number in a 4*4 matrix should be in order from 1 to 15 " ANSI_COLOR_RESET);
    printf("\n\n            winning situation:         \n");

    printf(ANSI_COLOR_YELLOW "---------------------\n" ANSI_COLOR_RESET);

    for (i = 1; i <= 15;)
    {
        printf(ANSI_COLOR_YELLOW "| " ANSI_COLOR_RESET);
        for (j = 1; j <= 4; j++)
        {
            if (i == 16)
            {
                printf(ANSI_COLOR_YELLOW "   | " ANSI_COLOR_RESET);
                break;
            }
            printf(ANSI_COLOR_YELLOW "%2d | " ANSI_COLOR_RESET, i);
            i++;
        }
        printf("\n");
    }

    printf(ANSI_COLOR_YELLOW "---------------------\n" ANSI_COLOR_RESET);
    printf("\n5.You can exit the game at any time by pressing 'E' or 'e' ");

    printf("\nSo Try to win in minimum no of move \n");

    printf("\nEnter any key to menu.....   ");

    int x = readEnteredKey();
    system("cls");
}

// added by me
void you_lose_sound()
{
    int i;
    if (sound == 1)
    {
        for (i = 600; i >= 300; i -= 50)
        {
            Beep(i, 200);
        }
        Beep(350, 1000);
    }
}
void you_win_sound()
{
    int i;
    if (sound == 1)
    {
        Beep(300, 300);
        Beep(350, 200);
        Beep(200, 50);
        Beep(300, 200);
        Beep(400, 1000);
    }
}
void print_menu(int index)
{
    char menu_item[6][30] = {"Play", "Difficulty", "Sound", "Unlimited moves", "How to play", "Quit game"};
    printf("\n\n\t\tgame menu\n");
    for (int i = 0; i < 6; i++)
    {
        if (i == index)
        {
            printf(ANSI_COLOR_BLUE "\n--> %s" ANSI_COLOR_RESET, menu_item[i]);
        }
        else
        {
            printf("\n    %s", menu_item[i]);
        }
        switch (i)
        {
        case 1:
            printf(ANSI_COLOR_MAGENTA "        %d Moves" ANSI_COLOR_RESET, difficulty * 50);
            break;
        case 2:
            if (sound == 1)
                printf(ANSI_COLOR_YELLOW "             on" ANSI_COLOR_RESET);
            else
                printf(ANSI_COLOR_MAGENTA "             off" ANSI_COLOR_RESET);
            break;
        case 3:
            if (cheat == 1)
                printf(ANSI_COLOR_MAGENTA "   off" ANSI_COLOR_RESET);
            else
                printf(ANSI_COLOR_YELLOW "   on" ANSI_COLOR_RESET);
            break;
        default:
            break;
        }
    }
    printf("\n\n");
}

void game_menu(int *maxtry)
{
    int key, menu_arrow = 0;
    system("cls");
    print_menu(menu_arrow);
    while (1)
    {
        key = readEnteredKey2(menu_arrow);
        system("cls");
        printf("<%d>", key);
        switch (key)
        {
        case 72:
            if (menu_arrow >= 1)
            {
                menu_arrow--;
            }
            break;
        case 80:
            if (menu_arrow <= 4)
            {
                menu_arrow++;
            }
            break;
        case 13:
            beep = 1;
            switch (menu_arrow)
            {
            case 0:
                return;
            case 1:
                if (difficulty >= 4)
                {
                    difficulty = 1;
                    *maxtry = difficulty * 50;
                    break;
                }
                *maxtry = difficulty * 50;
                difficulty++;
                break;
            case 2:
                sound = sound == 1 ? 0 : 1;
                break;
            case 3:
                cheat = cheat == 1 ? 0 : 1;
                break;
            case 4:
                gameRule();
                break;
            case 5:
                exit(0);
            default:
                break;
            }
        default:
            break;
        }
        print_menu(menu_arrow);
    }
}

// main function
int main()
{
    int arr[4][4], flg;           // matrix
    int maxTry = difficulty * 50; // maximum move
    char name[20];
    for (int k = 0; k < 3; k++)
        printf("\n");
    printf("Player Name: ");
    scanf("%s", name);

    system("cls"); // to clear screen

    while (1)
    {
        game_menu(&maxTry);
        while (1)
        {
            flg = 1;
            createMatrix(arr); // calling function to create  matrix
                               // gameRule();        // game rule function calling
            fflush(stdin);
            while (!winner(arr)) // checking for winning situation
            {
                system("cls");
                if (!maxTry) // for remaining zero move
                    break;

                printf("\n\n  Enter e to [e]ixt\n  Player Name:  %s ,  Move remaining : %d ", name, cheat==1?maxTry:NULL);
                if(cheat == 0)
                    printf("Unlimited moves\n\n");
                else
                    printf("\n\n");

                showMatrix(arr); // show matrix

                int key = readEnteredKey(); // this will return ascii code of user entered key

                switch (key) // maping
                {
                case 101: // ascii of E

                case 69: // ascii of e
                    printf("\a\a\a\a\a\a\n     Thanks for Playing ! \n\a");
                    printf("\nHit 'Enter' to menu \n");
                    key = readEnteredKey();
                    flg = 0;
                    break;

                case 72: // arrow up
                    if (shiftUp(arr) && cheat == 1)
                        maxTry--;
                    break;
                case 80: // arrow down
                    if (shiftDown(arr) && cheat == 1)
                        maxTry--;
                    break;
                case 77: // arrow  right
                    if (shiftRight(arr) && cheat == 1)
                        maxTry--;
                    break;
                case 75: // arrow left
                    if (shiftLeft(arr) && cheat == 1)
                        maxTry--;
                    break;
                default:
                    if (cheat == 1)
                    {
                        printf("\n\n      unlimited moves");
                        break;
                    }
                    printf("\n\n      \a\a Not Allowed \a");
                }
                if (flg == 0)
                    break;
            }
            if (flg == 0)
                break;

            if (!maxTry)
            {
                printf(ANSI_COLOR_RED "\n\a          YOU LOSE !          \a\a" ANSI_COLOR_RESET);
                you_lose_sound();
                readEnteredKey();
                break;
            }
            else
            {
                printf(ANSI_COLOR_GREEN "\n\a!!!!!!!!!!!!!Congratulations  %s for winning this game !!!!!!!!!!!!!\n\a" ANSI_COLOR_RESET, name);
                you_win_sound();
                readEnteredKey();
                break;
            }

            fflush(stdin); // Will clear the buffer
            // char check;
            // printf(ANSI_COLOR_GREEN "\nWant to play again? (y/n) : " ANSI_COLOR_RESET);
            // scanf("%c", &check);

            // // Leave the game here itself !
            // if ((check != 'y') && (check != 'Y'))
            // {
            //     maxTry = 4;
            //     break;
            // }
        }

        maxTry = difficulty * 50;
    }
    return 0;
}
