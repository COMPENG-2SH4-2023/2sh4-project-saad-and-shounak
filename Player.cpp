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
            if(myDir != LEFT)
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
            if(currHead.y>boardSizeY-2){
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


    objPos body;

    for (int i=1; i< playerPosList->getSize(); i++){
        playerPosList->getElement(body, i);
        if(playerPosList->getSize()<1){
            break;
        }
        if(currHead.x == body.x && currHead.y == body.y){
            mainGameMechsRef->setExitTrue();
            mainGameMechsRef->setLoseFlag();
        }
    }


    
    playerPosList->insertHead(currHead);



    objPos foodPos;
    mainGameMechsRef->getFoodPos(foodPos);
    if (currHead.x == foodPos.x && currHead.y == foodPos.y) {
        mainGameMechsRef->incrementScore(); // Increment the score
        mainGameMechsRef->generateFood(*playerPosList); // Generate new food
    } else {
        playerPosList->removeTail(); 
    }



}