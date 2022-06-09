#pragma once
#include "baseArms.h"
class Sword :
    public baseArms
{
public:
    baseArms* FactionArm();
public:
    bool ifDestroy();
    void OnUsing(baseWarrior*);
};

