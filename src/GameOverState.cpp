#include <GameOverState.hpp>
#include <iostream>

extern "C" {
    #include <raylib.h>
}

GameOverState::GameOverState(){

}

void GameOverState::init(){
    
}

void GameOverState::handleInput(){
    
}

void GameOverState::update(float deltaTime){
  
}

void GameOverState::render(){
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Game Over", 50, 200, 20, RED);
    EndDrawing();
}


    