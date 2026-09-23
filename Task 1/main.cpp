#include "core_engine.h"
#include "game_logic.h"
#include <ctime>

int main()
{
    // Inisialisasi seed random
    srand(static_cast<unsigned int>(time(0)));

    // Instansiasi logika dari Orang 2
    auto inputGen = std::make_unique<BasicInputGenerator>();
    auto scoringRule = std::make_unique<BalatroScoringRule>();
    auto rewardRule = std::make_unique<StandardRewardRule>();
    auto shopSystem = std::make_unique<ShopSystem>();

    // Menjalankan Core Engine dari Orang 1 dengan menyuntikkan logika Orang 2[cite: 1]
    RunSession session(
        std::move(inputGen),
        std::move(scoringRule),
        std::move(rewardRule),
        std::move(shopSystem));

    // Jalankan game loop
    session.startRun();

    return 0;
}