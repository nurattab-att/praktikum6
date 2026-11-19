#pragma once
#include <memory>
#include <string>
class Creature;

class Consumable {
protected:
    std::string name;
    int manaCost;

public:
    Consumable(std::string name, int manaCost) : name(name), manaCost(manaCost) {}
    virtual void use(std::shared_ptr<Creature> user, std::shared_ptr<Creature> target) = 0;
    virtual std::string getName() const { return name; }
};
