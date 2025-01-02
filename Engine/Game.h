#pragma once

class Game
{
public:
    Game() = default;
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
};
