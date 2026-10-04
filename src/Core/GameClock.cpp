#include "GameClock.h"
#include "Events.h"

GameClock::GameClock(EventBus& events_)
:   events(events_)
{
    increaseTimeScaleSubscription = events.Subscribe<IncreaseTimeScale>([this](const IncreaseTimeScale& event)
        {
            SetTimeScale(GetTimeScale() + event.increase);
        });
    decreaseTimeScaleSubscription = events.Subscribe<DecreaseTimeScale>([this](const DecreaseTimeScale& event)
        {
            SetTimeScale(GetTimeScale() - event.decrease);

        });
    resetTimeScaleSubscription = events.Subscribe<ResetTimeScale>([this](const ResetTimeScale& event)
        {
            SetTimeScale(event.timeScale);
        });
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
