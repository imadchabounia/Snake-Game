#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
using namespace std;

bool gameOver;
//now we need to draw the map by specifying dimensions
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail = 0;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void Setup(void){
    gameOver = false;
    dir = STOP;
    // the snake initially at the middle of the map(board)
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Draw(void){

    system("cls"); // system("clear") on linux
    
    cout << "Score: " << score << endl;

    for(int i = 0; i < width+2; i++){
        cout << "#";
    }
    cout << endl;
    for(int i = 0; i < height; i++){

        for(int j = 0; j < width; j++){
            
            if(j == 0){
                cout << "#";
            }

            if(i == x && j == y){
                cout << "O";
            }else if(i == fruitX && j == fruitY){
                cout << "F";            
            }else{
                bool print = false;
                for(int k = 0; k < nTail; k++){
                    if(tailX[k] == i && tailY[k] == j){
                        cout << "o";
                        print = true;
                    }
                }
                if(!print){
                    cout << " ";
                }
            }

            if(j == width-1){
                cout << "#";
            }

        }

        cout << endl;
    }

    for(int i = 0; i < width+2; i++){
        cout << "#";
    }
    cout << endl;
}

void Input(void){

    if(_kbhit()){ // if a button pressed
    
        switch(_getch())
        {
            case 'Z':
            dir = LEFT;
            break;

            case 'S':
            dir = RIGHT;
            break;

            case 'Q':
            dir = UP;
            break;

            case 'D':
            dir = DOWN;
            break;

            case 'X':
            gameOver = true;
            break;

            default:
            break;
        }
    }
}

void Logic(void){
    
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for(int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;

    }

    switch(dir)
    {
        case LEFT:
        x -= 1;
        break;

        case RIGHT:
        x += 1;
        break;

        case UP:
        y -= 1;
        break;

        case DOWN:
        y += 1;
        break;

        default:
        break;
    }

    if(x > width || x < 0){
        gameOver = true;
    }

    if(y > height || y < 0){
        gameOver = true;
    }

    for(int i = 0; i < nTail; i++){
        if(tailX[i] == x && tailY[i] == y){
            gameOver = true;
            break;
        }
    }

    //if we eat fruits we increase score

    if(x == fruitX && y == fruitY){
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

int main(void){

    Setup();
    
    while(!gameOver){
        Draw();
        Input();
        Logic();
    }

    return 0;
}