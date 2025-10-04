#pragma once
#include <GameState.hpp>
#include <deque>

extern "C" {
    #include <raylib.h>
}

class GameOverState : public GameState{
    
    public:
    GameOverState(int puntuacion);
    GameOverState();
    ~GameOverState() = default;         //destructor por defecto

    void init() ;                       //metodos virtuales de gameStat
    void handleInput() ;
    void update(float deltaTime) ;
    void render() ;     
       
    void pause(){};
    void resume(){};

    private:
    int puntuacion = 0;
        
};