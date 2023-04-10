#ifndef ZORKISH_ACTION_H
#define ZORKISH_ACTION_H

class Entity;
class Living;

class Action {
protected:

public:
    Action() = default;

    virtual void actOnLiving(Living* target){}
};

#endif //ZORKISH_ACTION_H
