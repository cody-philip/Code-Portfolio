#include "HeaderFiles/Builder/PlayerBuilder.h"

PlayerBuilder::PlayerBuilder() {
    _player = Actor();
}

void PlayerBuilder::Reset() {
    _player = Actor();
}

void PlayerBuilder::addHealthAttribute(int hp) {
    Attribute a = Attribute();
    a.setAtt(hp);
    a.setMax(hp);
    _player.addAttribute("Health", a);
}

void PlayerBuilder::setName(const std::string& name) {
    _player.setName(name);
}

void PlayerBuilder::setDescription(const std::string& desc) {
    _player.setDescription(desc);
}

Actor PlayerBuilder::getProduct() {
    Actor product = this->_player;
    this->Reset();
    return product;
}

void PlayerBuilder::addAttackAction() {
    _player.addAction("attack", Attack());
}
