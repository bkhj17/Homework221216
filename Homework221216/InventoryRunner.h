#pragma once
#include "BaseRunner.h"
class InventoryRunner : public BaseRunner
{
public:
    InventoryRunner();
    ~InventoryRunner();

    // BaseRunner을(를) 통해 상속됨
    virtual void Update(InputType input) override;
    virtual void Render() override;

};

