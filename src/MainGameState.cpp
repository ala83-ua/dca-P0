#include <MainGameState.hpp>
#include <iostream>
#include "StateMachine.hpp"
#include "GameOverState.hpp"
#include <memory>
#include <string>

extern "C" {
    #include <raylib.h>
}



MainGameState::MainGameState()
{
    
}

void MainGameState::init()
{
    player.x = 200;
    player.y = 200;
}

void MainGameState::handleInput()
{
    if (IsKeyPressed(KEY_SPACE)){
        player.vy = -300;
    }
}

void MainGameState::update(float deltaTime)
{   
    handleInput();
    const float gravedad = 900;             //fuerza hacia abajo
    player.vy += gravedad * deltaTime;             //velocidad 
    player.y += player.vy * deltaTime;                //posicion pajaro
    //player.vy = 0;   

    spawnTimer += deltaTime;                    //al tiempo inicial le sumo el delta time 

    //CREACION DE TUBOS
    if(spawnTimer >= spawnEvery){        
        float x = GetScreenWidth(); //posicion x del tubo el ancho de la pantalla

        float pipe_y_offset_top = GetRandomValue(PIPE_H/2, GetScreenWidth()/2);               //posicion y del tubo superior, maximo y minimo
        float pipe_y_offset_bot = (PIPE_H - pipe_y_offset_top) + GetRandomValue(PIPE_H/2, GetScreenWidth()/2);

        Rectangle top = {x,-pipe_y_offset_top, PIPE_W, PIPE_H};      //creo columnas x es fija
        Rectangle bot = {x,pipe_y_offset_bot, PIPE_W, PIPE_H};

        pipes.push_back({top, bot,false});          //inserto las columnas en la lista
        spawnTimer = 0;                           //reinicio el timer
    }

    //MOVIMIENTO DE TUBOS
    for (size_t i = 0; i < pipes.size(); i++) {                 //así muevo las columnas
        pipes[i].top.x -= PIPE_VELOCITY * deltaTime;
        pipes[i].bot.x -= PIPE_VELOCITY * deltaTime;
    }

    //ELIMINACION DE TUBOS pasados 
    if(!pipes.empty() && pipes.front().top.x < -PIPE_W){        //si la lista no esta vacia y la posicion x del primer tubo es menor que -PIPE_W
        pipes.pop_front();                                       //elimino el primer tubo
    }

    //Bounding box del pajaro
    Rectangle pajaro = {player.x-20, player.y-20, width:40, height:40};    //origenes y tamaño

    //comprobar colisiones
    for (const auto& p : pipes){                 //recorro la lista de tubos
        if(CheckCollisionRecs(pajaro, p.top) || CheckCollisionRecs(pajaro, p.bot)){
            this->state_machine->add_state(std::make_unique<GameOverState>(puntuacion), true);   //cambiar de estado a GameOverState
            return;
        }
    }

    //comprobar si ha pasado un tubo para sumar puntuacion
    for (auto& p : pipes){
        if(!p.scored && p.top.x + PIPE_W < player.x){   //si la posicion x del tubo + su ancho es menor que la posicion x del pajaro
            puntuacion++;                               //sumo puntuacion
            p.scored = true;                        
            std::cout << "Puntuación: " << puntuacion << std::endl; 
        }
    }

}

void MainGameState::render()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawCircle(player.x, player.y, 20, RED);
   //debuggeo caja pajaro con DrawRectanglePro 


    for (const auto& p : pipes){                 //dibujo las columnas
        DrawRectangle(p.top.x, p.top.y, p.top.width, p.top.height, GREEN);
        DrawRectangle(p.bot.x, p.bot.y, p.bot.width, p.bot.height, GREEN);
    }

    std::string s = "Puntuacion: " + std::to_string(puntuacion);
    DrawText(s.c_str(), 10, 10, 20, DARKGRAY);

    EndDrawing();
}
