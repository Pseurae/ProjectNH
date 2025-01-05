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

    mControls.SwapKeyStates();
}

void Game::Tick()
{
}

void Game::Render()
{
    mSpriteBatch->BeginScene(mGameFrameBuffer);
    mPlayerRenderer.Render(*mSpriteBatch, mPlayerState);
    mSpriteBatch->EndScene();

    mSpriteBatch->BeginScene(nullptr);
    mSpriteBatch->DrawQuad({ 0.0f, 0.0f }, global.window.GetWindowSize(), mGameTexture);
    mSpriteBatch->EndScene();
}
