#pragma once
#include "BaseRunner.h"
class InventoryRunner : public BaseRunner
{
public:
    InventoryRunner();
    ~InventoryRunner();

    // BaseRunner��(��) ���� ��ӵ�
    virtual void Update(InputType input) override;
    virtual void Render() override;

};

