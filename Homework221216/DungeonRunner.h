#pragma once
class DungeonRunner : public BaseRunner
{
	DungeonRunner();
	~DungeonRunner();


public:

	// BaseRunner을(를) 통해 상속됨
	virtual void Run() override;

	virtual void Update(InputType input) override;

	virtual void Render() override;

};

