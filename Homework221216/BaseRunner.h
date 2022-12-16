#pragma once
enum class InputType
{
	NONE, UP, DOWN, YES, CANCEL,
};

class BaseRunner
{
public:
	virtual void Run();
	virtual void Init();

	InputType Input();
	virtual void Update(InputType input) = 0;
	virtual void Render() = 0;

	bool IsExit() { return isExit; };
protected:	
	int cursor = 0;
	bool requestInput = false;
	bool requestRender = false;

	InputType input = InputType::NONE;
	virtual void Exit() { isExit = true; }
private:
	bool isExit = false;
};

