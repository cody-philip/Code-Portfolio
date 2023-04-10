#ifndef ZORKISH_STATIC_H
#define ZORKISH_STATIC_H

#include <utility>

#include "Entity.h"

class Static : public Entity {
public:
    Static(std::string name, std::string desc) : Entity(std::move(name), std::move(desc)){}

    [[nodiscard]] std::string getDescription() const override {
        std::string result;

        result += _description;

        if (!_actions.empty()) {
            result += " Actions: \n";
            for (auto const &r: _actions) {
                result += " > " + r.first + "\n";
            }
        }

        return result;
    }
};

#endif //ZORKISH_STATIC_H
