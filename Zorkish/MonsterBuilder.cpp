#include "MonsterBuilder.h"

MonsterBuilder::MonsterBuilder() {
    _monster = Actor();
}

void MonsterBuilder::Reset() {
    _monster = Actor();
}

void MonsterBuilder::setName(const std::string &name) {
    _monster.setName(name);
}

void MonsterBuilder::setDescription(const std::string &desc) {
    _monster.setDescription(desc);
}

void MonsterBuilder::addHealthAttribute(int hp) {
    Attribute a = Attribute();
    a.setAtt(hp);
    a.setMax(hp);
    _monster.addAttribute("Health", a);
}

Actor MonsterBuilder::getProduct() {
    Actor product = this->_monster;
    this->Reset();
    return product;
}
