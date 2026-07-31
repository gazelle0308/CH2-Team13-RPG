// Copyright 2026/07/30 JinHo

#pragma once

#include <string>

bool ignoreCaseCompare(const std::string& numOneS, const std::string& numTwoS);

bool IsLargeCase(char data);

bool IsSmallCase(char data);


template<typename Value>
bool IsOutRange(const Value& value,
                const Value& rangeOne,
                const Value& rangeTwo) {
    if (rangeOne == rangeTwo) {
        return rangeOne != value;
    }

    if (rangeOne < rangeTwo) {
        return value < rangeOne ||
               value > rangeTwo;
    } else {
        return value < rangeTwo ||
               value > rangeOne;
    }
}
