#pragma once

#include <string>

class Pane
{
public:
    virtual ~Pane() = default;

    virtual void Draw() = 0;
    virtual const std::string GetWindowName() = 0;

    bool &GetOpenState() { return mIsWindowOpen; }
    const bool &GetOpenState() const { return mIsWindowOpen; }

private:
    bool mIsWindowOpen = true;
};