#pragma once

#include "medianskiplist.h"
#include <string>

class RollingMedians
{
public:
    std::string getMedians(const std::string& in) noexcept;

private:
    MedianSkipList skipList;
};
