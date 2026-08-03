// Copyright 2026/08/01 JinHo

#include "Essence/EssenceOrb.h"

#include <iostream>
#include <sstream>
#include <string>
#include <limits>

#include "Essence/Essence.h"

// Constructor

EssenceOrb::EssenceOrb() {
    this->orb[0] = Essence("슬라임", 0, 0, 0, 0);
    this->orb[1] = Essence("좀비", 0, 0, 0, 0);
    this->orb[2] = Essence("고블린", 0, 0, 0, 0);
    this->orb[3] = Essence("야생 늑대", 0, 0, 0, 0);
    this->orb[4] = Essence("키메라", 0, 0, 0, 0);
    this->orb[5] = Essence("고스트", 0, 0, 0, 0);
    this->orb[6] = Essence("서큐버스", 0, 0, 0, 0);
    this->orb[7] = Essence("인큐버스", 0, 0, 0, 0);
    this->orb[8] = Essence("구울", 0, 0, 0, 0);
    this->orb[9] = Essence("웨어울프", 0, 0, 0, 0);
    this->orb[10] = Essence("가고일", 0, 0, 0, 0);
    this->orb[11] = Essence("마고일", 0, 0, 0, 0);
    this->orb[12] = Essence("미라", 0, 0, 0, 0);
    this->orb[13] = Essence("데몬", 0, 0, 0, 0);
    this->orb[14] = Essence("골렘", 0, 0, 0, 0);
    this->orb[15] = Essence("그리폰", 0, 0, 0, 0);
    this->orb[16] = Essence("뱀파이어", 0, 0, 0, 0);
    this->orb[17] = Essence("세이렌", 0, 0, 0, 0);
    this->orb[18] = Essence("미노타우르스", 0, 0, 0, 0);
    this->orb[19] = Essence("얼음 정령", 0, 0, 0, 0);
    this->orb[20] = Essence("헬 하운드", 0, 0, 0, 0);
    this->orb[21] = Essence("살라맨더", 0, 0, 0, 0);
    this->orb[22] = Essence("와이번", 0, 0, 0, 0);
    this->orb[23] = Essence("맨티코어", 0, 0, 0, 0);
    this->orb[24] = Essence("피닉스", 0, 0, 0, 0);
    this->orb[25] = Essence("잘못된 정보", 0, 0, 0, 0);
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
            oss << loop + 1 << ".잠겨 있는 정수(////////)\n";
        } else {
            oss << loop + 1 << "." << this->orb[loop].GetName() <<
            "의 정수(Hp: " << this->orb[loop].GetHp() <<
            " Mp: " << this->orb[loop].GetMp() <<
            " 공격력: " << this->orb[loop].GetPower() <<
            " 방어력: " << this->orb[loop].GetDefence() << ") \n";
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
        throw std::logic_error("에러! 전달 받은 인자"
                      + name + "의 정보가 존재하지 않습니다!");
    }
    // 이미 얻은 정수 선택지X
    if (!this->orb[essence].GetLock()) {
        return;
    }

    std::cout << "방금 전투한 몬스터의 정수를 발견했습니다!\n";
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
    std::cout << this->orb[essence].GetName()
              << "의 정수를 획득하셨습니다! \n";
}

void EssenceOrb::UseSkill(Monster& monster, Effect<Monster>& effect) {
    for (int loop = 0; loop < 25; loop = loop + 1) {
        if (this->orb[loop].GetEnable()) {
            this->orb[loop].Skill(monster, effect);
            return;
        }
    }

    Player& player = Player::GetInstance();
    
    std::cout << player.GetName() << "의 " << player.GetSkill() << "!!\n";
    std::cout << "(반동으로 10 데미지를 받았다)" << "!!\n";
    int  damage = 1;
    player[Pstat::Hp] -= 10;

    if (player[Pstat::Power] - monster.getdef() > 0) {
        damage = player[Pstat::Power] + 10 - monster.getdef();
    }

    monster.sethp(monster.gethp() - damage);
}

bool EssenceOrb::AllCollection() {
    for (int loop = 0; loop < 25; loop = loop + 1) {
        if (!this->orb[loop].GetLock()) {
            return false;
        }
    }
    return true;
}
