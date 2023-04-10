#include "HeaderFiles/Commands/Invoker.h"

using namespace std;

Invoker* Invoker::_invoker = nullptr;

Invoker::~Invoker() = default;

Invoker *Invoker::Instance() {
    if(_invoker == nullptr){
        _invoker = new Invoker();
    }
    return _invoker;
}

void Invoker::Invoke() {
    if (!_queue.empty()){
        Command *exe = _queue.front();
        if (exe){
            exe->Execute();
        }
        _queue.pop();
    }
}

void Invoker::EnqueueCommand(Command *cmd) {
    _queue.push(cmd);
}
