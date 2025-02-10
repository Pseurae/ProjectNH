#pragma once

class Tool final 
{
public:
    Tool();
    ~Tool();

    void Init();
    void Shutdown();

    void PreRender();
    void Render();
    void PostRender();
};