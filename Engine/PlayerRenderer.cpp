#include "PlayerRenderer.h"
#include <stb_image.h>
#include <Ethyl/Assert.h>
#include "Global.h"

void PlayerRenderer::Init()
{
    {
        int w, h, channels;
        unsigned char *data = stbi_load("Assets/Nobita.png", &w, &h, &channels, 0);
        ETHYL_ASSERT(data, "Error loading image.");
        mPlayerSpriteSheet = global.gfxDevice->CreateTexture({ data, w, h, channels });
        stbi_image_free(data);
    }
}

void PlayerRenderer::Shutdown()
{
}

void PlayerRenderer::Render(Tonic::Graphics::SpriteBatch &sb, const PlayerState &pState, const glm::vec2 &cameraPos)
{
    auto pos = pState.GetPosition() - cameraPos;
    sb.DrawQuad(pos - glm::vec2{ 4.0f, 16.0f }, { 24.0f, 32.0f }, mPlayerSpriteSheet, GetCropArea(pState));
}

glm::vec4 PlayerRenderer::GetCropArea(const PlayerState &pState)
{
    glm::vec2 cropArea{0.0f, 0.0f};

    switch (pState.GetFacingDir())
    {
    case DIRECTION_UP:
        cropArea.y = 32 * 0;
        break;
    case DIRECTION_LEFT:
        cropArea.y = 32 * 3;
        break;
    case DIRECTION_RIGHT:
        cropArea.y = 32 * 1;
        break;
    case DIRECTION_DOWN:
    default:
        cropArea.y = 32 * 2;
        break;
    }

    cropArea.x = !pState.IsMoving() ? 24 : 24 * pState.GetLegState();

    return { cropArea.x, cropArea.y, cropArea.x + 24, cropArea.y + 32 };
}