#pragma once

class State
{
public:
    State(const State&) = delete;
    State& operator=(const State&) = delete;
    State(State&&) = delete;
    State& operator=(State&&) = delete;

    virtual void Attach(void) {}
    virtual void Detach(void) {}

    virtual void Update(void) {}
    virtual void Tick(void) {}
    virtual void Render(void) {}
};