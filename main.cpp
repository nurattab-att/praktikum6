#include <iostream>
#include <memory>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>
#include "creatures.h"
#include "myconsumable.h"
#include "mycreatures.h"

void Creature::attack(std::shared_ptr<Creature> target) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> d(attackMean, attackStddev);
    int rawDamage = static_cast<int>(d(gen));
    int finalDamage = std::max(0, rawDamage - target->getArmor());
    std::cout << name << " verursacht " << finalDamage << " Schaden an " << target->getName() << "!\n";
    target->takeDamage(finalDamage);
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));
    std::shared_ptr<Creature> player = std::make_shared<Mage>();
    player->addToInventory(std::make_shared<SmallHealthPotion>());
    player->addToInventory(std::make_shared<ManaPotion>());
    player->addToInventory(std::make_shared<MagicMissileScroll>());
    player->addToInventory(std::make_shared<ArmorBreakScroll>());

    while (player->isAlive()) {
        auto monster = std::make_shared<Undead>();
        std::cout << "\nEin " << monster->getName() << " erscheint!\n";

        while (player->isAlive() && monster->isAlive()) {
            std::cout << "\n== Status ==\n";
            std::cout << player->getName() << " - HP: " << player->getHP() << ", Mana: " << player->getMana() << ", Rüstung: " << player->getArmor() << "\n";
            std::cout << monster->getName() << " - HP: " << monster->getHP() << ", Mana: " << monster->getMana() << ", Rüstung: " << monster->getArmor() << "\n";

            std::cout << "\n1. Angreifen\n2. Item benutzen\n> ";
            int choice;
            std::cin >> choice;

            if (choice == 1) {
                player->attack(monster);
            } else if (choice == 2 && !player->getInventory().empty()) {
                std::cout << "Items:\n";
                auto inv = player->getInventory();
                for (size_t i = 0; i < inv.size(); ++i) {
                    std::cout << i << ": " << inv[i]->getName() << "\n";
                }
                std::cout << "Index wählen: ";
                int index;
                std::cin >> index;
                if (index >= 0 && index < (int)inv.size()) {
                    inv[index]->use(player, monster);
                }
            }

            if (monster->isAlive()) {
                monster->attack(player);
            }
        }

        if (player->isAlive()) {
            std::cout << "\nDu hast überlebt! Level Up!\n";
            player->levelUp();
        } else {
            std::cout << "\nDu bist gestorben.\n";
        }
    }
    return 0;
}
