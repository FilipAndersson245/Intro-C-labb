// C-labb-intro.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include <locale.h>
#include <Windows.h>
#include <math.h>

int asignment1()
{
    int   num = 0;
    int   antal_variabler;
    int   nytt_tal;

    srand((unsigned)time(NULL));
    nytt_tal = rand() % 100 + 1;

    printf("Datorn tänker på ett tal mellan 1 och 100. Varsågod att gissa:");
    antal_variabler = scanf_s("%d", &num);
    getchar(); //töm radslutet efter scanf
    while (num != nytt_tal)
    {
        if (num > nytt_tal)
            printf("Talet är för stort.");
        else printf("Talet är för litet.");
        printf("Gissa igen: ");
        antal_variabler = scanf_s("%d", &num);
        getchar(); //töm radslutet efter scanf
    }
    printf("Right guessed");
    getchar();//för att stanna i consolen till du hunnit se körningen
    return 0;
}

int asignment2()
{
    char again = 'y';
    while ((again == 'y') || (again == 'Y'))
    {
        asignment1();
        printf("Right guessed\n Wannt to try again? (y/n)");
        again = getchar();
    }
    return 0;
}

int asignment3()
{
    int num1 = 0, num2 = 0;
    int antalVariabler = scanf_s("%d %d", num1, num2);
    printf("summan av %d + %d = %d", num1, num2, (num1 + num2));
    return 0;
}

int asignment4()
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = 1; j < i; j++)
        {
            printf("*");
        }
        printf("\n");
    }
    return 0;
}

int asignment5()
{
    int  center = 4;
    int min, max;
    min = max = 4;
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (j<min || j>max)
                printf(" ");
            else
                printf("*");
        }
        printf("\n");
        min--, max++;

        if (i == 2)
        {
            min = center - 1, max = center + 1;
        }
    }
    return 0;
}

void gotoxy(int x, int y) {
    COORD pos = { x, y };
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}

void hidecursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void randomColor()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), rand() % 5 ? 2 : rand() % 15 + 1);
}

void paintTop(int consoleWidth, int rows, int topWidth, int center)
{
    randomColor();
    int span = (topWidth / 2);
    int min = center - span > 0 ? center - span : 0;
    int max = center + span < consoleWidth ? center + span : consoleWidth;

    char* str = (char *)malloc((consoleWidth + 1)*rows + 1);
    char* savedStr = str;
    int index = 0;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < consoleWidth; j++)
        {
            if (j<min || j>max)
                str[index] = ' ';
            else
                str[index] = '*';
            index++;
        }
        min--;
        max++;
        str[index] = '\n';
        index++;
    }
    str[index] = '\0';
    printf(str);
    free(savedStr);
}

int asignment6()
{
    int consoleWidth = 119;
    int center = consoleWidth / 2;
    bool right = false;
    int upperBound = ((consoleWidth / 5) * 4);
    int lowerBound = consoleWidth / 5;
    int top = center;
    int numOfchunks = 12;
    hidecursor();
    for (;;)
    {
        int diff = top - center;
        gotoxy(0, 0);
        for (int i = 1; i < numOfchunks * 2; i += 2)
        {
            paintTop(consoleWidth, i < 5 ? i : 5, i, top - (diff / numOfchunks)*(i / 2));
        }
        if (top > upperBound)
            right = false;
        else if (top < lowerBound)
            right = true;
        if (right)
            top += (rand() % 15) + 4;
        else
            top -= (rand() % 15) + 4;
        Sleep(30);
    }

    return 0;
}

enum Asignment
{
    zero = 0,
    first,
    second,
    third,
    fourth,
    fifth,
    sixth
};

void getAsignments() {
    for (;;) {
        Asignment a;
        printf("\nWrite 0 if you wannt to quit\nChoose asignment:");
        scanf_s("%d", &a);
        getchar();
        switch (a)
        {
        case zero:
            return;
        case first:
            asignment1();
            break;
        case second:
            asignment2();
            break;
        case third:
            asignment3();
            break;
        case fourth:
            asignment4();
            break;
        case fifth:
            asignment5();
            break;
        case sixth:
            asignment6();
            break;
        default:
            printf("Asignment Not implemented");
            break;
        }
    }
}

int main()
{
    char *locale;

    locale = setlocale(LC_ALL, "");

    getAsignments();

    return 0;
}