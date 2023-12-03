#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.setObjPos(30, 7, '*')

}


Player::~Player()
{
    // delete any heap members here
}

void Player::getplayerPos(objPos &returnPos)
{
    // return the reference to the playerPos arrray list
    
    returnPos.setObjPos(playerPos.x, playerPos.y, playerPos.symbol);
    

}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic 
    char input = mainGameMechsRef->getInput();

    switch(input)
    {
        case 'w':
            if(myDir == LEFT || myDir == RIGHT || myDir == DOWN)
                myDir = UP;
            break;
        case 'a':
            if(myDir == UP || myDir == DOWN || myDir == RIGHT)
                myDir = LEFT;
            break;
        case 's':
            if(myDir == LEFT || myDir == RIGHT || myDir == UP)
                myDir = DOWN;
            break;
        case 'd':
            if(myDir == UP || myDir == DOWN || myDir == LEFT)
                myDir = RIGHT;
            break;

        default:
            break;
    }

}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic

    int boardSizeX = mainGameMechsRef->getBoardSizeX();
    int boardSizeY = mainGameMechsRef->getBoardSizeY();

    switch(myDir)
    {
        case UP:
            playerPos.y = (playerPos.y - 1 + boardSizeY) % boardSizeY;
            break;
        case DOWN:
            playerPos.y = (playerPos.y + 1) % boardSizeY;
            break;
        case LEFT:
            playerPos.x = (playerPos.x - 1 + boardSizeX) % boardSizeX;
            break;
        case RIGHT:
            playerPos.x = (playerPos.x + 1) % boardSizeX;
            break;
        case STOP:
            break;
    }

}