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

    DrawText("Game Over", 50, 200, 20, RED);
    DrawText(TextFormat("Puntuacion: %d", puntuacion), 60, 240, 28, DARKGRAY);
    DrawText("ENTER para reiniciar", 20, 300, 18, GRAY);
    
    EndDrawing();
}


    