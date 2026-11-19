#pragma once
#include <string>
#include <vector>
#include <memory>
#include <iostream>

class Creature;
class Consumable;

class Creature {
protected:
    std::string name;
    int hp, armor, level, mana;
    double attackMean, attackStddev;
    std::vector<std::shared_ptr<Consumable>> inventory;

public:
    Creature(std::string name, int hp, double mean, double stddev, int armor, int mana = 0)
        : name(name), hp(hp), attackMean(mean), attackStddev(stddev), armor(armor), level(1), mana(mana) {}

    virtual void attack(std::shared_ptr<Creature> target);
    virtual void doSpecialMove(std::shared_ptr<Creature> target) {} // Optional

    void heal(int amount) {
        hp += amount;
        if (hp > 100) hp = 100;
        std::cout << name << " heilt sich um " << amount << " HP (neu: " << hp << ")\n";
    }

    void takeDamage(int amount) {
        int actual = std::max(0, amount - armor);
        hp -= actual;
        std::cout << name << " erleidet " << actual << " Schaden (HP: " << hp << ")\n";
    }

    void reduceArmor(int amount) {
        armor = std::max(0, armor - amount);
        std::cout << name << " verliert " << amount << " Rüstung (neu: " << armor << ")\n";
    }

    bool isAlive() const { return hp > 0; }
    std::string getName() const { return name; }
    int getMana() const { return mana; }
    void consumeMana(int amount) {
        mana -= amount;
        std::cout << name << " verbraucht " << amount << " Mana (neu: " << mana << ")\n";
    }
    void restoreMana(int amount) {
        mana += amount;
        std::cout << name << " erhält " << amount << " Mana (neu: " << mana << ")\n";
    }

    int getHP() const { return hp; }
    int getArmor() const { return armor; }

    std::vector<std::shared_ptr<Consumable>>& getInventory() { return inventory; }
    void addToInventory(std::shared_ptr<Consumable> c) { inventory.push_back(c); }
    void levelUp() { ++level; armor += 1; attackMean += 1; std::cout << name << " erreicht Level " << level << "!\n"; }
};
