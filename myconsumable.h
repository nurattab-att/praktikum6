#pragma once
#include "consumable.h"
#include "consumable.h"
#include "creatures.h"

class SmallHealthPotion : public Consumable {
public:
    SmallHealthPotion() : Consumable("Small Health Potion", 0) {}
    void use(std::shared_ptr<Creature> user, std::shared_ptr<Creature> target) override {
        std::cout << user->getName() << " benutzt Small Health Potion.\n";
        user->heal(20);
    }
};

class MagicMissileScroll : public Consumable {
public:
    MagicMissileScroll() : Consumable("Magic Missile Scroll", 5) {}
    void use(std::shared_ptr<Creature> user, std::shared_ptr<Creature> target) override {
        std::cout << user->getName() << " benutzt Magic Missile Scroll.\n";
        if (user->getMana() >= 5) {
            user->consumeMana(5);
            target->takeDamage(15);
        } else {
            std::cout << "Nicht genug Mana!\n";
        }
    }
};

class ManaPotion : public Consumable {
public:
    ManaPotion() : Consumable("Mana Potion", 0) {}
    void use(std::shared_ptr<Creature> user, std::shared_ptr<Creature> target) override {
        std::cout << user->getName() << " benutzt Mana Potion.\n";
        user->restoreMana(15);
    }
};

class ArmorBreakScroll : public Consumable {
public:
    ArmorBreakScroll() : Consumable("Armor Break Scroll", 5) {}
    void use(std::shared_ptr<Creature> user, std::shared_ptr<Creature> target) override {
        std::cout << user->getName() << " benutzt Armor Break Scroll.\n";
        if (user->getMana() >= 5) {
            user->consumeMana(5);
            target->reduceArmor(3);
        } else {
            std::cout << "Nicht genug Mana!\n";
        }
    }
};
