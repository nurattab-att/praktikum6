#pragma once
#include "creatures.h"
#include <random>

class Mage : public Creature {
public:
    Mage() : Creature("Mage", 50, 5, 15, 5, 30) {}
    void doSpecialMove(std::shared_ptr<Creature> target) override {
        if (getMana() >= 10) {
            std::cout << name << " wirkt Feuerball auf " << target->getName() << "!\n";
            consumeMana(10);
            target->takeDamage(25);
        }
    }
    void attack(std::shared_ptr<Creature> target) override {
        if (rand() % 2 == 0) doSpecialMove(target);
        else {
            std::cout << name << " greift " << target->getName() << " mit einem Zauberstab an!\n";
            Creature::attack(target);
        }
    }
};

class Undead : public Creature {
public:
    Undead() : Creature("Undead", 60, 7, 10, 3, 20) {}
    void doSpecialMove(std::shared_ptr<Creature>) override {
        if (getMana() >= 5) {
            std::cout << name << " murmelt dunkle Worte und heilt sich!\n";
            consumeMana(5);
            heal(10);
        }
    }
    void attack(std::shared_ptr<Creature> target) override {
        if (rand() % 2 == 0) doSpecialMove(target);
        else {
            std::cout << name << " schwingt seine Klauen gegen " << target->getName() << "!\n";
            Creature::attack(target);
        }
    }
};
