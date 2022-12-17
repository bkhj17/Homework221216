#include "Framework.h"

void ShowPlayer::Update(InputType input)
{
	switch (input)
	{
	case InputType::NONE:
		break;
	case InputType::UP:
		break;
	case InputType::DOWN:
		break;
	case InputType::YES:
		Exit();
		break;
	case InputType::CANCEL:
		Exit();
		break;
	default:
		break;
	}
}

void ShowPlayer::Render()
{
	system("cls");
	cout << "==============================\n";
	cout << "		플레이어\n";
	cout << "==============================\n";

	PlayerInstance::Get()->ShowPlayerInfo();


	cout << "\n==================================\n"
		<< "Z: 확인 X: 종료\n";

}
