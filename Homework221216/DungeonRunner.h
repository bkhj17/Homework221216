#pragma once
class DungeonRunner : public BaseRunner
{
	DungeonRunner();
	~DungeonRunner();


public:

	// BaseRunner��(��) ���� ��ӵ�
	virtual void Run() override;

	virtual void Update(InputType input) override;

	virtual void Render() override;

};

