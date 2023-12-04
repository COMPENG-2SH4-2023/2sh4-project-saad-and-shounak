#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2,
                      mainGameMechsRef->getBoardSizeY()/2,
                      '*');
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);

    playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);

}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos()
{
    // return the reference to the playerPos arrray list
    
    return playerPosList;
    

}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic 
    char input = mainGameMechsRef->getInput();

    switch(input)
    {
        case 'w':
            if(myDir != DOWN)
                myDir = UP;
            break;
        case 'a':
            if(myDir != RIGHT)
                myDir = LEFT;
            break;
        case 's':
            if(myDir !=UP )
                myDir = DOWN;
            break;
        case 'd':
            if(myDir != RIGHT)
                myDir = RIGHT;
            break;

        default:
            break;
    }

}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    objPos currHead;
    playerPosList->getHeadElement(currHead);
    int boardSizeX = mainGameMechsRef->getBoardSizeX();
    int boardSizeY = mainGameMechsRef->getBoardSizeY();

    switch(myDir)
    {
        case UP:
            currHead.y--;
            if(currHead.y<=0){
                currHead.y = boardSizeY-2;
            }
            break;
        case DOWN:
            currHead.y++;
            if(currHead.y>boardSizeY-1){
                currHead.y = 1;
            }
            break;
        case LEFT:
            currHead.x--;
            if(currHead.x <=0){
                currHead.x = boardSizeX-2;
            }
            break;
        case RIGHT:
            currHead.x++;
            if(currHead.x >= boardSizeX-1){
                currHead.x = 1;
            }
            break;

        case STOP:
        default:
            break;
    }


    objPos foodPos;
    mainGameMechsRef->getFoodPos(foodPos);
    if (newHead.x == foodPos.x && newHead.y == foodPos.y) {
        mainGameMechsRef->incrementScore(); // Increment the score
        mainGameMechsRef->generateFood(playerPosList->getAllPos()); // Generate new food
    } else {
        playerPosList->removeTail(); 
    }
    
    playerPosList->insertHead(currHead);

}