#include "Game.h"
#include "Global.h"
#include <stb_image.h>

void Game::Init()
{
    mControls.AttachEventHandler();
    mSpriteBatch = Ethyl::CreateShared<Tonic::Graphics::SpriteBatch>(*global.gfxDevice);
    mPlayerRenderer.Init();
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
    mSpriteBatch->BeginScene();
    mPlayerRenderer.Render(*mSpriteBatch, mPlayerState);
    mSpriteBatch->EndScene();
}
