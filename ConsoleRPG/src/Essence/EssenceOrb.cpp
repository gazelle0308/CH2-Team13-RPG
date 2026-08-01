// Copyright 2026/08/01 JinHo

#include "Essence/EssenceOrb.h"

#include <iostream>
#include <sstream>
#include <string>
#include <limits>

#include "Essence/Essence.h"

// Constructor

EssenceOrb::EssenceOrb() {
    this->orb[0] = Essence("Slime", 0, 0, 0, 0);
    this->orb[1] = Essence("Zombie", 0, 0, 0, 0);
    this->orb[2] = Essence("Goblin", 0, 0, 0, 0);
    this->orb[3] = Essence("Wild Wolf", 0, 0, 0, 0);
    this->orb[4] = Essence("Chimera", 0, 0, 0, 0);
    this->orb[5] = Essence("Ghost", 0, 0, 0, 0);
    this->orb[6] = Essence("Succubus", 0, 0, 0, 0);
    this->orb[7] = Essence("Incubus", 0, 0, 0, 0);
    this->orb[8] = Essence("Ghoul", 0, 0, 0, 0);
    this->orb[9] = Essence("Werewolf", 0, 0, 0, 0);
    this->orb[10] = Essence("Gargoyle", 0, 0, 0, 0);
    this->orb[11] = Essence("Margoyle", 0, 0, 0, 0);
    this->orb[12] = Essence("Mummy", 0, 0, 0, 0);
    this->orb[13] = Essence("Demon", 0, 0, 0, 0);
    this->orb[14] = Essence("Golem", 0, 0, 0, 0);
    this->orb[15] = Essence("Griffon", 0, 0, 0, 0);
    this->orb[16] = Essence("Vampire", 0, 0, 0, 0);
    this->orb[17] = Essence("Siren", 0, 0, 0, 0);
    this->orb[18] = Essence("Minotaur", 0, 0, 0, 0);
    this->orb[19] = Essence("Ice Elemental", 0, 0, 0, 0);
    this->orb[20] = Essence("High Demon", 0, 0, 0, 0);
    this->orb[21] = Essence("High Minotaur", 0, 0, 0, 0);
    this->orb[22] = Essence("High Vampire", 0, 0, 0, 0);
    this->orb[23] = Essence("Guardian Chimera", 0, 0, 0, 0);
    this->orb[24] = Essence("Phoenix", 0, 0, 0, 0);
    this->orb[25] = Essence("False", 0, 0, 0, 0);
}

// operator

Essence& EssenceOrb::operator[](int index) {
    if (index > 24 || index < 0) {
        throw std::out_of_range("Out of index : " + std::to_string(index));
    }
    return this->orb[index];
}

// Function

Essence& EssenceOrb::UseEssence(std::string name) {
    int essence = this->NameToIndex(name);
    if (essence == -1) {
        return this->orb[25];
    }
    if (this->orb[essence].GetLock()) {
        return this->orb[25];
    }
    if (this->orb[essence].GetEnable()) {
        this->orb[essence].DisableEssence();
        return this->orb[essence];
    } else {
        this->orb[essence].EnableEssence();
        for (int loop = 0; loop < 25; loop = loop + 1) {
            if (essence == loop) {
                continue;
            }
            this->orb[loop].DisableEssence();
        }
        return this->orb[essence];
    }
}

std::string EssenceOrb::GetOrbInfo() {
    std::ostringstream oss;
    for (int loop = 0; loop < 25; loop = loop + 1) {
        if (this->orb[loop].GetLock()) {
            oss << loop + 1 << ".Locked(////////)\n";
        } else {
            oss << loop + 1 << "." << this->orb[loop].GetName() <<
            " Essence(Hp: " << this->orb[loop].GetHp() <<
            " Mp: " << this->orb[loop].GetMp() <<
            " Power: " << this->orb[loop].GetPower() <<
            " Defence: " << this->orb[loop].GetDefence() << ") \n";
        }
    }
    return oss.str();
}

int EssenceOrb::NameToIndex(std::string name) {
    for (int loop = 0; loop < 25; loop = loop + 1) {
        if (this->orb[loop].GetName() == name) {
            return loop;
        }
    }
    return -1;
}

void EssenceOrb::AcquireEssence(std::string name) {
    int essence = this->NameToIndex(name);
    int Gain = 1;
    int choice = -1;

    // 몬스터 name 값 확인
    if (essence == -1) {
        throw std::logic_error("에러! 전달 받은 인자" + name + "의 정보가 존재하지 않습니다!");
    }
    // 이미 얻은 정수 선택지X
    if (!this->orb[essence].GetLock()) {
        return;
    }

    std::cout << "방금 전투한 몬스터의 정수를 발견했습니다!.\n";
    std::cout << "획득 하시겠습니까?\n(획득 : 1, 포기 : 아무 키나 입력): ";

    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "정수 획득을 포기하셨습니다!\n";
        return;
    }

    if (choice != Gain) {
        std::cout << "정수 획득을 포기하셨습니다!\n";
        return;
    }

    this->orb[essence].OpenEssence();
    std::cout << "정수" << this->orb[essence].GetName() << "을 획득하셨습니다! \n";
}
