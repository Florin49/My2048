#include <iostream>
#include <graphics.h>
#include <windows.h>
#include <time.h>
#include <cmath>
#include <string>
#include <stdlib.h>

using namespace std;

const char *ImageName(int a)
{
    char nr[9] = "";
    int i = 0;
    if (a / 1000 > 0)
    {
        nr[i] = (char)(a / 1000 + '0');
        i++;
    }
    if (a / 100 > 0)
    {
        nr[i] = (char)(a / 100 % 10 + '0');
        i++;
    }
    if (a / 10 > 0)
    {
        nr[i] = (char)(a / 10 % 10 + '0');
        i++;
    }
    nr[i] = (char)(a % 10 + '0');

    strcat(nr, ".jpg");

    char *Nr = new char[strlen(nr)];
    strcpy(Nr, nr);
    delete[] nr;
    return Nr;
}

void Instantiate(int a[6][6], int L)
{
    int W, H, i, j, pk = 1;
    W = 4 * L;
    H = 4 * L;
    initwindow(W, H, "2048");
    for (i = 1; i <= 11; i++)
    {
        pk = pk * 2;
        cout << ImageName(pk) << " " << strlen(ImageName(pk)) << endl;
        readimagefile(ImageName(pk), L * (i % 4), L * (i % 4), L * (i % 4 + 1), L * (i % 4 + 1));
        readimagefile(ImageName(pk), L * (3 - i % 4), L * (i % 4), L * (4 - i % 4), L * (i % 4 + 1));
        delay(300);
    }

    for (i = 1; i <= 4; i++)
        for (j = 1; j <= 4; j++)
            readimagefile("0.jpg", L * (j - 1), L * (i - 1), L * j, L * i);
    srand(time(NULL));
    int i1, j1, i2, j2;
    i1 = rand() % 4 + 1;
    j1 = rand() % 4 + 1;
    if (i1 % 5 == 0 || j1 % 5 == 0)
    {
        readimagefile("4.jpg", L * (j1 - 1), L * (i1 - 1), L * j1, L * i1);
        a[i1][j1] = 4;
    }
    else
    {
        readimagefile("2.jpg", L * (j1 - 1), L * (i1 - 1), L * j1, L * i1);
        a[i1][j1] = 2;
    }
    do
    {
        i2 = rand() % 4 + 1;
        j2 = rand() % 4 + 1;
    } while (i1 != i2 && j1 != j2);
    if (i1 % 5 == 0 || j1 % 5 == 0)
    {
        readimagefile("4.jpg", L * (j2 - 1), L * (i2 - 1), L * j2, L * i2);
        a[i2][j2] = 4;
    }
    else
    {
        readimagefile("2.jpg", L * (j2 - 1), L * (i2 - 1), L * j2, L * i2);
        a[i2][j2] = 2;
    }
}

void ConsoleDisplay(int a[6][6])
{
    cout << endl;
    for (int i = 1; i <= 4; i++)
    {
        for (int j = 1; j <= 4; j++)
            cout << a[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

void Populate(int a[6][6], int s[4], int L)
{
    int i, j;
    a[0][5] = 0;
    for (i = 1; i <= 4; i++)
        for (j = 1; j <= 4; j++)
            if (a[i][j] == 0)
                a[0][5] = 1;
    if ((s[1] == 1 || s[2] == 1 || s[3] == 1 || s[0] == 1) && a[0][5] == 1)
    {

        do
        {
            i = rand() % 4 + 1;
            j = rand() % 4 + 1;
        } while (a[i][j] != 0);

        if (rand() % 7 == 0)
        {
            a[i][j] = 4;
            readimagefile("4.jpg", L * (j - 1), L * (i - 1), L * j, L * i);
        }
        else
        {
            a[i][j] = 2;
            readimagefile("2.jpg", L * (j - 1), L * (i - 1), L * j, L * i);
        }
    }
}
void UpdateGameStatus(int a[6][6], int L)
{
    if (a[0][0] == 2048)
    {
        delay(3000);
        readimagefile("yes.jpg", 0, 0, 4 * L, 4 * L);
        delay(10000);
    }
    else if (a[0][0] == 0)

    {
        a[0][0] = 1;
        for (int i = 1; i <= 4; i++)
            for (int j = 1; j <= 4; j++)
                if (a[i][j] == 0 || (a[i - 1][j] == a[i][j] || a[i][j - 1] == a[i][j] || a[i + 1][j] == a[i][j] || a[i][j + 1] == a[i][j]))
                    a[0][0] = 0;
    }
    if (a[0][0] == 1)
    {
        delay(3000);
        readimagefile("no.jpg", 0, 0, 4 * L, 4 * L);
        delay(10000);
    }
}

int main()
{

    int a[6][6] = {0}, i, j, L, s[4];
    L = 200;
    Instantiate(a, L);

    char ch;
    while (a[0][0] == 0)
    {
        ch = getch();
        if (ch == KEY_LEFT)
        {

            for (i = 0; i < 4; i++)
            {
                s[i] = 0;
                if (a[i + 1][1] == 0 && a[i + 1][2] == 0 && a[i + 1][3] == 0 && a[i + 1][4] != 0) /// CASE 1
                {
                    s[i] = 1;
                    a[i + 1][1] = a[i + 1][4];
                    a[i + 1][4] = 0;
                    readimagefile(ImageName(a[i + 1][1]), 0, L * i, L, L * (i + 1));
                    readimagefile("0.jpg", L * 3, L * i, L * 4, L * (i + 1));
                }
                /*else if(a[i+1][1]==0 && a[i+1][2]==0 && a[i+1][3]!=0 && a[i+1][4]==0)///CASE 2
                {
                    s[i]=1;
                    a[i+1][1]=a[i+1][3];
                    a[i+1][3]=0;

                    readimagefile("0.jpg",L*2,L*i,L*3,L*(i+1));
                    readimagefile(ImageName(a[i+1][1]),0,L*i,L,L*(i+1));
                }*/
                /*else if(a[i+1][1]==0 && a[i+1][2]!=0 && a[i+1][3]==0 && a[i+1][4]==0)///CASE 3
                {
                    s[i]=1;
                    a[i+1][1]=a[i+1][2];
                    a[i+1][2]=0;
                    readimagefile("0.jpg",L,L*i,L*2,L*(i+1));
                    readimagefile(ImageName(a[i+1][1]),0,L*i,L,L*(i+1));
                }*/
                /*else if(a[i+1][1]==a[i+1][2] && a[i+1][2]!=0 && a[i+1][3]==0 && a[i+1][4]==0)///CASE 4
                {
                    s[i]=1;
                    a[i+1][1]=2*a[i+1][2];
                    a[i+1][2]=0;
                    readimagefile("0.jpg",L,L*i,L*2,L*(i+1));
                    readimagefile(ImageName(a[i+1][1]),0,L*i,L,L*(i+1));
                    if(a[i+1][1]==2048)
                      a[0][0]=2048;

                }*/
                /*else if(a[i+1][1]==a[i+1][3] && a[i+1][3]!=0 && a[i+1][2]==0 && a[i+1][4]==0)///CASE 5
                {
                    s[i]=1;
                    a[i+1][1]=2*a[i+1][3];
                    a[i+1][3]=0;
                    readimagefile("0.jpg",L*2,L*i,L*3,L*(i+1));
                    readimagefile(ImageName(a[i+1][1]),0,L*i,L,L*(i+1));
                    if(a[i+1][1]==2048)
                      a[0][0]=2048;
                }*/
                else if (a[i + 1][1] == a[i + 1][4] && a[i + 1][4] != 0 && a[i + 1][2] == 0 && a[i + 1][3] == 0) /// CASE 6
                {
                    s[i] = 1;
                    a[i + 1][1] = 2 * a[i + 1][4];
                    a[i + 1][4] = 0;
                    readimagefile("0.jpg", L * 3, L * i, L * 4, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][1]), 0, L * i, L, L * (i + 1));
                    if (a[i + 1][1] == 2048)
                        a[0][0] = 2048;
                }
                /*else if(a[i+1][2]==a[i+1][3] && a[i+1][3]!=0 && a[i+1][1]==0 && a[i+1][4]==0)///CASE 7
                {
                    s[i]=1;
                    a[i+1][1]=2*a[i+1][2];
                    a[i+1][2]=0;
                    a[i+1][3]=0;
                    readimagefile("0.jpg",L,L*i,L*2,L*(i+1));
                    readimagefile("0.jpg",L*2,L*i,L*3,L*(i+1));
                    readimagefile(ImageName(a[i+1][1]),0,L*i,L,L*(i+1));
                    if(a[i+1][1]==2048)
                       a[0][0]=2048;

                }*/
                else if (a[i + 1][2] == a[i + 1][4] && a[i + 1][4] != 0 && a[i + 1][3] == 0 && a[i + 1][1] == 0) /// CASE 8
                {
                    s[i] = 1;
                    a[i + 1][1] = 2 * a[i + 1][2];
                    a[i + 1][2] = 0;
                    a[i + 1][4] = 0;
                    readimagefile("0.jpg", L, L * i, L * 2, L * (i + 1));
                    readimagefile("0.jpg", L * 3, L * i, L * 4, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][1]), 0, L * i, L, L * (i + 1));
                    if (a[i + 1][1] == 2048)
                        a[0][0] = 2048;
                }
                else if (a[i + 1][3] == a[i + 1][4] && a[i + 1][4] != 0 && a[i + 1][2] == 0 && a[i + 1][1] == 0) /// CASE 9
                {
                    s[i] = 1;
                    a[i + 1][1] = 2 * a[i + 1][3];
                    a[i + 1][3] = 0;
                    a[i + 1][4] = 0;
                    readimagefile("0.jpg", L * 2, L * i, L * 3, L * (i + 1));
                    readimagefile("0.jpg", L * 3, L * i, L * 4, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][1]), 0, L * i, L, L * (i + 1));
                    if (a[i + 1][1] == 2048)
                        a[0][0] = 2048;
                }
                /*else if(a[i+1][1]!=0 && a[i+1][2]==0 && a[i+1][3]!=0 && a[i+1][4]==0 && a[i+1][1]!=a[i+1][3])///CASE 10
                {
                    s[i]=1;
                    a[i+1][2]=a[i+1][3];
                    a[i+1][3]=0;
                    readimagefile("0.jpg",L*2,L*i,L*3,L*(i+1));
                    readimagefile(ImageName(a[i+1][2]),L,L*i,L*2,L*(i+1));
                }*/
                else if (a[i + 1][1] != 0 && a[i + 1][2] == 0 && a[i + 1][3] == 0 && a[i + 1][4] != 0 && a[i + 1][4] != a[i + 1][1]) /// CASE 11
                {
                    s[i] = 1;
                    a[i + 1][2] = a[i + 1][4];
                    a[i + 1][4] = 0;
                    readimagefile("0.jpg", L * 3, L * i, L * 4, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][2]), L, L * i, L * 2, L * (i + 1));
                }
                /*else if(a[i+1][1]==0 && a[i+1][2]!=0 && a[i+1][3]!=0 && a[i+1][4]==0 && a[i+1][2]!=a[i+1][3])///CASE 12
                {
                    s[i]=1;
                    a[i+1][1]=a[i+1][2];
                    a[i+1][2]=a[i+1][3];
                    a[i+1][3]=0;
                    readimagefile(ImageName(a[i+1][1]),0,L*i,L,L*(i+1));
                    readimagefile(ImageName(a[i+1][2]),L,L*i,L*2,L*(i+1));
                    readimagefile("0.jpg",L*2,L*i,L*3,L*(i+1));
                }*/
                else if (a[i + 1][1] == 0 && a[i + 1][2] != 0 && a[i + 1][3] == 0 && a[i + 1][4] != 0 && a[i + 1][4] != a[i + 1][2]) /// CASE 13
                {
                    s[i] = 1;
                    a[i + 1][1] = a[i + 1][2];
                    a[i + 1][2] = a[i + 1][4];
                    a[i + 1][4] = 0;
                    readimagefile(ImageName(a[i + 1][1]), 0, L * i, L, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][2]), L, L * i, L * 2, L * (i + 1));
                    readimagefile("0.jpg", L * 3, L * i, L * 4, L * (i + 1));
                }
                else if (a[i + 1][1] == 0 && a[i + 1][2] == 0 && a[i + 1][3] != 0 && a[i + 1][3] != a[i + 1][4]) /// CASE 14
                {
                    s[i] = 1;
                    a[i + 1][1] = a[i + 1][3];
                    a[i + 1][2] = a[i + 1][4];
                    a[i + 1][4] = 0;
                    a[i + 1][3] = 0;

                    readimagefile(ImageName(a[i + 1][1]), 0, L * i, L, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][2]), L, L * i, L * 2, L * (i + 1));
                    readimagefile("0.jpg", L * 2, L * i, L * 3, L * (i + 1));
                    readimagefile("0.jpg", L * 3, L * i, L * 4, L * (i + 1));
                }
                /*else if(a[i+1][1]==a[i+1][2] && a[i+1][2]!=0 && a[i+1][3]!=0 && a[i+1][4]==0)///CASE 15
                {
                    s[i]=1;
                    a[i+1][1]=2*a[i+1][2];
                    a[i+1][2]=a[i+1][3];
                    a[i+1][3]=0;

                    readimagefile(ImageName(a[i+1][1]),0,L*i,L,L*(i+1));
                    readimagefile(ImageName(a[i+1][2]),L,L*i,L*2,L*(i+1));
                    readimagefile("0.jpg",L*2,L*i,L*3,L*(i+1));

                    if(a[i+1][1]==2048)
                         a[0][0]=2048;
                }*/
                /*else if(a[i+1][2]==a[i+1][3] && a[i+1][1]!=0 && a[i+1][3]!=0 && a[i+1][3]!=a[i+1][1] && a[i+1][4]==0)///CASE 16
                {
                    s[i]=1;
                    a[i+1][2]=2*a[i+1][2];
                    a[i+1][3]=0;
                    readimagefile("0.jpg",L*2,L*i,L*3,L*(i+1));
                    readimagefile(ImageName(a[i+1][2]),L,L*i,L*2,L*(i+1));
                    if(a[i+1][2]==2048)
                        a[0][0]=2048;
                }*/
                else if (a[i + 1][2] == a[i + 1][4] && a[i + 1][1] != 0 && a[i + 1][4] != 0 && a[i + 1][2] != a[i + 1][1] && a[i + 1][3] == 0) /// CASE 17
                {
                    s[i] = 1;
                    a[i + 1][2] = 2 * a[i + 1][2];
                    a[i + 1][4] = 0;
                    readimagefile("0.jpg", L * 3, L * i, L * 4, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][2]), L, L * i, L * 2, L * (i + 1));
                    if (a[i + 1][2] == 2048)
                        a[0][0] = 2048;
                }
                else if (a[i + 1][1] == a[i + 1][2] && a[i + 1][2] != 0 && a[i + 1][3] == 0 && a[i + 1][4] != 0) /// CASE 18
                {
                    s[i] = 1;
                    a[i + 1][1] = 2 * a[i + 1][2];
                    a[i + 1][2] = a[i + 1][4];
                    a[i + 1][4] = 0;
                    readimagefile("0.jpg", L * 3, L * i, L * 4, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][1]), 0, L * i, L, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][2]), L, L * i, L * 2, L * (i + 1));
                    if (a[i + 1][1] == 2048)
                        a[0][0] = 2048;
                }
                else if (a[i + 1][1] != 0 && a[i + 1][2] != 0 && a[i + 1][2] != a[i + 1][1] && a[i + 1][2] != a[i + 1][4] && a[i + 1][3] == 0 && a[i + 1][4] != 0) /// CASE 19
                {
                    s[i] = 1;
                    a[i + 1][3] = a[i + 1][4];
                    a[i + 1][4] = 0;
                    readimagefile("0.jpg", L * 3, L * i, L * 4, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][3]), L * 2, L * i, L * 3, L * (i + 1));
                }
                else if (a[i + 1][1] == a[i + 1][3] && a[i + 1][3] != 0 && a[i + 1][2] == 0) /// CASE 20
                {
                    s[i] = 1;
                    a[i + 1][1] = 2 * a[i + 1][3];
                    a[i + 1][2] = a[i + 1][4];
                    a[i + 1][4] = 0;
                    a[i + 1][3] = 0;
                    readimagefile("0.jpg", L * 3, L * i, L * 4, L * (i + 1));
                    readimagefile("0.jpg", L * 2, L * i, L * 3, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][1]), 0, L * i, L, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][2]), L, L * i, L * 2, L * (i + 1));
                    if (a[i + 1][1] == 2048)
                        a[0][0] = 2048;
                }
                else if (a[i + 1][3] == a[i + 1][4] && a[i + 1][1] != 0 && a[i + 1][4] != 0 && a[i + 1][3] != a[i + 1][1] && a[i + 1][2] == 0) /// CASE 21
                {
                    s[i] = 1;
                    a[i + 1][2] = 2 * a[i + 1][3];
                    a[i + 1][4] = 0;
                    a[i + 1][3] = 0;
                    readimagefile("0.jpg", L * 3, L * i, L * 4, L * (i + 1));
                    readimagefile("0.jpg", L * 2, L * i, L * 3, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][2]), L, L * i, L * 2, L * (i + 1));
                    if (a[i + 1][2] == 2048)
                        a[0][0] = 2048;
                }
                else if (a[i + 1][1] != 0 && a[i + 1][3] != 0 && a[i + 1][3] != a[i + 1][1] && a[i + 1][3] != a[i + 1][4] && a[i + 1][2] == 0) /// CASE 22
                {
                    s[i] = 1;
                    a[i + 1][2] = a[i + 1][3];
                    a[i + 1][3] = a[i + 1][4];
                    a[i + 1][4] = 0;
                    readimagefile("0.jpg", L * 3, L * i, L * 4, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][2]), L, L * i, L * 2, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][3]), L * 2, L * i, L * 3, L * (i + 1));
                }
                else if (a[i + 1][3] == a[i + 1][2] && a[i + 1][1] == 0 && a[i + 1][3] != 0) /// CASE 23
                {
                    s[i] = 1;
                    a[i + 1][1] = 2 * a[i + 1][2];
                    a[i + 1][2] = a[i + 1][4];
                    a[i + 1][3] = 0;
                    a[i + 1][4] = 0;
                    readimagefile("0.jpg", L * 2, L * i, L * 3, L * (i + 1));
                    readimagefile("0.jpg", L * 3, L * i, L * 4, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][2]), L, L * i, L * 2, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][1]), 0, L * i, L, L * (i + 1));
                    if (a[i + 1][1] == 2048)
                        a[0][0] = 2048;
                }
                else if (a[i + 1][4] == a[i + 1][3] && a[i + 1][3] != 0 && a[i + 1][3] != a[i + 1][2] && a[i + 1][1] == 0 && a[i + 1][2] != 0) /// CASE 24
                {
                    s[i] = 1;
                    a[i + 1][1] = a[i + 1][2];
                    a[i + 1][2] = a[i + 1][3] * 2;
                    a[i + 1][3] = 0;
                    a[i + 1][4] = 0;
                    readimagefile("0.jpg", L * 2, L * i, L * 3, L * (i + 1));
                    readimagefile("0.jpg", L * 3, L * i, L * 4, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][2]), L, L * i, L * 2, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][1]), 0, L * i, L, L * (i + 1));
                    if (a[i + 1][2] == 2048)
                        a[0][0] = 2048;
                }
                else if (a[i + 1][1] == 0 && a[i + 1][3] != a[i + 1][2] && ((a[i + 1][3] != 0 && a[i + 1][3] != a[i + 1][4]) || (a[i + 1][3] == 0 && a[i + 1][4] == 0)) && a[i + 1][2] != 0) /// CASE 25
                {
                    s[i] = 1;
                    a[i + 1][1] = a[i + 1][2];
                    a[i + 1][2] = a[i + 1][3];
                    a[i + 1][3] = a[i + 1][4];
                    a[i + 1][4] = 0;
                    readimagefile("0.jpg", L * 3, L * i, L * 4, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][1]), 0, L * i, L, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][2]), L, L * i, L * 2, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][3]), L * 2, L * i, L * 3, L * (i + 1));
                }
                else if (a[i + 1][1] == a[i + 1][2] && a[i + 1][2] != 0 && a[i + 1][3] != 0 && a[i + 1][4] != a[i + 1][3]) /// CASE 26
                {
                    s[i] = 1;
                    a[i + 1][1] = 2 * a[i + 1][2];
                    a[i + 1][2] = a[i + 1][3];
                    a[i + 1][3] = a[i + 1][4];
                    a[i + 1][4] = 0;
                    readimagefile("0.jpg", L * 3, L * i, L * 4, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][1]), 0, L * i, L, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][2]), L, L * i, L * 2, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][3]), L * 2, L * i, L * 3, L * (i + 1));
                    if (a[i + 1][1] == 2048)
                        a[0][0] = 2048;
                }
                else if (a[i + 1][2] == a[i + 1][3] && a[i + 1][1] != 0 && a[i + 1][3] != 0 && a[i + 1][3] != a[i + 1][1]) /// CASE 27
                {
                    s[i] = 1;
                    a[i + 1][2] = 2 * a[i + 1][2];
                    a[i + 1][3] = a[i + 1][4];
                    a[i + 1][4] = 0;
                    readimagefile("0.jpg", L * 3, L * i, L * 4, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][2]), L, L * i, L * 2, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][3]), L * 2, L * i, L * 3, L * (i + 1));
                    if (a[i + 1][2] == 2048)
                        a[0][0] = 2048;
                }
                else if (a[i + 1][1] != 0 && a[i + 1][2] != 0 && a[i + 1][3] != a[i + 1][2] && a[i + 1][3] == a[i + 1][4] && a[i + 1][1] != a[i + 1][2] && a[i + 1][3] != 0) /// CASE 28
                {
                    s[i] = 1;
                    a[i + 1][3] = a[i + 1][3] * 2;
                    a[i + 1][4] = 0;
                    readimagefile("0.jpg", L * 3, L * i, L * 4, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][3]), L * 2, L * i, L * 3, L * (i + 1));
                    if (a[i + 1][3] == 2048)
                        a[0][0] = 2048;
                }
                else if (a[i + 1][1] == a[i + 1][2] && a[i + 1][1] != 0 && a[i + 1][3] == a[i + 1][4]) /// CASE 29
                {
                    s[i] = 1;
                    a[i + 1][1] = a[i + 1][1] * 2;
                    a[i + 1][2] = a[i + 1][3] * 2;
                    a[i + 1][3] = 0;
                    a[i + 1][4] = 0;
                    readimagefile("0.jpg", L * 3, L * i, L * 4, L * (i + 1));
                    readimagefile("0.jpg", L * 2, L * i, L * 3, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][1]), 0, L * i, L, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][2]), L, L * i, L * 2, L * (i + 1));
                    if (a[i + 1][1] == 2048 || a[i + 1][2] == 2048)
                        a[0][0] = 2048;
                }
            }
            ConsoleDisplay(a);
            Populate(a, s, L);
            ConsoleDisplay(a);
            UpdateGameStatus(a, L);
        }
        else if (ch == KEY_RIGHT)
        {

            for (i = 0; i < 4; i++)
            {
                s[i] = 0;
                if (a[i + 1][4] == 0 && a[i + 1][3] == 0 && a[i + 1][2] == 0 && a[i + 1][1] != 0) /// CASE 1
                {
                    s[i] = 1;
                    a[i + 1][4] = a[i + 1][1];
                    a[i + 1][1] = 0;
                    readimagefile("0.jpg", 0, L * i, L, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][4]), L * 3, L * i, L * 4, L * (i + 1));
                }
                /*else if (a[i+1][4]==0 && a[i+1][3]==0 && a[i+1][2]!=0 && a[i+1][1]==0)///CASE 2
                {
                    s[i]=1;
                    a[i+1][4]=a[i+1][2];
                    a[i+1][2]=0;
                    readimagefile(ImageName(a[i+1][4]),L*3,L*i,L*4,L*(i+1));
                    readimagefile("0.jpg",L,L*i,L*2,L*(i+1));

                }*/
                /*else if (a[i+1][4]==0 && a[i+1][3]!=0 && a[i+1][2]==0 && a[i+1][1]==0)///CASE 3
                {
                    s[i]=1;
                    a[i+1][4]=a[i+1][3];
                    a[i+1][3]=0;
                    readimagefile("0.jpg",L*2,L*i,L*3,L*(i+1));
                    readimagefile(ImageName(a[i+1][4]),L*3,L*i,L*4,L*(i+1));


                }*/
                /*else if(a[i+1][4]==a[i+1][3] && a[i+1][3]!=0 && a[i+1][2]==0 && a[i+1][1]==0)///CASE 4
                {
                    s[i]=1;
                    a[i+1][4]=2*a[i+1][3];
                    a[i+1][3]=0;
                    readimagefile(ImageName(a[i+1][4]),L*3,L*i,L*4,L*(i+1));
                    readimagefile("0.jpg",L*2,L*i,L*3,L*(i+1));
                    if(a[i+1][4]==2048)
                       a[0][0]=2048;


                }*/
                /*else if(a[i+1][4]==a[i+1][2] && a[i+1][2]!=0 && a[i+1][3]==0 && a[i+1][1]==0)///CASE 5
                {
                    s[i]=1;
                    a[i+1][4]=2*a[i+1][2];
                    a[i+1][2]=0;
                    readimagefile("0.jpg",L,L*i,L*2,L*(i+1));
                    readimagefile(ImageName(a[i+1][4]),L*3,L*i,L*4,L*(i+1));
                    if(a[i+1][4]==2048)
                       a[0][0]=2048;

                }*/
                else if (a[i + 1][4] == a[i + 1][1] && a[i + 1][1] != 0 && a[i + 1][3] == 0 && a[i + 1][2] == 0) /// CASE 6
                {
                    s[i] = 1;
                    a[i + 1][4] = 2 * a[i + 1][4];
                    a[i + 1][1] = 0;
                    readimagefile("0.jpg", 0, L * i, L, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][4]), L * 3, L * i, L * 4, L * (i + 1));
                    if (a[i + 1][4] == 2048)
                        a[0][0] = 2048;
                }
                /*else if(a[i+1][2]==a[i+1][3] && a[i+1][3]!=0 && a[i+1][1]==0 && a[i+1][4]==0)///CASE 7
                {
                    s[i]=1;
                    a[i+1][4]=2*a[i+1][2];
                    a[i+1][2]=0;
                    a[i+1][3]=0;
                    readimagefile("0.jpg",L,L*i,L*2,L*(i+1));
                    readimagefile("0.jpg",L*2,L*i,L*3,L*(i+1));
                    readimagefile(ImageName(a[i+1][4]),L*3,L*i,L*4,L*(i+1));
                    if(a[i+1][4] ==2048)
                       a[0][0]=2048;

                }*/
                else if (a[i + 1][3] == a[i + 1][1] && a[i + 1][1] != 0 && a[i + 1][2] == 0 && a[i + 1][4] == 0) /// CASE 8
                {
                    s[i] = 1;
                    a[i + 1][4] = 2 * a[i + 1][3];
                    a[i + 1][3] = 0;
                    a[i + 1][1] = 0;
                    readimagefile("0.jpg", L * 2, L * i, L * 3, L * (i + 1));
                    readimagefile("0.jpg", 0, L * i, L, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][4]), L * 3, L * i, L * 4, L * (i + 1));
                    if (a[i + 1][4] == 2048)
                        a[0][0] = 2048;
                }
                else if (a[i + 1][2] == a[i + 1][1] && a[i + 1][1] != 0 && a[i + 1][3] == 0 && a[i + 1][4] == 0) /// CASE 9
                {
                    s[i] = 1;
                    a[i + 1][4] = 2 * a[i + 1][2];
                    a[i + 1][2] = 0;
                    a[i + 1][1] = 0;
                    readimagefile("0.jpg", L, L * i, L * 2, L * (i + 1));
                    readimagefile("0.jpg", 0, L * i, L, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][4]), L * 3, L * i, L * 4, L * (i + 1));
                    if (a[i + 1][4] == 2048)
                        a[0][0] = 2048;
                }
                /*else if (a[i+1][4]!=0 && a[i+1][3]==0 && a[i+1][2]!=0 && a[i+1][1]==0 && a[i+1][4]!=a[i+1][2])///CASE 10
                {
                    s[i]=1;
                    a[i+1][3]=a[i+1][2];
                    a[i+1][2]=0;
                    readimagefile("0.jpg",L*1,L*i,L*2,L*(i+1));
                    readimagefile(ImageName(a[i+1][3]),L*2,L*i,L*3,L*(i+1));

                }*/
                else if (a[i + 1][4] != 0 && a[i + 1][3] == 0 && a[i + 1][2] == 0 && a[i + 1][1] != 0 && a[i + 1][4] != a[i + 1][1]) /// CASE 11
                {
                    s[i] = 1;
                    a[i + 1][3] = a[i + 1][1];
                    a[i + 1][1] = 0;
                    readimagefile("0.jpg", 0, L * i, L, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][3]), L * 2, L * i, L * 3, L * (i + 1));
                }
                /*else if (a[i+1][4]==0 && a[i+1][3]!=0 && a[i+1][2]!=0 && a[i+1][1]==0 && a[i+1][2]!=a[i+1][3])///CASE 12
                {
                    s[i]=1;
                    a[i+1][4]=a[i+1][3];
                    a[i+1][3]=a[i+1][2];
                    a[i+1][2]=0;
                    readimagefile("0.jpg",L,L*i,L*2,L*(i+1));
                    readimagefile(ImageName(a[i+1][3]),L*2,L*i,L*3,L*(i+1));
                    readimagefile(ImageName(a[i+1][4]),L*3,L*i,L*4,L*(i+1));



                }*/
                else if (a[i + 1][4] == 0 && a[i + 1][3] != 0 && a[i + 1][2] == 0 && a[i + 1][1] != 0 && a[i + 1][1] != a[i + 1][3]) /// CASE 13
                {
                    s[i] = 1;
                    a[i + 1][4] = a[i + 1][3];
                    a[i + 1][3] = a[i + 1][1];
                    a[i + 1][1] = 0;
                    readimagefile("0.jpg", 0, L * i, L, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][3]), L * 2, L * i, L * 3, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][4]), L * 3, L * i, L * 4, L * (i + 1));
                }
                else if (a[i + 1][4] == 0 && a[i + 1][3] == 0 && a[i + 1][2] != 0 && a[i + 1][2] != a[i + 1][1]) /// CASE 14
                {
                    s[i] = 1;
                    a[i + 1][4] = a[i + 1][2];
                    a[i + 1][3] = a[i + 1][1];
                    a[i + 1][1] = 0;
                    a[i + 1][2] = 0;
                    readimagefile("0.jpg", L, L * i, L * 2, L * (i + 1));
                    readimagefile("0.jpg", 0, L * i, L, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][4]), L * 3, L * i, L * 4, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][3]), L * 2, L * i, L * 3, L * (i + 1));
                }
                /*else if(a[i+1][4]==a[i+1][3] && a[i+1][3]!=0 && a[i+1][2]!=0 && a[i+1][1]==0 )///CASE 15
                {
                    s[i]=1;
                    a[i+1][4]=2*a[i+1][4];
                    a[i+1][3]=a[i+1][2];
                    a[i+1][2]=0;
                    readimagefile("0.jpg",L,L*i,L*2,L*(i+1));
                    readimagefile(ImageName(a[i+1][4]),L*3,L*i,L*4,L*(i+1));
                    readimagefile(ImageName(a[i+1][3]),L*2,L*i,L*3,L*(i+1));
                    if(a[i+1][4]==2048)
                       a[0][0]=2048;


                }*/
                /*else if(a[i+1][2]==a[i+1][3] && a[i+1][4]!=0 && a[i+1][2]!=0 && a[i+1][2]!=a[i+1][4] && a[i+1][1]==0)///CASE 16
                {
                    s[i]=1;
                    a[i+1][3]=2*a[i+1][2];
                    a[i+1][2]=0;
                    readimagefile("0.jpg",L,L*i,L*2,L*(i+1));
                    readimagefile(ImageName(a[i+1][3]),L*2,L*i,L*3,L*(i+1));
                    if(a[i+1][3]==2048)
                        a[0][0]=2048;


                }*/
                else if (a[i + 1][3] == a[i + 1][1] && a[i + 1][4] != 0 && a[i + 1][1] != 0 && a[i + 1][3] != a[i + 1][4] && a[i + 1][2] == 0) /// CASE 17
                {
                    s[i] = 1;
                    a[i + 1][3] = 2 * a[i + 1][3];
                    a[i + 1][1] = 0;
                    readimagefile("0.jpg", 0, L * i, L, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][3]), L * 2, L * i, L * 3, L * (i + 1));
                    if (a[i + 1][3] == 2048)
                        a[0][0] = 2048;
                }
                else if (a[i + 1][4] == a[i + 1][3] && a[i + 1][3] != 0 && a[i + 1][2] == 0 && a[i + 1][1] != 0) /// CASE 18
                {
                    s[i] = 1;
                    a[i + 1][4] = 2 * a[i + 1][3];
                    a[i + 1][3] = a[i + 1][1];
                    a[i + 1][1] = 0;
                    readimagefile("0.jpg", 0, L * i, L, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][3]), L * 2, L * i, L * 3, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][4]), L * 3, L * i, L * 4, L * (i + 1));
                    if (a[i + 1][4] == 2048)
                        a[0][0] = 2048;
                }
                else if (a[i + 1][4] != 0 && a[i + 1][3] != 0 && a[i + 1][3] != a[i + 1][4] && a[i + 1][3] != a[i + 1][1] && a[i + 1][2] == 0 && a[i + 1][1] != 0) /// CASE 19
                {
                    s[i] = 1;
                    a[i + 1][2] = a[i + 1][1];
                    a[i + 1][1] = 0;
                    readimagefile("0.jpg", 0, L * i, L, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][2]), L, L * i, L * 2, L * (i + 1));
                }
                else if (a[i + 1][4] == a[i + 1][2] && a[i + 1][2] != 0 && a[i + 1][3] == 0) /// CASE 20
                {
                    s[i] = 1;
                    a[i + 1][4] = 2 * a[i + 1][2];
                    a[i + 1][3] = a[i + 1][1];
                    a[i + 1][1] = 0;
                    a[i + 1][2] = 0;
                    readimagefile("0.jpg", 0, L * i, L, L * (i + 1));
                    readimagefile("0.jpg", L, L * i, L * 2, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][3]), L * 2, L * i, L * 3, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][4]), L * 3, L * i, L * 4, L * (i + 1));
                    if (a[i + 1][4] == 2048)
                        a[0][0] = 2048;
                }
                else if (a[i + 1][2] == a[i + 1][1] && a[i + 1][4] != 0 && a[i + 1][1] != 0 && a[i + 1][2] != a[i + 1][4] && a[i + 1][3] == 0) /// CASE 21
                {
                    s[i] = 1;
                    a[i + 1][3] = 2 * a[i + 1][2];
                    a[i + 1][1] = 0;
                    a[i + 1][2] = 0;
                    readimagefile("0.jpg", 0, L * i, L, L * (i + 1));
                    readimagefile("0.jpg", L, L * i, L * 2, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][3]), L * 2, L * i, L * 3, L * (i + 1));
                    if (a[i + 1][3] == 2048)
                        a[0][0] = 2048;
                }
                else if (a[i + 1][4] != 0 && a[i + 1][3] == 0 && a[i + 1][2] != a[i + 1][4] && a[i + 1][2] != a[i + 1][1] && a[i + 1][2] != 0) /// CASE 22
                {
                    s[i] = 1;
                    a[i + 1][3] = a[i + 1][2];
                    a[i + 1][2] = a[i + 1][1];
                    a[i + 1][1] = 0;
                    readimagefile("0.jpg", 0, L * i, L, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][2]), L, L * i, L * 2, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][3]), L * 2, L * i, L * 3, L * (i + 1));
                }
                else if (a[i + 1][2] == a[i + 1][3] && a[i + 1][4] == 0 && a[i + 1][2] != 0) /// CASE 23
                {
                    s[i] = 1;
                    a[i + 1][4] = 2 * a[i + 1][3];
                    a[i + 1][3] = a[i + 1][1];
                    a[i + 1][2] = 0;
                    a[i + 1][1] = 0;
                    readimagefile("0.jpg", L, L * i, L * 2, L * (i + 1));
                    readimagefile("0.jpg", 0, L * i, L, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][3]), L * 2, L * i, L * 3, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][4]), L * 3, L * i, L * 4, L * (i + 1));
                    if (a[i + 1][4] == 2048)
                        a[0][0] = 2048;
                }
                else if (a[i + 1][1] == a[i + 1][2] && a[i + 1][2] != 0 && a[i + 1][3] != a[i + 1][2] && a[i + 1][4] == 0 && a[i + 1][3] != 0) /// CASE 24
                {
                    s[i] = 1;
                    a[i + 1][4] = a[i + 1][3];
                    a[i + 1][3] = a[i + 1][2] * 2;
                    a[i + 1][2] = 0;
                    a[i + 1][1] = 0;
                    readimagefile("0.jpg", L, L * i, L * 2, L * (i + 1));
                    readimagefile("0.jpg", 0, L * i, L, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][3]), L * 2, L * i, L * 3, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][4]), L * 3, L * i, L * 4, L * (i + 1));
                    if (a[i + 1][3] == 2048)
                        a[0][0] = 2048;
                }
                else if (a[i + 1][4] == 0 && a[i + 1][3] != 0 && a[i + 1][2] != a[i + 1][3] && (a[i + 1][2] != 0 && a[i + 1][2] != a[i + 1][1] || a[i + 1][2] == 0 && a[i + 1][1] == 0)) /// CASE 25
                {
                    s[i] = 1;
                    a[i + 1][4] = a[i + 1][3];
                    a[i + 1][3] = a[i + 1][2];
                    a[i + 1][2] = a[i + 1][1];
                    a[i + 1][1] = 0;
                    readimagefile("0.jpg", 0, L * i, L, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][2]), L, L * i, L * 2, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][3]), L * 2, L * i, L * 3, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][4]), L * 3, L * i, L * 4, L * (i + 1));
                }
                else if (a[i + 1][4] == a[i + 1][3] && a[i + 1][3] != 0 && a[i + 1][2] != 0 && a[i + 1][1] != a[i + 1][2]) /// CASE 26
                {
                    s[i] = 1;
                    a[i + 1][4] = 2 * a[i + 1][3];
                    a[i + 1][3] = a[i + 1][2];
                    a[i + 1][2] = a[i + 1][1];
                    a[i + 1][1] = 0;
                    readimagefile("0.jpg", 0, L * i, L, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][2]), L, L * i, L * 2, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][3]), L * 2, L * i, L * 3, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][4]), L * 3, L * i, L * 4, L * (i + 1));
                    if (a[i + 1][4] == 2048)
                        a[0][0] = 2048;
                }
                else if (a[i + 1][2] == a[i + 1][3] && a[i + 1][4] != 0 && a[i + 1][2] != 0 && a[i + 1][2] != a[i + 1][4]) /// CASE 27
                {
                    s[i] = 1;
                    a[i + 1][3] = 2 * a[i + 1][3];
                    a[i + 1][2] = a[i + 1][1];
                    a[i + 1][1] = 0;
                    readimagefile("0.jpg", 0, L * i, L, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][2]), L, L * i, L * 2, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][3]), L * 2, L * i, L * 3, L * (i + 1));
                    if (a[i + 1][3] == 2048)
                        a[0][0] = 2048;
                }
                else if (a[i + 1][4] != 0 && a[i + 1][3] != 0 && a[i + 1][2] != a[i + 1][3] && a[i + 1][2] == a[i + 1][1] && a[i + 1][4] != a[i + 1][3] && a[i + 1][2] != 0) /// CASE 28
                {
                    s[i] = 1;
                    a[i + 1][2] = a[i + 1][2] * 2;
                    a[i + 1][1] = 0;
                    readimagefile("0.jpg", 0, L * i, L, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][2]), L, L * i, L * 2, L * (i + 1));
                    if (a[i + 1][2] == 2048)
                        a[0][0] = 2048;
                }
                else if (a[i + 1][4] == a[i + 1][3] && a[i + 1][4] != 0 && a[i + 1][2] == a[i + 1][1]) /// CASE 29
                {
                    s[i] = 1;
                    a[i + 1][4] = a[i + 1][4] * 2;
                    a[i + 1][3] = a[i + 1][2] * 2;
                    a[i + 1][2] = 0;
                    a[i + 1][1] = 0;
                    readimagefile("0.jpg", 0, L * i, L * 1, L * (i + 1));
                    readimagefile("0.jpg", L, L * i, L * 2, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][3]), L * 2, L * i, L * 3, L * (i + 1));
                    readimagefile(ImageName(a[i + 1][4]), L * 3, L * i, L * 4, L * (i + 1));
                    if (a[i + 1][4] == 2048 || a[i + 1][3] == 2048)
                        a[0][0] = 2048;
                }
            }
            Populate(a, s, L);
            UpdateGameStatus(a, L);
        }
        else if (ch == KEY_UP)
        {

            for (j = 0; j < 4; j++)
            {
                s[j] = 0;
                if (a[1][j + 1] == 0 && a[2][j + 1] == 0 && a[3][j + 1] == 0 && a[4][j + 1] != 0) /// CASE 1
                {
                    s[j] = 1;
                    a[1][j + 1] = a[4][j + 1];
                    a[4][j + 1] = 0;
                    readimagefile("0.jpg", L * j, L * 3, L * (j + 1), L * 4);
                    readimagefile(ImageName(a[1][j + 1]), L * j, 0, L * (j + 1), L);
                }
                /*else if (a[1][j+1]==0 && a[2][j+1]==0 && a[3][j+1]!=0 && a[4][j+1]==0)///CASE 2
                {
                    s[j]=1;
                    a[1][j+1]=a[3][j+1];
                    a[3][j+1]=0;
                    readimagefile("0.jpg",L*j,L*2,L*(j+1),L*3);
                    readimagefile(ImageName(a[1][j+1]),L*j,0,L*(j+1),L);



                }*/
                /*else if (a[1][j+1]==0 && a[2][j+1]!=0 && a[3][j+1]==0 && a[4][j+1]==0)///CASE 3
                {
                    s[j]=1;
                    a[1][j+1]=a[2][j+1];
                    a[2][j+1]=0;
                    readimagefile("0.jpg",L*j,L,L*(j+1),L*2);
                    readimagefile(ImageName(a[1][j+1]),L*j,0,L*(j+1),L);

                }*/
                /*else if(a[1][j+1]==a[2][j+1] && a[2][j+1]!=0 && a[3][j+1]==0 && a[4][j+1]==0)///CASE 4
                {
                    s[j]=1;
                    a[1][j+1]=2*a[2][j+1];
                    a[2][j+1]=0;
                    readimagefile("0.jpg",L*j,L,L*(j+1),L*2);
                    readimagefile(ImageName(a[1][j+1]),L*j,0,L*(j+1),L);
                    if(a[1][j+1]==2048)
                       a[0][0]=2048;
                }*/
                /*else if(a[1][j+1]==a[3][j+1] && a[3][j+1]!=0 && a[2][j+1]==0 && a[4][j+1]==0)///CASE 5
                {
                    s[j]=1;
                    a[1][j+1]=2*a[3][j+1];
                    a[3][j+1]=0;
                    readimagefile("0.jpg",L*j,L*2,L*(j+1),L*3);
                    readimagefile(ImageName(a[1][j+1]),L*j,0,L*(j+1),L);
                    if(a[1][j+1]==2048)
                        a[0][0]=2048;


                }*/
                else if (a[1][j + 1] == a[4][j + 1] && a[4][j + 1] != 0 && a[2][j + 1] == 0 && a[3][j + 1] == 0) /// CASE 6
                {
                    s[j] = 1;
                    a[1][j + 1] = 2 * a[4][j + 1];
                    a[4][j + 1] = 0;
                    readimagefile("0.jpg", L * j, L * 3, L * (j + 1), L * 4);
                    readimagefile(ImageName(a[1][j + 1]), L * j, 0, L * (j + 1), L);
                    if (a[1][j + 1] == 2048)
                        a[0][0] = 2048;
                }
                /*else if(a[2][j+1]==a[3][j+1] && a[3][j+1]!=0 && a[1][j+1]==0 && a[4][j+1]==0)///CASE 7
                {
                    s[j]=1;
                    a[1][j+1]=2*a[2][j+1];
                    a[2][j+1]=0;
                    a[3][j+1]=0;
                    readimagefile("0.jpg",L*j,L,L*(j+1),L*2);
                    readimagefile("0.jpg",L*j,L*2,L*(j+1),L*3);
                    readimagefile(ImageName(a[1][j+1]),L*j,0,L*(j+1),L);
                    if(a[1][j+1]==2048)
                        a[0][0]=2048;

                }*/
                else if (a[2][j + 1] == a[4][j + 1] && a[4][j + 1] != 0 && a[3][j + 1] == 0 && a[1][j + 1] == 0) /// CASE 8
                {
                    s[j] = 1;
                    a[1][j + 1] = 2 * a[2][j + 1];
                    a[2][j + 1] = 0;
                    a[4][j + 1] = 0;
                    readimagefile("0.jpg", L * j, L, L * (j + 1), L * 2);
                    readimagefile("0.jpg", L * j, L * 3, L * (j + 1), L * 4);
                    readimagefile(ImageName(a[1][j + 1]), L * j, 0, L * (j + 1), L);
                    if (a[1][j + 1] == 2048)
                        a[0][0] = 2048;
                }
                else if (a[3][j + 1] == a[4][j + 1] && a[4][j + 1] != 0 && a[2][j + 1] == 0 && a[1][j + 1] == 0) /// CASE 9
                {
                    s[j] = 1;
                    a[1][j + 1] = 2 * a[3][j + 1];
                    a[3][j + 1] = 0;
                    a[4][j + 1] = 0;
                    readimagefile("0.jpg", L * j, L * 2, L * (j + 1), L * 3);
                    readimagefile("0.jpg", L * j, L * 3, L * (j + 1), L * 4);
                    readimagefile(ImageName(a[1][j + 1]), L * j, 0, L * (j + 1), L);
                    if (a[1][j + 1] == 2048)
                        a[0][0] = 2048;
                }
                /*else if (a[1][j+1]!=0 && a[2][j+1]==0 && a[3][j+1]!=0 && a[4][j+1]==0 && a[1][j+1]!=a[3][j+1])///CASE 10
                {
                    s[j]=1;
                    a[2][j+1]=a[3][j+1];
                    a[3][j+1]=0;
                    readimagefile("0.jpg",L*j,L*2,L*(j+1),L*3);
                    readimagefile(ImageName(a[2][j+1]),L*j,L,L*(j+1),L*2);


                }*/
                else if (a[1][j + 1] != 0 && a[2][j + 1] == 0 && a[3][j + 1] == 0 && a[4][j + 1] != 0 && a[4][j + 1] != a[1][j + 1]) /// CASE 11
                {
                    s[j] = 1;
                    a[2][j + 1] = a[4][j + 1];
                    a[4][j + 1] = 0;
                    readimagefile("0.jpg", L * j, L * 3, L * (j + 1), L * 4);
                    readimagefile(ImageName(a[2][j + 1]), L * j, L, L * (j + 1), L * 2);
                }
                /*else if (a[1][j+1]==0 && a[2][j+1]!=0 && a[3][j+1]!=0 && a[4][j+1]==0 && a[2][j+1]!=a[3][j+1])///CASE 12
                {
                    s[j]=1;
                    a[1][j+1]=a[2][j+1];
                    a[2][j+1]=a[3][j+1];
                    a[3][j+1]=0;
                    readimagefile("0.jpg",L*j,L*2,L*(j+1),L*3);
                    readimagefile(ImageName(a[2][j+1]),L*j,L,L*(j+1),L*2);
                    readimagefile(ImageName(a[1][j+1]),L*j,0,L*(j+1),L);

                }*/
                else if (a[1][j + 1] == 0 && a[2][j + 1] != 0 && a[3][j + 1] == 0 && a[4][j + 1] != 0 && a[4][j + 1] != a[2][j + 1]) /// CASE 13
                {
                    s[j] = 1;
                    a[1][j + 1] = a[2][j + 1];
                    a[2][j + 1] = a[4][j + 1];
                    a[4][j + 1] = 0;
                    readimagefile("0.jpg", L * j, L * 3, L * (j + 1), L * 4);
                    readimagefile(ImageName(a[1][j + 1]), L * j, 0, L * (j + 1), L);
                    readimagefile(ImageName(a[2][j + 1]), L * j, L, L * (j + 1), L * 2);
                }
                else if (a[1][j + 1] == 0 && a[2][j + 1] == 0 && a[3][j + 1] != 0 && a[3][j + 1] != a[4][j + 1]) /// CASE 14
                {
                    s[j] = 1;
                    a[1][j + 1] = a[3][j + 1];
                    a[2][j + 1] = a[4][j + 1];
                    a[3][j + 1] = 0;
                    readimagefile("0.jpg", L * j, L * 2, L * (j + 1), L * 3);
                    if (a[4][j + 1] != 0)
                    {
                        a[4][j + 1] = 0;
                        readimagefile("0.jpg", L * j, L * 3, L * (j + 1), L * 4);
                    }
                    readimagefile(ImageName(a[1][j + 1]), L * j, 0, L * (j + 1), L);
                    readimagefile(ImageName(a[2][j + 1]), L * j, L, L * (j + 1), L * 2);
                }
                /*else if(a[1][j+1]==a[2][j+1] && a[2][j+1]!=0 && a[3][j+1]!=0 && a[4][j+1]==0 )///CASE 15
                {
                    s[j]=1;
                    a[1][j+1]=2*a[2][j+1];
                    a[2][j+1]=a[3][j+1];
                    a[3][j+1]=0;
                    readimagefile("0.jpg",L*j,L*2,L*(j+1),L*3);
                    readimagefile(ImageName(a[1][j+1]),L*j,0,L*(j+1),L);
                    readimagefile(ImageName(a[2][j+1]),L*j,L,L*(j+1),L*2);
                    if(a[1][j+1]==2048)
                        a[0][0]=2048;


                }*/
                /*else if(a[2][j+1]==a[3][j+1] && a[1][j+1]!=0 && a[3][j+1]!=0 && a[3][j+1]!=a[1][j+1] && a[4][j+1]==0)///CASE 16
                {
                    s[j]=1;
                    a[2][j+1]=2*a[2][j+1];
                    a[3][j+1]=0;
                    readimagefile("0.jpg",L*j,L*2,L*(j+1),L*3);
                    readimagefile(ImageName(a[2][j+1]),L*j,L,L*(j+1),L*2);
                    if(a[2][j+1]==2048)
                       a[0][0]=2048;

                }*/
                else if (a[2][j + 1] == a[4][j + 1] && a[1][j + 1] != 0 && a[4][j + 1] != 0 && a[2][j + 1] != a[1][j + 1] && a[3][j + 1] == 0) /// CASE 17
                {
                    s[j] = 1;
                    a[2][j + 1] = 2 * a[2][j + 1];
                    a[4][j + 1] = 0;
                    readimagefile("0.jpg", L * j, L * 3, L * (j + 1), L * 4);
                    readimagefile(ImageName(a[2][j + 1]), L * j, L, L * (j + 1), L * 2);
                    if (a[2][j + 1] == 2048)
                        a[0][0] = 2048;
                }
                else if (a[1][j + 1] == a[2][j + 1] && a[2][j + 1] != 0 && a[3][j + 1] == 0 && a[4][j + 1] != 0) /// CASE 18
                {
                    s[j] = 1;
                    a[1][j + 1] = 2 * a[2][j + 1];
                    a[2][j + 1] = a[4][j + 1];
                    a[4][j + 1] = 0;
                    readimagefile("0.jpg", L * j, L * 3, L * (j + 1), L * 4);
                    readimagefile(ImageName(a[1][j + 1]), L * j, 0, L * (j + 1), L);
                    readimagefile(ImageName(a[2][j + 1]), L * j, L, L * (j + 1), L * 2);
                    if (a[1][j + 1] == 2048)
                        a[0][0] = 2048;
                }
                else if (a[1][j + 1] != 0 && a[2][j + 1] != 0 && a[2][j + 1] != a[1][j + 1] && a[2][j + 1] != a[4][j + 1] && a[3][j + 1] == 0 && a[4][j + 1] != 0) /// CASE 19
                {
                    s[j] = 1;
                    a[3][j + 1] = a[4][j + 1];
                    a[4][j + 1] = 0;
                    readimagefile("0.jpg", L * j, L * 3, L * (j + 1), L * 4);
                    readimagefile(ImageName(a[3][j + 1]), L * j, L * 2, L * (j + 1), L * 3);
                }
                else if (a[1][j + 1] == a[3][j + 1] && a[3][j + 1] != 0 && a[2][j + 1] == 0) /// CASE 20
                {
                    s[j] = 1;
                    a[1][j + 1] = 2 * a[3][j + 1];
                    a[2][j + 1] = a[4][j + 1];
                    a[3][j + 1] = 0;
                    if (a[4][j + 1] != 0)
                    {
                        a[4][j + 1] = 0;
                        readimagefile("0.jpg", L * j, L * 3, L * (j + 1), L * 4);
                    }
                    readimagefile("0.jpg", L * j, L * 2, L * (j + 1), L * 3);
                    readimagefile(ImageName(a[2][j + 1]), L * j, L, L * (j + 1), L * 2);
                    readimagefile(ImageName(a[1][j + 1]), L * j, 0, L * (j + 1), L);
                    if (a[1][j + 1] == 2048)
                        a[0][0] = 2048;
                }
                else if (a[3][j + 1] == a[4][j + 1] && a[1][j + 1] != 0 && a[4][j + 1] != 0 && a[3][j + 1] != a[1][j + 1] && a[2][j + 1] == 0) /// CASE 21
                {
                    s[j] = 1;
                    a[2][j + 1] = 2 * a[3][j + 1];
                    a[4][j + 1] = 0;
                    a[3][j + 1] = 0;
                    readimagefile("0.jpg", L * j, L * 3, L * (j + 1), L * 4);
                    readimagefile("0.jpg", L * j, L * 2, L * (j + 1), L * 3);
                    readimagefile(ImageName(a[2][j + 1]), L * j, L, L * (j + 1), L * 2);
                    if (a[2][j + 1] == 2048)
                        a[0][0] = 2048;
                }
                else if (a[1][j + 1] != 0 && a[3][j + 1] != 0 && a[3][j + 1] != a[1][j + 1] && a[3][j + 1] != a[4][j + 1] && a[2][j + 1] == 0) /// CASE 22
                {
                    s[j] = 1;
                    a[2][j + 1] = a[3][j + 1];
                    a[3][j + 1] = a[4][j + 1];
                    if (a[4][j + 1] != 0)
                    {
                        a[4][j + 1] = 0;
                        readimagefile("0.jpg", L * j, L * 3, L * (j + 1), L * 4);
                    }
                    readimagefile(ImageName(a[2][j + 1]), L * j, L, L * (j + 1), L * 2);
                    readimagefile(ImageName(a[3][j + 1]), L * j, L * 2, L * (j + 1), L * 3);
                }
                else if (a[3][j + 1] == a[2][j + 1] && a[1][j + 1] == 0 && a[3][j + 1] != 0) /// CASE 23
                {
                    s[j] = 1;
                    a[1][j + 1] = 2 * a[2][j + 1];
                    a[2][j + 1] = a[4][j + 1];
                    a[3][j + 1] = 0;
                    if (a[4][j + 1] != 0)
                    {
                        a[4][j + 1] = 0;
                        readimagefile("0.jpg", L * j, L * 3, L * (j + 1), L * 4);
                    }
                    readimagefile("0.jpg", L * j, L * 2, L * (j + 1), L * 3);
                    readimagefile(ImageName(a[2][j + 1]), L * j, L, L * (j + 1), L * 2);
                    readimagefile(ImageName(a[1][j + 1]), L * j, 0, L * (j + 1), L);
                    if (a[1][j + 1] == 2048)
                        a[0][0] = 2048;
                }
                else if (a[4][j + 1] == a[3][j + 1] && a[3][j + 1] != 0 && a[3][j + 1] != a[2][j + 1] && a[1][j + 1] == 0 && a[2][j + 1] != 0) /// CASE 24
                {
                    s[j] = 1;
                    a[1][j + 1] = a[2][j + 1];
                    a[2][j + 1] = a[3][j + 1] * 2;
                    a[3][j + 1] = 0;
                    a[4][j + 1] = 0;
                    readimagefile("0.jpg", L * j, L * 2, L * (j + 1), L * 3);
                    readimagefile("0.jpg", L * j, L * 3, L * (j + 1), L * 4);
                    readimagefile(ImageName(a[2][j + 1]), L * j, L, L * (j + 1), L * 2);
                    readimagefile(ImageName(a[1][j + 1]), L * j, 0, L * (j + 1), L);
                    if (a[2][j + 1] == 2048)
                        a[0][0] = 2048;
                }
                else if (a[1][j + 1] == 0 && a[2][j + 1] != 0 && a[2][j + 1] != a[3][j + 1] && ((a[4][j + 1] != a[3][j + 1] && a[3][j + 1] != 0) || (a[3][j + 1] == 0 && a[4][j + 1] == 0))) /// CASE 25
                {
                    s[j] = 1;
                    a[1][j + 1] = a[2][j + 1];
                    a[2][j + 1] = a[3][j + 1];
                    a[3][j + 1] = a[4][j + 1];
                    if (a[4][j + 1] != 0)
                    {
                        a[4][j + 1] = 0;
                        readimagefile("0.jpg", L * j, L * 3, L * (j + 1), L * 4);
                    }
                    readimagefile(ImageName(a[2][j + 1]), L * j, L, L * (j + 1), L * 2);
                    readimagefile(ImageName(a[1][j + 1]), L * j, 0, L * (j + 1), L);
                    readimagefile(ImageName(a[3][j + 1]), L * j, L * 2, L * (j + 1), L * 3);
                }
                else if (a[1][j + 1] == a[2][j + 1] && a[2][j + 1] != 0 && a[3][j + 1] != 0 && a[4][j + 1] != a[3][j + 1]) /// CASE 26
                {
                    s[j] = 1;
                    a[1][j + 1] = 2 * a[2][j + 1];
                    a[2][j + 1] = a[3][j + 1];
                    a[3][j + 1] = a[4][j + 1];
                    if (a[4][j + 1] != 0)
                    {
                        a[4][j + 1] = 0;
                        readimagefile("0.jpg", L * j, L * 3, L * (j + 1), L * 4);
                    }
                    readimagefile(ImageName(a[2][j + 1]), L * j, L, L * (j + 1), L * 2);
                    readimagefile(ImageName(a[1][j + 1]), L * j, 0, L * (j + 1), L);
                    readimagefile(ImageName(a[3][j + 1]), L * j, L * 2, L * (j + 1), L * 3);
                    if (a[1][j + 1] == 2048)
                        a[0][0] = 2048;
                }
                else if (a[2][j + 1] == a[3][j + 1] && a[1][j + 1] != 0 && a[3][j + 1] != 0 && a[3][j + 1] != a[1][j + 1]) /// CASE 27
                {
                    s[j] = 1;
                    a[2][j + 1] = 2 * a[2][j + 1];
                    a[3][j + 1] = a[4][j + 1];
                    if (a[4][j + 1] != 0)
                    {
                        a[4][j + 1] = 0;
                        readimagefile("0.jpg", L * j, L * 3, L * (j + 1), L * 4);
                    }
                    readimagefile(ImageName(a[2][j + 1]), L * j, L, L * (j + 1), L * 2);
                    readimagefile(ImageName(a[3][j + 1]), L * j, L * 2, L * (j + 1), L * 3);
                    if (a[2][j + 1] == 2048)
                        a[0][0] = 2048;
                }
                else if (a[1][j + 1] != 0 && a[2][j + 1] != 0 && a[3][j + 1] != a[2][j + 1] && a[3][j + 1] == a[4][j + 1] && a[1][j + 1] != a[2][j + 1] && a[3][j + 1] != 0) /// CASE 28
                {
                    s[j] = 1;
                    a[3][j + 1] = a[3][j + 1] * 2;
                    a[4][j + 1] = 0;
                    readimagefile("0.jpg", L * j, L * 3, L * (j + 1), L * 4);
                    readimagefile(ImageName(a[3][j + 1]), L * j, L * 2, L * (j + 1), L * 3);
                    if (a[3][j + 1] == 2048)
                        a[0][0] = 2048;
                }
                else if (a[1][j + 1] == a[2][j + 1] && a[1][j + 1] != 0 && a[3][j + 1] == a[4][j + 1]) /// CASE 29
                {
                    s[j] = 1;
                    a[1][j + 1] = a[1][j + 1] * 2;
                    a[2][j + 1] = a[3][j + 1] * 2;
                    if (a[3][j + 1] != 0)
                    {
                        a[3][j + 1] = 0;
                        a[4][j + 1] = 0;
                        readimagefile("0.jpg", L * j, L * 3, L * (j + 1), L * 4);
                        readimagefile("0.jpg", L * j, L * 2, L * (j + 1), L * 3);
                    }
                    readimagefile(ImageName(a[2][j + 1]), L * j, L, L * (j + 1), L * 2);
                    readimagefile(ImageName(a[1][j + 1]), L * j, 0, L * (j + 1), L);
                    if (a[1][j + 1] == 2048 || a[2][j + 1] == 2048)
                        a[0][0] = 2048;
                }
            }
            Populate(a, s, L);
            UpdateGameStatus(a, L);
        }
        else if (ch == KEY_DOWN)
        {

            for (j = 0; j < 4; j++)
            {
                s[j] = 0;
                if (a[4][j + 1] == 0 && a[3][j + 1] == 0 && a[2][j + 1] == 0 && a[1][j + 1] != 0) /// CASE 1
                {
                    s[j] = 1;
                    a[4][j + 1] = a[1][j + 1];
                    readimagefile(ImageName(a[4][j + 1]), L * j, L * 3, L * (j + 1), L * 4);
                    a[1][j + 1] = 0;
                    readimagefile("0.jpg", L * j, 0, L * (j + 1), L);
                }
                /*else if (a[4][j+1]==0 && a[3][j+1]==0 && a[2][j+1]!=0 && a[1][j+1]==0)///CASE 2
                {
                    s[j]=1;
                    a[4][j+1]=a[2][j+1];
                    a[2][j+1]=0;
                    readimagefile("0.jpg",L*j,L,L*(j+1),L*2);
                    readimagefile(ImageName(a[4][j+1]),L*j,L*3,L*(j+1),L*4);



                }*/
                /*else if (a[1][j+1]==0 && a[3][j+1]!=0 && a[2][j+1]==0 && a[4][j+1]==0)///CASE 3
                {
                    s[j]=1;
                    a[4][j+1]=a[3][j+1];
                    a[3][j+1]=0;
                    readimagefile("0.jpg",L*j,L*2,L*(j+1),L*3);
                    readimagefile(ImageName(a[4][j+1]),L*j,L*3,L*(j+1),L*4);

                }*/
                /*else if(a[4][j+1]==a[3][j+1] && a[3][j+1]!=0 && a[2][j+1]==0 && a[1][j+1]==0)///CASE 4
                {
                    s[j]=1;
                    a[4][j+1]=2*a[3][j+1];
                    a[3][j+1]=0;
                    readimagefile("0.jpg",L*j,L*2,L*(j+1),L*3);
                    readimagefile(ImageName(a[4][j+1]),L*j,L*3,L*(j+1),L*4);
                    if(a[4][j+1]==2048)
                       a[0][0]=2048;




                }*/
                /*else if(a[4][j+1]==a[2][j+1] && a[2][j+1]!=0 && a[3][j+1]==0 && a[1][j+1]==0)///CASE 5
                {
                    s[j]=1;
                    a[4][j+1]=2*a[2][j+1];
                    a[2][j+1]=0;
                    readimagefile("0.jpg",L*j,L,L*(j+1),L*2);
                    readimagefile(ImageName(a[4][j+1]),L*j,L*3,L*(j+1),L*4);
                    if(a[4][j+1]==2048)
                       a[0][0]=2048;


                }*/
                else if (a[1][j + 1] == a[4][j + 1] && a[4][j + 1] != 0 && a[2][j + 1] == 0 && a[3][j + 1] == 0) /// CASE 6
                {
                    s[j] = 1;
                    a[4][j + 1] = 2 * a[1][j + 1];
                    readimagefile(ImageName(a[4][j + 1]), L * j, L * 3, L * (j + 1), L * 4);
                    a[1][j + 1] = 0;
                    readimagefile("0.jpg", L * j, 0, L * (j + 1), L);

                    if (a[4][j + 1] == 2048)
                        a[0][0] = 2048;
                }
                /*else if(a[2][j+1]==a[3][j+1] && a[3][j+1]!=0 && a[1][j+1]==0 && a[4][j+1]==0)///CASE 7
                {
                    s[j]=1;
                    a[4][j+1]=2*a[3][j+1];
                    a[2][j+1]=0;
                    a[3][j+1]=0;
                    readimagefile("0.jpg",L*j,L,L*(j+1),L*2);
                    readimagefile("0.jpg",L*j,L*2,L*(j+1),L*3);
                    readimagefile(ImageName(a[4][j+1]),L*j,L*3,L*(j+1),L*4);
                    if(a[4][j+1]==2048)
                       a[0][0]=2048;


                }*/
                else if (a[3][j + 1] == a[1][j + 1] && a[1][j + 1] != 0 && a[2][j + 1] == 0 && a[4][j + 1] == 0) /// CASE 8
                {
                    s[j] = 1;
                    a[4][j + 1] = 2 * a[3][j + 1];
                    readimagefile(ImageName(a[4][j + 1]), L * j, L * 3, L * (j + 1), L * 4);
                    a[3][j + 1] = 0;
                    readimagefile("0.jpg", L * j, L * 2, L * (j + 1), L * 3);
                    a[1][j + 1] = 0;
                    readimagefile("0.jpg", L * j, 0, L * (j + 1), L);

                    if (a[4][j + 1] == 2048)
                        a[0][0] = 2048;
                }
                else if (a[2][j + 1] == a[1][j + 1] && a[1][j + 1] != 0 && a[3][j + 1] == 0 && a[4][j + 1] == 0) /// CASE 9
                {
                    s[j] = 1;
                    a[4][j + 1] = 2 * a[2][j + 1];
                    readimagefile(ImageName(a[4][j + 1]), L * j, L * 3, L * (j + 1), L * 4);
                    a[2][j + 1] = 0;
                    readimagefile("0.jpg", L * j, L, L * (j + 1), L * 2);
                    a[1][j + 1] = 0;
                    readimagefile("0.jpg", L * j, 0, L * (j + 1), L);

                    if (a[4][j + 1] == 2048)
                        a[0][0] = 2048;
                }
                /*else if (a[4][j+1]!=0 && a[3][j+1]==0 && a[2][j+1]!=0 && a[1][j+1]==0 && a[4][j+1]!=a[2][j+1])///CASE 10
                {
                    s[j]=1;
                    a[3][j+1]=a[2][j+1];
                    a[2][j+1]=0;
                    readimagefile("0.jpg",L*j,L,L*(j+1),L*2);
                    readimagefile(ImageName(a[3][j+1]),L*j,L*2,L*(j+1),L*3);


                }*/
                else if (a[4][j + 1] != 0 && a[3][j + 1] == 0 && a[2][j + 1] == 0 && a[1][j + 1] != 0 && a[4][j + 1] != a[1][j + 1]) /// CASE 11
                {
                    s[j] = 1;
                    a[3][j + 1] = a[1][j + 1];
                    readimagefile(ImageName(a[3][j + 1]), L * j, L * 2, L * (j + 1), L * 3);
                    a[1][j + 1] = 0;
                    readimagefile("0.jpg", L * j, 0, L * (j + 1), L);
                }
                /*else if (a[1][j+1]==0 && a[2][j+1]!=0 && a[3][j+1]!=0 && a[4][j+1]==0 && a[2][j+1]!=a[3][j+1])///CASE 12
                {
                    s[j]=1;
                    a[4][j+1]=a[3][j+1];
                    a[3][j+1]=a[2][j+1];
                    a[2][j+1]=0;
                    readimagefile("0.jpg",L*j,L,L*(j+1),L*2);
                    readimagefile(ImageName(a[3][j+1]),L*j,L*2,L*(j+1),L*3);
                    readimagefile(ImageName(a[4][j+1]),L*j,L*3,L*(j+1),L*4);

                }*/
                else if (a[4][j + 1] == 0 && a[3][j + 1] != 0 && a[2][j + 1] == 0 && a[1][j + 1] != 0 && a[1][j + 1] != a[3][j + 1]) /// CASE 13
                {
                    s[j] = 1;
                    a[4][j + 1] = a[3][j + 1];
                    readimagefile(ImageName(a[4][j + 1]), L * j, L * 3, L * (j + 1), L * 4);
                    a[3][j + 1] = a[1][j + 1];
                    readimagefile(ImageName(a[3][j + 1]), L * j, L * 2, L * (j + 1), L * 3);
                    a[1][j + 1] = 0;
                    readimagefile("0.jpg", L * j, 0, L * (j + 1), L);
                }
                else if (a[4][j + 1] == 0 && a[3][j + 1] == 0 && a[2][j + 1] != 0 && a[2][j + 1] != a[1][j + 1]) /// CASE 14
                {
                    s[j] = 1;
                    a[4][j + 1] = a[2][j + 1];
                    readimagefile(ImageName(a[4][j + 1]), L * j, L * 3, L * (j + 1), L * 4);
                    a[3][j + 1] = a[1][j + 1];
                    readimagefile(ImageName(a[3][j + 1]), L * j, L * 2, L * (j + 1), L * 3);
                    a[2][j + 1] = 0;
                    readimagefile("0.jpg", L * j, L, L * (j + 1), L * 2);
                    if (a[1][j + 1] != 0)
                    {
                        readimagefile("0.jpg", L * j, 0, L * (j + 1), L);
                        a[1][j + 1] = 0;
                    }
                }
                /*else if(a[4][j+1]==a[3][j+1] && a[3][j+1]!=0 && a[2][j+1]!=0 && a[1][j+1]==0 )///CASE 15
                {
                    s[j]=1;
                    a[4][j+1]=2*a[3][j+1];
                    a[3][j+1]=a[2][j+1];
                    a[2][j+1]=0;
                    readimagefile("0.jpg",L*j,L,L*(j+1),L*2);
                    readimagefile(ImageName(a[3][j+1]),L*j,L*2,L*(j+1),L*3);
                    readimagefile(ImageName(a[4][j+1]),L*j,L*3,L*(j+1),L*4);
                    if(a[4][j+1]==2048)
                      a[0][0]=2048;



                }*/
                /*else if(a[2][j+1]==a[3][j+1] && a[4][j+1]!=0 && a[3][j+1]!=0 && a[3][j+1]!=a[4][j+1] && a[1][j+1]==0)///CASE 16
                {
                    s[j]=1;
                    a[3][j+1]=2*a[2][j+1];
                    a[2][j+1]=0;
                    readimagefile("0.jpg",L*j,L,L*(j+1),L*2);
                    readimagefile(ImageName(a[3][j+1]),L*j,L*2,L*(j+1),L*3);
                    if(a[3][j+1]==2048)
                        a[0][0]=2048;

                }*/
                else if (a[3][j + 1] == a[1][j + 1] && a[4][j + 1] != 0 && a[1][j + 1] != 0 && a[3][j + 1] != a[4][j + 1] && a[2][j + 1] == 0) /// CASE 17
                {
                    s[j] = 1;
                    a[3][j + 1] = 2 * a[3][j + 1];
                    readimagefile(ImageName(a[3][j + 1]), L * j, L * 2, L * (j + 1), L * 3);
                    a[1][j + 1] = 0;
                    readimagefile("0.jpg", L * j, 0, L * (j + 1), L);

                    if (a[3][j + 1] == 2048)
                        a[0][0] = 2048;
                }
                else if (a[4][j + 1] == a[3][j + 1] && a[3][j + 1] != 0 && a[2][j + 1] == 0 && a[1][j + 1] != 0) /// CASE 18
                {
                    s[j] = 1;
                    a[4][j + 1] = 2 * a[3][j + 1];
                    readimagefile(ImageName(a[4][j + 1]), L * j, L * 3, L * (j + 1), L * 4);
                    a[3][j + 1] = a[1][j + 1];
                    readimagefile(ImageName(a[3][j + 1]), L * j, L * 2, L * (j + 1), L * 3);
                    a[1][j + 1] = 0;
                    readimagefile("0.jpg", L * j, 0, L * (j + 1), L);
                    if (a[4][j + 1] == 2048)
                        a[0][0] = 2048;
                }
                else if (a[4][j + 1] != 0 && a[3][j + 1] != 0 && a[3][j + 1] != a[4][j + 1] && a[3][j + 1] != a[1][j + 1] && a[2][j + 1] == 0 && a[1][j + 1] != 0) /// CASE 19
                {
                    s[j] = 1;
                    a[2][j + 1] = a[1][j + 1];
                    readimagefile(ImageName(a[2][j + 1]), L * j, L, L * (j + 1), L * 2);
                    a[1][j + 1] = 0;
                    readimagefile("0.jpg", L * j, 0, L * (j + 1), L);
                }
                else if (a[4][j + 1] == a[2][j + 1] && a[2][j + 1] != 0 && a[3][j + 1] == 0) /// CASE 20
                {
                    s[j] = 1;
                    a[4][j + 1] = 2 * a[2][j + 1];
                    readimagefile(ImageName(a[4][j + 1]), L * j, L * 3, L * (j + 1), L * 4);
                    a[3][j + 1] = a[1][j + 1];
                    readimagefile(ImageName(a[3][j + 1]), L * j, L * 2, L * (j + 1), L * 3);
                    a[2][j + 1] = 0;
                    readimagefile("0.jpg", L * j, L, L * (j + 1), L * 2);
                    if (a[1][j + 1] != 0)
                    {
                        a[1][j + 1] = 0;
                        readimagefile("0.jpg", L * j, 0, L * (j + 1), L);
                    }

                    if (a[4][j + 1] == 2048)
                        a[0][0] = 2048;
                }
                else if (a[2][j + 1] == a[1][j + 1] && a[4][j + 1] != 0 && a[1][j + 1] != 0 && a[2][j + 1] != a[4][j + 1] && a[3][j + 1] == 0) /// CASE 21
                {
                    s[j] = 1;
                    a[3][j + 1] = 2 * a[2][j + 1];
                    readimagefile(ImageName(a[3][j + 1]), L * j, L * 2, L * (j + 1), L * 3);
                    a[2][j + 1] = 0;
                    readimagefile("0.jpg", L * j, L, L * (j + 1), L * 2);
                    a[1][j + 1] = 0;
                    readimagefile("0.jpg", L * j, 0, L * (j + 1), L);
                    if (a[3][j + 1] == 2048)
                        a[0][0] = 2048;
                }
                else if (a[4][j + 1] != 0 && a[2][j + 1] != 0 && a[2][j + 1] != a[4][j + 1] && a[2][j + 1] != a[1][j + 1] && a[3][j + 1] == 0) /// CASE 22
                {
                    s[j] = 1;
                    a[3][j + 1] = a[2][j + 1];
                    readimagefile(ImageName(a[3][j + 1]), L * j, L * 2, L * (j + 1), L * 3);
                    a[2][j + 1] = a[1][j + 1];
                    readimagefile(ImageName(a[2][j + 1]), L * j, L, L * (j + 1), L * 2);
                    if (a[1][j + 1] != 0)
                    {
                        a[1][j + 1] = 0;
                        readimagefile("0.jpg", L * j, 0, L * (j + 1), L);
                    }
                }
                else if (a[3][j + 1] == a[2][j + 1] && a[4][j + 1] == 0 && a[2][j + 1] != 0) /// CASE 23
                {
                    s[j] = 1;
                    a[4][j + 1] = 2 * a[3][j + 1];
                    readimagefile(ImageName(a[4][j + 1]), L * j, L * 3, L * (j + 1), L * 4);
                    a[3][j + 1] = a[1][j + 1];
                    readimagefile(ImageName(a[3][j + 1]), L * j, L * 2, L * (j + 1), L * 3);
                    a[2][j + 1] = 0;
                    readimagefile("0.jpg", L * j, L, L * (j + 1), L * 2);
                    if (a[1][j + 1] != 0)
                    {
                        a[1][j + 1] = 0;
                        readimagefile("0.jpg", L * j, 0, L * (j + 1), L);
                    }

                    if (a[4][j + 1] == 2048)
                        a[0][0] = 2048;
                }
                else if (a[1][j + 1] == a[2][j + 1] && a[2][j + 1] != 0 && a[3][j + 1] != a[2][j + 1] && a[4][j + 1] == 0 && a[3][j + 1] != 0) /// CASE 24
                {
                    s[j] = 1;
                    a[4][j + 1] = a[3][j + 1];
                    readimagefile(ImageName(a[4][j + 1]), L * j, L * 3, L * (j + 1), L * 4);
                    a[3][j + 1] = a[2][j + 1] * 2;
                    readimagefile(ImageName(a[3][j + 1]), L * j, L * 2, L * (j + 1), L * 3);
                    a[2][j + 1] = 0;
                    readimagefile("0.jpg", L * j, L, L * (j + 1), L * 2);
                    a[1][j + 1] = 0;
                    readimagefile("0.jpg", L * j, 0, L * (j + 1), L);
                    if (a[3][j + 1] == 2048)
                        a[0][0] = 2048;
                }
                else if (a[4][j + 1] == 0 && a[3][j + 1] != 0 && a[3][j + 1] != a[2][j + 1] && ((a[2][j + 1] != 0 && a[1][j + 1] != a[2][j + 1]) || (a[1][j + 1] == 0 && a[2][j + 1] == 0))) /// CASE 25
                {
                    s[j] = 1;
                    a[4][j + 1] = a[3][j + 1];
                    readimagefile(ImageName(a[4][j + 1]), L * j, L * 3, L * (j + 1), L * 4);
                    a[3][j + 1] = a[2][j + 1];
                    readimagefile(ImageName(a[3][j + 1]), L * j, L * 2, L * (j + 1), L * 3);
                    if (a[2][j + 1] != 0)
                    {
                        a[2][j + 1] = a[1][j + 1];
                        readimagefile(ImageName(a[2][j + 1]), L * j, L, L * (j + 1), L * 2);
                    }

                    if (a[1][j + 1] != 0)
                    {
                        a[1][j + 1] = 0;
                        readimagefile("0.jpg", L * j, 0, L * (j + 1), L);
                    }
                }
                else if (a[4][j + 1] == a[3][j + 1] && a[3][j + 1] != 0 && a[2][j + 1] != 0 && a[1][j + 1] != a[2][j + 1]) /// CASE 26
                {
                    s[j] = 1;
                    a[4][j + 1] = 2 * a[3][j + 1];
                    readimagefile(ImageName(a[4][j + 1]), L * j, L * 3, L * (j + 1), L * 4);
                    a[3][j + 1] = a[2][j + 1];
                    readimagefile(ImageName(a[3][j + 1]), L * j, L * 2, L * (j + 1), L * 3);
                    a[2][j + 1] = a[1][j + 1];
                    readimagefile(ImageName(a[2][j + 1]), L * j, L, L * (j + 1), L * 2);
                    if (a[1][j + 1] != 0)
                    {
                        a[1][j + 1] = 0;
                        readimagefile("0.jpg", L * j, 0, L * (j + 1), L);
                    }
                    if (a[4][j + 1] == 2048)
                        a[0][0] = 2048;
                }
                else if (a[2][j + 1] == a[3][j + 1] && a[4][j + 1] != 0 && a[3][j + 1] != 0 && a[2][j + 1] != a[4][j + 1]) /// CASE 27
                {
                    s[j] = 1;
                    a[3][j + 1] = 2 * a[3][j + 1];
                    readimagefile(ImageName(a[3][j + 1]), L * j, L * 2, L * (j + 1), L * 3);
                    a[2][j + 1] = a[1][j + 1];
                    readimagefile(ImageName(a[2][j + 1]), L * j, L, L * (j + 1), L * 2);
                    if (a[1][j + 1] != 0)
                    {
                        a[1][j + 1] = 0;
                        readimagefile("0.jpg", L * j, 0, L * (j + 1), L);
                    }

                    if (a[3][j + 1] == 2048)
                        a[0][0] = 2048;
                }
                else if (a[4][j + 1] != 0 && a[3][j + 1] != 0 && a[3][j + 1] != a[2][j + 1] && a[2][j + 1] == a[1][j + 1] && a[4][j + 1] != a[3][j + 1] && a[2][j + 1] != 0) /// CASE 28
                {
                    s[j] = 1;
                    a[2][j + 1] = a[2][j + 1] * 2;
                    readimagefile(ImageName(a[2][j + 1]), L * j, L, L * (j + 1), L * 2);
                    a[1][j + 1] = 0;
                    readimagefile("0.jpg", L * j, 0, L * (j + 1), L);
                    if (a[2][j + 1] == 2048)
                        a[0][0] = 2048;
                }
                else if (a[4][j + 1] == a[3][j + 1] && a[4][j + 1] != 0 && a[2][j + 1] == a[1][j + 1]) /// CASE 29
                {
                    s[j] = 1;
                    a[4][j + 1] = a[4][j + 1] * 2;
                    readimagefile(ImageName(a[4][j + 1]), L * j, L * 3, L * (j + 1), L * 4);
                    a[3][j + 1] = a[2][j + 1] * 2;
                    readimagefile(ImageName(a[3][j + 1]), L * j, L * 2, L * (j + 1), L * 3);
                    if (a[2][j + 1] != 0)
                    {
                        a[2][j + 1] = 0;
                        a[1][j + 1] = 0;
                        readimagefile("0.jpg", L * j, L, L * (j + 1), L * 2);
                        readimagefile("0.jpg", L * j, 0, L * (j + 1), L);
                    }
                    if (a[4][j + 1] == 2048 || a[3][j + 1] == 2048)
                        a[0][0] = 2048;
                }
            }
            Populate(a, s, L);
            UpdateGameStatus(a, L);
        }
    }
    return 0;
}
