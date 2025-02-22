#pragma once

#include "PlayerState.h"
#include <Tonic/Graphics/SpriteBatch.h>
#include <Tonic/Graphics/Texture.h>
#include <Ethyl/Pointers.h>

class PlayerRenderer
{
public:
    void Init();
    void Shutdown();

    void Render(Tonic::Graphics::SpriteBatch &sb, const PlayerState &pState, const glm::vec2 &cameraPos);

private:
    static glm::vec4 GetCropArea(const PlayerState &pState);
    Ethyl::Shared<Tonic::Graphics::Texture> mPlayerNormalSpriteSheet, mPlayerCombatSpriteSheet;
};