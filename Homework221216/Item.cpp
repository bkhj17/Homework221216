#include "Framework.h"

Item::Item(int itemKey, int count)
	:  count(count)
{
	if(itemKey >= 0)
		data = DataManager::Get()->GetItemData(itemKey);
}

void Item::GetItemSaveData(stringstream& ss)
{
	//ss << 아이템 키 << "\t" << 아이템 이름 << "\t" << 아이템 가격 << "\t" << 아이템 수량 << "\n";
	ss << data.key << "\t" 
		<< data.name << "\t" 
		<< data.price << "\t" 
		<< count << "\n";
}
