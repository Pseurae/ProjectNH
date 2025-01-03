#pragma once

#include <Ethyl/Pointers.h>
#include <Tonic/Graphics/FrameBuffer.h>
#include "Controls.h"
#include "PlayerState.h"

enum class GameState
{
    Menu,
    Game
};

class Game
{
public:
    Game() = default;
    ~Game() = default;

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(Game&&) = delete;

    void Init();
    void Shutdown();

    void Update();
    void Tick();
    void Render();

private:
    GameState mState = GameState::Game;
    Controls mControls;
    PlayerState mPlayerState;
};
