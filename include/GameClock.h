#pragma once

class GameClock
{
public:
    void  Advance(float realDt);
    float GameTime()const;
    float RealTime()const;
    void  SetTimeScale(float scale);
    bool  ShouldStep()const;
    void  ConsumeStep();

    // TEST
    float GetTimeScale()const;

    static constexpr float FIXED_DT{ 1.0f / 60.0f};

private:

    float real_         { 0.0 };
    float game_         { 0.0 };
    float scale_        { 1.0 };
    float accumulator_  { 0.0 };
};
