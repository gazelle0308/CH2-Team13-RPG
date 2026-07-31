// Copyright 2026/07/30 JinHo

#include "Utility/Utility.h"

#include <string>

bool ignoreCaseCompare(const std::string& oneString,
                       const std::string& twoString) {
    if (oneString.size() != twoString.size()) {
        return false;
    }

    for (size_t i = 0;
        i < oneString.size();
        i = i + 1) {
        if (oneString[i] != twoString[i] &&
            !(std::abs(oneString[i] - twoString[i]) == 32 &&
                (IsSmallCase(oneString[i]) ||
                 IsLargeCase(oneString[i])) &&
                (IsSmallCase(twoString[i]) ||
                 IsLargeCase(twoString[i])))) {
            return false;
        }
    }
    return true;
}


// check to large case
bool IsLargeCase(char data) {
    if (data >= 65 &&
        data <= 90) {
        return true;
    }
    return false;
}

// check to small case
bool IsSmallCase(char data) {
    if (data >= 97 &&
        data <= 122) {
        return true;
    }
    return false;
}
