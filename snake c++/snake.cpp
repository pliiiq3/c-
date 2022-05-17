#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <Windows.h>

using  namespace std;

bool gameOver;
const int width = 20;
const int height =20;
int x, y, heartX, heartY;
int tailX[100], tailY[100], nTail;
enum direction { stop = 0, LEFT, RIGHT, UP, DOWN }dir;
int score;

char heart = 3;

//lavel 
int level;
int levelmine;

//mine 
int mineX[1], mineY[1];

void setupmine()
{
    mineX[level * levelmine], mineY[level * levelmine];
    for (int i = 0; i < level * 10; i++)
    {
        mineX[i] = rand() % width;
        mineY[i] = rand() % height;
    }

}

void setup()
{
    gameOver = false;
    dir = stop;
    x = width / 2;
    y = height / 2;
    heartX = rand() % width;
    heartY = rand() % height;
    score = 0;

    level = 1;
    levelmine = 5;      
    setupmine();

}




void Draw()
{
    system("cls");

    for (int i = 0; i < width + 2; i++)
        cout << '#';
    cout << endl;

    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            if (i == 0)
                cout << '#';
            if (i == x && j == y)
                cout << 'O';
            else if (i == heartX && j == heartY)
            {
                cout << heart;
            }
            else
            {
                bool ismine = 0;
                // mineX 
                for (int m = 0; m < level * levelmine; m++)
                {
                    if (i == mineX[m] && j == mineY[m])
                    {
                        cout << '*';
                        ismine = true;
                    }
                }


                //tail
                if (!ismine) 
                { 
                bool isTail = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == i && tailY[k] == j)
                    {
                        cout << 'O';
                        isTail = true;
                    }
                }
                if (!isTail)
                    cout << ' ';
                }
            }
            if (i == width - 1)
                cout << '#';    
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << '#';
    cout << endl;

    // score:
    cout << "level: " << level << " with " << level * levelmine << "mine " << endl <<  "score: " << score << endl;

}
void InPut()
{
    cout << _kbhit(); 

    if (_kbhit())
    {
        cout << _kbhit();
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }

    if (x >= width)
        x = 0;
    else if (x < 0)
        x = width - 1;

    if (y >= height)
        y = 0;
    else if (y < 0)
        y = height - 1;

}
void logic()
{
    for (int i = nTail - 1; i > 0; --i)
    {
        tailX[i] = tailX[i - 1];
        tailY[i] = tailY[i - 1];
    }

    tailX[0] = x;
    tailY[0] = y;

   switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;

    }



    if (x == heartX && y == heartY)
    {
        heartX = rand() % width;
        heartY = rand() % height;
        nTail++;
        score += 10;
    }
    else
    {
        for (int i = 0; i < level * levelmine; i++)
        {
            if (x == mineX[i] && y == mineY[i])
                gameOver = true;
        }
    }


    if (score > level*5*10)
    {
        level++;
        setupmine();
    }


}



int main()
{

   
   /*
  

    while (true)
    {
        char ch = _getch();
        cout << ch;
    }
  
   */
   
     setup();

     while (!gameOver)
     {
         Draw();
         InPut();
         logic();
         Sleep(20);
     }
     cout << "gameOver";
       
        

    // Draw();

    return 0;

}
