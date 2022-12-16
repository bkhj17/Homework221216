#pragma once
struct ItemData {
	int key = -1;
	int price = 0;
	string name = "";
};

class Item {
public:
	Item(int itemKey = -1, int count = 1);

	int& Count() { return count; }
	ItemData& GetData() { return data; }

	void GetItemSaveData(stringstream& ss);
private:
	int count = 0;
	ItemData data;
};
