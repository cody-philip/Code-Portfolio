#include "HeaderFiles/Builder/Director.h"

void Director::constructPlayer(LivingEntityBuilder* builder, const std::string& name, const std::string& desc, int hp) {
    builder->setName(name);
    builder->setDescription(desc);

    builder->addHealthAttribute(hp);

    builder->addAttackAction();
}

void Director::constructMonster(LivingEntityBuilder *builder, const std::string &name, const std::string &desc, int hp) {
    builder->setName(name);
    builder->setDescription(desc);

    builder->addHealthAttribute(hp);
}

void Director::constructItem(StaticEntityBuilder *builder, const std::string& name, const std::string& desc) {
    builder->setName(name);
    builder->setDescription(desc);

}

void Director::constructContainer(StaticEntityBuilder *builder, const std::string &name, const std::string &desc) {
    builder->setName(name);
    builder->setDescription(desc);
}
