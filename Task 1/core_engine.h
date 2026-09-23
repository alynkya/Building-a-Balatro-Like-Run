#ifndef CORE_ENGINE_H
#define CORE_ENGINE_H

#include <iostream>
#include <memory>
#include <string>

// Struktur Data Input Turn[cite: 1]
struct TurnInput {
    int handPower = 0;
    int multiplier = 1;
};

// Interface untuk Input Generator[cite: 1]
class IInputGenerator {
public:
    virtual ~IInputGenerator() = default;
    virtual TurnInput generateInput() = 0;
};

// Interface untuk Scoring Rule[cite: 1]
class IScoringRule {
public:
    virtual ~IScoringRule() = default;
    virtual int calculateBaseScore(const TurnInput& input) = 0;
};

// Interface untuk Reward Rule[cite: 1]
class IRewardRule {
public:
    virtual ~IRewardRule() = default;
    virtual int calculateReward(int baseScore) = 0;
};

// Sistem Shop sederhana[cite: 1]
class ShopSystem {
public:
    virtual void openShop(int& currentMoney) {
        std::cout << "\n=== SHOP PHASE ===" << std::endl;
        std::cout << "Uang saat ini: $" << currentMoney << std::endl;
        std::cout << "Membeli item seharga $5..." << std::endl;
        if (currentMoney >= 5) {
            currentMoney -= 5;
            std::cout << "Berhasil membeli item! Sisa uang: $" << currentMoney << std::endl;
        } else {
            std::cout << "Uang tidak cukup untuk membeli item." << std::endl;
        }
        std::cout << "==================\n" << std::endl;
    }
};

// Kelas Utama Runner / Game Loop[cite: 1]
class RunSession {
private:
    int money = 10;
    int currentRound = 1;
    const int maxRounds = 3; // Berjalan selama 3 ronde[cite: 1]

    std::unique_ptr<IInputGenerator> inputGen;
    std::unique_ptr<IScoringRule> scoringRule;
    std::unique_ptr<IRewardRule> rewardRule;
    std::unique_ptr<ShopSystem> shopSystem;

public:
    RunSession(std::unique_ptr<IInputGenerator> gen,
               std::unique_ptr<IScoringRule> score,
               std::unique_ptr<IRewardRule> reward,
               std::unique_ptr<ShopSystem> shop)
        : inputGen(std::move(gen)),
          scoringRule(std::move(score)),
          rewardRule(std::move(reward)),
          shopSystem(std::move(shop)) {}

    void startRun() {
        std::cout << "--- MEMULAI BALATRO-LIKE RUN ---" << std::endl;

        while (currentRound <= maxRounds) {
            std::cout << "\n===============================" << std::endl;
            std::cout << "ROUND " << currentRound << " OF " << maxRounds << std::endl;
            std::cout << "===============================" << std::endl;

            // 1. Generate Input[cite: 1]
            TurnInput input = inputGen->generateInput();

            // 2. Compute Base Score[cite: 1]
            int baseScore = scoringRule->calculateBaseScore(input);
            std::cout << "Base Score yang didapat: " << baseScore << std::endl;

            // 3. Compute Reward[cite: 1]
            int reward = rewardRule->calculateReward(baseScore);
            std::cout << "Reward didapat: $" << reward << std::endl;

            // 4. Update Money[cite: 1]
            money += reward;
            std::cout << "Total Uang Saat Ini: $" << money << std::endl;

            // 5. Shop Phase[cite: 1]
            shopSystem->openShop(money);

            // 6. Advance Round[cite: 1]
            currentRound++;
        }

        std::cout << "--- RUN SELESAI ---" << std::endl;
        std::cout << "Uang Akhir: $" << money << std::endl;
    }
};

#endif