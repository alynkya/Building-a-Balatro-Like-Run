#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "core_engine.h"
#include <cstdlib>

// Implementasi Input Generator dari User / Random[cite: 1]
class BasicInputGenerator : public IInputGenerator
{
public:
    TurnInput generateInput() override
    {
        TurnInput input;
        // Simulasi nilai kartu/hand secara acak sederhana
        input.handPower = (rand() % 10) + 1; // Nilai 1 - 10
        input.multiplier = (rand() % 3) + 1; // Multiplier 1 - 3

        std::cout << "[Input] Hand Power: " << input.handPower
                  << " | Multiplier: " << input.multiplier << "x" << std::endl;
        return input;
    }
};

// Implementasi Scoring Rule (Kalkulasi Nilai Dasar)[cite: 1]
class BalatroScoringRule : public IScoringRule
{
public:
    int calculateBaseScore(const TurnInput &input) override
    {
        // Logika scoring sederhananya: Power x Multiplier
        return input.handPower * input.multiplier * 10;
    }
};

// Implementasi Reward Rule (Kalkulasi Hadiah Uang)[cite: 1]
class StandardRewardRule : public IRewardRule
{
public:
    int calculateReward(int baseScore) override
    {
        // Logika reward: $1 per 20 poin score
        return baseScore / 20;
    }
};

#endif