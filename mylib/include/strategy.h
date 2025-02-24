#pragma once

enum Status
{
    Success
    , Failed
    , Running
};

template<Status STATUS>
class IStrategy
{
public:
    virtual ~IStrategy() = default;
    virtual Status execute(ControlNode* node) = 0;
};