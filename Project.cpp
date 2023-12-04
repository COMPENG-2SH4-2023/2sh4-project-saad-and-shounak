#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "objPosArrayList.h"
using namespace std;

#define DELAY_CONST 100000

GameMechs* myGM;
Player* myPlayer;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void DrawGameOverScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    myGM = new GameMechs();
    myPlayer = new Player (myGM);


    //this gets player pos and generates food pos
    objPos playerPosition{-1,-1,'o'};
    myGM->generateFood(*myPlayer->getPlayerPos());
    
}

void GetInput(void)
{
   myGM->getInput();
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();

    if(myGM->getLoseFlagStatus()) {
        DrawGameOverScreen(); 
        MacUILib_Delay(5000000); 
        myGM->setExitTrue(); 
    }

    myGM->clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();    

    bool drawn;
    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    objPos tempBody;
    objPos tempFoodPos;
    myGM->getFoodPos(tempFoodPos);



    int i,j;
    for(i=0; i <myGM->getBoardSizeY(); i++){
        for(j=0; j < myGM->getBoardSizeX(); j++){

            drawn = false;

            for(int k=0; k < playerBody->getSize(); k++ ){

                playerBody->getElement(tempBody, k);
                if(tempBody.x == j && tempBody.y == i){
                    MacUILib_printf("%c", tempBody.symbol);
                    drawn = true;
                    break;
                }
            }

            if(drawn) continue; // continues if player body was drawn


            if(i==0 || i == myGM->getBoardSizeY() - 1 || j==0|| j == myGM->getBoardSizeX() - 1){
                MacUILib_printf("%c", '#');
            }


            else if(i == tempFoodPos.y && j == tempFoodPos.x) {
                MacUILib_printf("%c", tempFoodPos.symbol);
                continue; 
            }


            else{
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
        
    }
}


void DrawGameOverScreen(void)
{
    MacUILib_clearScreen();
    MacUILib_printf("Game Over!\n");
    MacUILib_printf("Final Score: %d\n", myGM->getScore());
    MacUILib_printf("Press any key to exit...\n");

    while(!MacUILib_hasChar()) {
        MacUILib_Delay(100000); 
    }
}


void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
    
    delete myGM;
    delete myPlayer;


    MacUILib_uninit();
}