#include "Game.h"
#include "Global.h"
#include <stb_image.h>

static const Tonic::Graphics::TextureDesc sGameTextureDesc = { 
    nullptr, 
    320, 
    240, 
    4,
    Tonic::Graphics::TextureWrapMode::ClampBorder,
    Tonic::Graphics::TextureFilterType::Nearest,
    true
};

void Game::Init()
{
    mControls.AttachEventHandler();
    mSpriteBatch = Ethyl::CreateShared<Tonic::Graphics::SpriteBatch>(*global.gfxDevice);
    mPlayerRenderer.Init();

    mGameTexture = global.gfxDevice->CreateTexture(sGameTextureDesc);
    mGameFrameBuffer = global.gfxDevice->CreateFrameBuffer({ mGameTexture });
    mGameMap.Load("Assets/map_test.toml");
}

void Game::Shutdown()
{
    mPlayerRenderer.Shutdown();
    mControls.DetachEventHandler();
}

void Game::Update()
{
    mPlayerState.Update();
    mPlayerState.UpdateControls(mControls);

    mCameraPos = mPlayerState.GetPosition() - (glm::vec2{ 320, 240 } - glm::vec2{ 16, 32 }) / 2.0f;

    mControls.SwapKeyStates();
}

void Game::Tick()
{
}

void Game::Render()
{
    global.gfxDevice->SetRenderTarget(mGameFrameBuffer, true);

    mSpriteBatch->BeginScene();
    mGameMap.Render(*mSpriteBatch, mCameraPos);
    mSpriteBatch->EndScene();

    mSpriteBatch->BeginScene();
    mPlayerRenderer.Render(*mSpriteBatch, mPlayerState, mCameraPos);
    mSpriteBatch->EndScene();

    global.gfxDevice->SetRenderTarget(nullptr);

    mSpriteBatch->BeginScene();
    mSpriteBatch->DrawQuad({ 0.0f, 0.0f }, global.window.GetWindowSize(), mGameTexture);
    mSpriteBatch->EndScene();
}
