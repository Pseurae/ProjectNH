#include "Game.h"
#include "Global.h"

void Game::Init()
{
    mControls.AttachEventHandler();
}

void Game::Shutdown()
{
    mControls.DetachEventHandler();
}

void Game::Update()
{
    mPlayerState.Update();
    mPlayerState.Move(mControls.GetMovementDirection());
}

void Game::Tick()
{
}

void Game::Render()
{
}
