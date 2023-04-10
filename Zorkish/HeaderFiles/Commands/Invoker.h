#ifndef ZORKISH_INVOKER_H
#define ZORKISH_INVOKER_H

#include "HeaderFiles/Commands/Command.h"

#include <queue>

class Invoker {
private:
    explicit Invoker()= default;

    static Invoker* _invoker;

    std::queue<Command*> _queue;

public:
    Invoker(Invoker(&other)) = delete;
    void operator=(const Invoker &) = delete;
    ~Invoker();

    static Invoker *Instance();

    void EnqueueCommand(Command *cmd);
    void Invoke();
};


#endif //ZORKISH_INVOKER_H
