#include <GameOverState.hpp>
#include <iostream>
#include "StateMachine.hpp"
#include "MainGameState.hpp"
#include <memory>

extern "C" {
    #include <raylib.h>
}

GameOverState::GameOverState(int puntuacion){
    this->puntuacion = puntuacion; 

}   

GameOverState::GameOverState(){

}

void GameOverState::init(){
    gameOverSprite = LoadTexture("assets/gameover.png"); 
}   

void GameOverState::handleInput(){
    if (IsKeyPressed(KEY_ENTER)){                                                   //Si pulso espacio cambio de nuevo a volver a jugar
        state_machine->add_state(std::make_unique<MainGameState>(), true);
    }
}

void GameOverState::update(float deltaTime){
  
}

void GameOverState::render(){
    BeginDrawing();
    ClearBackground(RAYWHITE);

    //pongo game over con el sprite de Png gameover.png
    DrawTextureEx(this->gameOverSprite, {50, 100}, 0.f, 1.0f, WHITE);
    //muestro la puntuacion obtenida    
    DrawText(TextFormat("Puntuacion: %d", puntuacion), 60, 240, 28, RED);
    DrawText("ENTER para reiniciar", 20, 300, 18, BLACK);
        
    EndDrawing();
}



    