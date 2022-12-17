#pragma once
class ShowPlayer :
    public BaseRunner
{
public:
	virtual void Update(InputType input) override;
	virtual void Render() override;
};

