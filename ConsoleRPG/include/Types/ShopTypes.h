#pragma once
#include <string>

struct FShopItemData
{
public:
	std::string id = "ID";
	int count = 0;

public:
	void SetId(std::string id_) {
		id = id_;
	}
	void SetCount(int count_) {
		count = count_;
	}

	std::string GetId() const {
		return id;
	}
	int GetCount() const {
		return count;
	}
};