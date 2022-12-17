
#include "Framework.h"

int main()
{
	DataManager::Get();
	PlayerInstance::Get();

	//러너
	GameRunner runner;
	runner.Run();

	PlayerInstance::Delete();
	DataManager::Delete();

	return 0;
}