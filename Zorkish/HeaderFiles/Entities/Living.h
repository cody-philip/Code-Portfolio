#ifndef ZORKISH_LIVING_H
#define ZORKISH_LIVING_H

#include <HeaderFiles/Entities/Entity.h>
#include <HeaderFiles/Entities/Components/Attribute.h>

#include <utility>

class Living : public Entity {
private:
    std::map<std::string, Attribute> _attributes;

public:
    Living(std::string name, std::string desc) : Entity(std::move(name), std::move(desc)){}

    void addAttribute(const std::string& s, Attribute a) { if (_attributes.count(s) == 0) _attributes[s] = a; }
    [[nodiscard]] std::map<std::string, Attribute> getAttributes() const { return _attributes; }
    Attribute* getAttribute(const std::string& s) { if (_attributes.count(s) != 0) return &_attributes[s]; else return nullptr; }

    [[nodiscard]] std::string getDescription() const override {
        std::string result;

        result += _description;

        if (!_attributes.empty()) {
            result += "\n Attributes: \n";
            for (auto const &r: getAttributes()) {
                result += " > " + r.first + ":\t\t" + std::to_string(r.second.GetAtt()) + "\n";
            }
        }

        if (!_actions.empty()) {
            result += " Actions: \n";
            for (auto const &r: _actions) {
                result += " > " + r.first + "\n";
            }
        }

        return result;
    }

};

#endif //ZORKISH_LIVING_H
