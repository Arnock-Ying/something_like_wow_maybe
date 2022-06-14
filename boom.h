#pragma once
#include "baseArms.h"
class Boom :
    public baseArms
{
private:
    bool ifDis = false;
public:
    baseArms* FactionArm();
    bool ifDestroy();
public:
    void Updata();
    std::string to_string();
};

