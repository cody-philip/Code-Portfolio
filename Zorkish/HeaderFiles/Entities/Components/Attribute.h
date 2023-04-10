#ifndef ZORKISH_ATTRIBUTE_H
#define ZORKISH_ATTRIBUTE_H

#include <string>
#include <utility>

class Attribute {
private:
    int _value;
    int _max;

public:
    Attribute() = default;

    void setAtt(int i) { _value = i; }
    [[nodiscard]] int GetAtt() const { return _value; }

    void setMax(int i) { _max = i; }
    [[nodiscard]] int GetMax() const { return _max; }

    void Alter(int i) { _value += i; }
};

#endif //ZORKISH_ATTRIBUTE_H
