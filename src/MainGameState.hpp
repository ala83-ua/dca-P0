#pragma once
#include <GameState.hpp>
#include <deque>

extern "C" {
    #include <raylib.h>
}



class MainGameState : public GameState
{
    public:

        struct bird{
            float x;
            float y;
            float vy;
        };

        struct PipePair { 
            Rectangle top, bot; 
            bool scored=false; 
        };

        MainGameState();
        ~MainGameState() = default;

        void init() override;
        void handleInput() override;
        void update(float deltaTime) override;
        void render() override;

        void pause(){};
        void resume(){};

    
    private:
        char entered_key;
        bird player;

        std::deque<PipePair> pipes;
        float PIPE_SPACE = 200;
        float PIPE_WIDTH = 80;
        float PIPE_VELOCITY = 200;

        float spawnTimer = 1.5f;           //cada cuanto tiempo aparece un tubo
        float spawnEvery = 1.25f;           //tiempo entre tubos
        float PIPE_W = 32.0f;
        float PIPE_H = 320.0f;  

        int puntuacion = 0;         
};  