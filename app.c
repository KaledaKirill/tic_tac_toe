#include <stdio.h>
#define MAX_NAME 15

char field[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
char players[2][MAX_NAME];
char symb[2] = {'x', 'o'};

void render()
{
    printf(" %c | %c | %c\n", field[0][0], field[0][1], field[0][2]);
    printf("===========\n");
    printf(" %c | %c | %c\n", field[1][0], field[1][1], field[1][2]);
    printf("===========\n");
    printf(" %c | %c | %c\n", field[2][0], field[2][1], field[2][2]);
}

void clear()
{
    for(int i = 0; i < 3; i ++)
    {
        for(int j = 0; j < 3; j++)
        {
            field[i][j] = (j + 3 * i + 1) + '0';
        }
    }
}

int is_empty(int cell)
{
    if(cell < 1 || cell > 9)
    {
        return 0;
    }
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if((field[i][j] - '0') == cell)
            {
                return 1;
            }
        }
    }

    return 0;
}

void action(int index)
{
    int num;
    int cell;
    if(index % 2 == 0) num = 0;
    else num = 1;
    while(1)
    {
        printf("%s, choose number of cell: ", players[num]);
        scanf("%d", &cell);
        if(is_empty(cell) == 0)
        {
            puts("cell aren't empty or doesn't exist");
        }
        else break;
    }
    switch(cell)
    {
        case 1:
            field[0][0] = symb[num];
            break;
        case 2:
            field[0][1] = symb[num];
            break;
        case 3:
            field[0][2] = symb[num];
            break;
        case 4:
            field[1][0] = symb[num];
            break;
        case 5:
            field[1][1] = symb[num];
            break;
        case 6:
            field[1][2] = symb[num];
            break;
        case 7:
            field[2][0] = symb[num];
            break;
        case 8:
            field[2][1] = symb[num];
            break;
        case 9:
            field[2][2] = symb[num];
            break;
    }
}

int check_win(int index)
{
    int num;
    if(index % 2 == 0) num = 0;
    else num = 1;

    if(field[0][0] == field[1][1] && field[1][1] == field[2][2])
    {
        return num;
    } 

    if(field[2][0] == field[1][1] && field[1][1] == field[0][2])
    {
        return num;
    }

    for(int i = 0;  i < 3; i++)
    {
        if(field[i][0] == field[i][1] && field[i][1] == field[i][2])
        {
            return num;
        }
        if(field[0][i] == field[1][i] && field[1][i] == field[2][i])
        {
            return num;
        }
    }

    return -1;
}

void enter_name(char *str)
{
    char c;
    char *ptr = str;
    int i = 0;

    while((c = getchar()) != '\n' && c != EOF && i < MAX_NAME - 1)
    {
        ptr[i++] = c;
    }

    ptr[i] = '\0';
    if(i == MAX_NAME - 1)
    {
        while((c = getchar()) != '\n' && c != EOF);
    }
}

int main()
{
    int win_num;
    int mode;
    printf("player 1, please, enter your name: ");
    enter_name(players[0]);
    printf("player 2, please, enter your name: ");
    enter_name(players[1]);

    while(1)
    {
        render();

        for(int i = 0; i < 9; i++)
        {
            action(i);
            printf("\e[1;1H\e[2J");
            render();
            win_num = check_win(i);
            if(win_num == -1)
            {
                if(i == 8)
                {
                    puts("draw");
                }
                continue;
            }
            else if(win_num == 0)
            {
                printf("%s is winner!\n", players[0]);
                break;
            }
            else if(win_num == 1)
            {
                printf("%s is winner!\n", players[1]);
                break;
            }
            }

            puts("1--continue\n2--exit");
            scanf("%d", &mode);
            if(mode == 2) break;

            clear();
        }
    
    return 0;
}