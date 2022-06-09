#pragma once
#include "baseMissile.h"
class Arch :
    public baseMissile
{
public:
    virtual baseArms* FactionArm();

    virtual int FireTime() { return 35; }
};

