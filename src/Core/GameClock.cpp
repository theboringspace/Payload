#include "GameClock.h"
#include "Events.h"

GameClock::GameClock(EventBus& events_)
:   events(events_)
{
}

void GameClock::Advance(float realDt)
{
    const float scaled{ realDt * scale_ };
    real_        += realDt;
    game_        += scaled;
    accumulator_ += scaled;
}

bool GameClock::ShouldStep()const
{
    return accumulator_ >= FIXED_DT;
}

void GameClock::ConsumeStep()
{
    accumulator_ -= FIXED_DT;
}

// TEST
float GameClock::GetTimeScale()const
{
    return scale_;
}


float GameClock::GameTime()const
{
    return game_;
}

float GameClock::RealTime()const
{
    return real_;
}

void GameClock::SetTimeScale(float scale)
{
    scale_ = scale;
    events.Enqueue(TimeScaleChanged{ scale });
}
