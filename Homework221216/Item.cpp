#include "Framework.h"

Item::Item(int itemKey, int count)
	:  count(count)
{
	if(itemKey >= 0)
		data = DataManager::Get()->GetItemData(itemKey);
}

void Item::GetItemSaveData(stringstream& ss)
{
	//ss << ������ Ű << "\t" << ������ �̸� << "\t" << ������ ���� << "\t" << ������ ���� << "\n";
	ss << data.key << "\t" 
		<< data.name << "\t" 
		<< data.price << "\t" 
		<< count << "\n";
}
