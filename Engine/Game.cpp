#include "Game.h"
#include "Global.h"
#include <algorithm>
#include "Tileset.h"
#include <Tonic/FileSystem/Provider.h>

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
    LoadTilesetDescs("Assets/Tilesets");

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

    UpdateCamera();

    mControls.SwapKeyStates();
}

void Game::Tick()
{
}

void Game::Render()
{
    global.gfxDevice->SetRenderTarget(mGameFrameBuffer, true);

    mSpriteBatch->BeginScene();
    mPlayerRenderer.Render(*mSpriteBatch, mPlayerState, mCameraPos);
    mSpriteBatch->EndScene();

    global.gfxDevice->SetRenderTarget(nullptr);

    mSpriteBatch->BeginScene();
    mSpriteBatch->DrawQuad({ 0.0f, 0.0f }, global.window.GetWindowSize(), mGameTexture);
    mSpriteBatch->EndScene();
}

void Game::UpdateCamera(void)
{
    auto newCameraPos = mPlayerState.GetPosition() - (glm::vec2{ 320, 240 } - glm::vec2{ 16, 32 }) / 2.0f;
    auto mapSize = glm::ivec2{16, 16};

    if (mapSize.x * 16 > 320) 
        mCameraPos.x = std::clamp(newCameraPos.x, 0.0f, mapSize.x * 16.0f - 320.0f);
    else
        mCameraPos.x = -(320.0f - mapSize.x * 16.0f) / 2.0f;

    if (mapSize.y * 16 > 240) 
        mCameraPos.y = std::clamp(newCameraPos.y, 0.0f, mapSize.y * 16.0f - 240.0f);
    else
        mCameraPos.y = -(240.0f - mapSize.x * 16.0f) / 2.0f;
}
