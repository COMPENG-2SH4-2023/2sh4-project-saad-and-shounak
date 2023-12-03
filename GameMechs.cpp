#include "GameMechs.h"
#include "MacUILib.h"
using namespace std;

GameMechs::GameMechs()    // Default constructor
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;
    boardSizeX = 30;  // default board size
    boardSizeY = 15;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    exitFlag = 0;
    loseFlag = 0;
    score = 0;
    boardSizeX = boardX;
    boardSizeY = boardY;
}

// do you need a destructor?

GameMechs::~GameMechs(){


}

bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

void GameMechs::setExitTrue()
{
    exitFlag = true;
}

bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

char GameMechs::getInput()
{
    if(MacUILib_hasChar()){
        input = MacUILib_getChar();
    }
    if(input == 27){
        GameMechs::setExitTrue();
    }
    return input;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}

int GameMechs::getScore()
{
    return score;
}

void GameMechs::incrementScore()
{
    score++;
}

void GameMechs::generateFood(objPos blockOff) {
    srand(time(NULL)); 
    do {
        foodPos.x = rand() % boardSizeX;
        foodPos.y = rand() % boardSizeY;
    } while ((foodPos.x == blockOff.x && foodPos.y == blockOff.y) || foodPos.x == 0 || foodPos.y == 0 || foodPos.x == boardSizeX - 1 || foodPos.y == boardSizeY - 1);

    foodPos.symbol = 'O'; 
}

void GameMechs::getFoodPos(objPos &returnPos) {
    returnPos = foodPos;
}








