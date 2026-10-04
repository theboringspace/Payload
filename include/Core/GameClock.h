#pragma once

/**
 * CLASS GameClock
 * --
 * Tracks real and scaled game time, and enforces a fixed-timestep update loop.
 *
 * The scaling allows game time to be sped up, slowed down, or paused.
 *
 * Fixed-time-steps ensure that there is only ever x amount of updates every y amount of time.
 *
 * Typical use:
 *      clock.Advance(dt);
 *      while (clock.ShouldStep())
 *      {
 *          something.Update(GameClock::FIXED_DT);
 *          clock.ConsumeStep();
 *      }
 *
 * This assumes time in seconds btw.
 */
#include "EventBus.h"

class GameClock
{
public:
    GameClock(EventBus& events_);

    GameClock(const GameClock&) = delete;

    /**
     * FUNCTION Advance
     * --
     * Advances the clock one frame of real time.
     */
    void  Advance(float realDt);
    /**
     * FUNCTION GameTime
     * --
     * Time scaled for gameplay.
     */
    float GameTime()const;
    /**
     * FUNCTION RealTime
     * --
     *  Non-scaled real time.
     */
    float RealTime()const;
    /**
     * FUNCTION SetTimeScale
     * --
     * Set game-time multiplier. 1.0 is normal, 0.0 is paused, 2 is double, etc...
     */
    void  SetTimeScale(float scale);
    /**
     * FUNCTION GetTimeScale
     * --
     * Get game-time multiplier.
     */
    float GetTimeScale()const;
    /**
     * FUNCTION ShouldStep
     * --
     * Returns true  if enough time has passed to update.
     * Returns false otherwise.
     */
    bool  ShouldStep()const;
    /**
     * FUNCTION ConsumeStep
     * --
     * Subtract 1 update time.
     */
    void  ConsumeStep();

    /// 60Hz
    static constexpr float FIXED_DT{ 1.0f / 60.0f};

private:
    EventBus& events;

    float real_         { 0.0 }; ///< Real seconds elapsed.
    float game_         { 0.0 }; ///< Scaled seconds elapsed.
    float scale_        { 1.0 }; ///< Game-time multiplier.
    float accumulator_  { 0.0 }; ///< Scaled time not yet used.
};
