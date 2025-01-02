#pragma once

#include <Tonic/Keys.h>

namespace Events
{
struct Init {};

struct PreUpdate {};
struct Update {};
struct PostUpdate {};

struct PreTick {};
struct Tick {};
struct PostTick {};

struct PreRender {};
struct Render {};
struct PostRender {};

struct KeyboardInput 
{
    ::Tonic::Input::Key key;
    ::Tonic::Input::Action action;
    ::Tonic::Input::KeyMod mods;
};

struct Quit {};
}