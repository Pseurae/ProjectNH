#pragma once

#include <Ethyl/Pointers.h>
#include <Tonic/Graphics/FrameBuffer.h>
#include "Controls.h"
#include "PlayerState.h"
#include <Tonic/Graphics/SpriteBatch.h>
#include <Tonic/Graphics/Texture.h>
#include "PlayerRenderer.h"

enum class GameState
{
    Menu,
    Game
};

class Game final
{
public:
    Game();
    ~Game();

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(Game&&) = delete;

    void Init();
    void Shutdown();

    void Update();
    void Tick();
    void Render();

    void UpdateCamera(void);

private:
    GameState mState = GameState::Game;
    Controls mControls;
    PlayerState mPlayerState;
    Ethyl::Shared<Tonic::Graphics::SpriteBatch> mSpriteBatch;
    Ethyl::Shared<Tonic::Graphics::FrameBuffer> mGameFrameBuffer;
    Ethyl::Shared<Tonic::Graphics::Texture> mGameTexture;
    PlayerRenderer mPlayerRenderer;
    glm::vec2 mCameraPos;
};
