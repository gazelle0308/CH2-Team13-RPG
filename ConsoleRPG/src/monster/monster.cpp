#include "monster/monster.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <stdexcept>

// 생성자
Monster::Monster(MonsterType monsterType)
    : hp(0), 
    mp(0), 
    atk(0), 
    def(0), 
    exp(0), 
    bonusExp(0),
    name(""),
    dropItem(""),
    regionMultiplier(1.0f),
    expMultiplier(1.0f),
    hpMultiplier(1.0f),
    mpMultiplier(1.0f),
    atkMultiplier(1.0f),
    defMultiplier(1.0f),
    type(monsterType)
{
    static bool randomSeedInitialized = false;
    if (!randomSeedInitialized)
    {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        randomSeedInitialized = true;
    }

    setMonsterData(monsterType);
    calculateExp();
}



// getter
int Monster::gethp() const
{
    return hp;
}

int Monster::getmp() const
{
    return mp;
}

int Monster::getatk() const
{
    return atk;
}

int Monster::getdef() const
{
    return def;
}

int Monster::getexp() const 
{
    return exp;
}

int Monster::getbonusExp() const 
{
    return bonusExp;
}

// setter
void Monster::sethp(int value)
{
    hp = value;
}

void Monster::setmp(int value)
{
    mp = value;
}

void Monster::setatk(int value)
{
    atk = value;
}

void Monster::setdef(int value)
{
    def = value;
}

void Monster::setexp(int value) 
{
    exp = value;
}

void Monster::setbonusExp(int value) 
{
    bonusExp = value;
}

std::string Monster::getName() const
{
    return name;
}

std::string Monster::getDropItem() const
{
    return dropItem;
}

float Monster::getRegionMultiplier() const
{
    return regionMultiplier;
}

float Monster::getExpMultiplier() const
{
    return expMultiplier;
}

// 랜덤 범위 함수
int Monster::randomRange(int minValue, int maxValue)
{
    if (minValue > maxValue)
    {
        std::swap(minValue, maxValue);
    }

    return minValue + (std::rand() % (maxValue - minValue + 1));
}


// 몬스터 랜덤 경험치 부여
int Monster::calculateExp()
{
    int totalExp =
        static_cast<int>(
            (DEFAULT_EXP + bonusExp)
            *
            expMultiplier
            );


    int minExp =
        static_cast<int>(
            totalExp * 0.9f
            );


    int maxExp =
        static_cast<int>(
            totalExp * 1.1f
            );


    exp = randomRange(
        minExp,
        maxExp
    );


    return exp;
}


// 몬스터 기본 데이터 세팅
void Monster::setMonsterData(MonsterType monsterType)
{
    switch (monsterType)
    {
        // 라벤더 들판
    case MonsterType::Slime:
        name = "슬라임";
        regionMultiplier = 0.8f;
        expMultiplier = 0.8f;
        hpMultiplier = 0.8f;
        mpMultiplier = 1.2f;
        atkMultiplier = 0.8f;
        defMultiplier = 0.8f;
        dropItem = "ITEM_MATERIAL_SLIME_GEL";
        break;

    case MonsterType::Zombie:
        name = "좀비";
        regionMultiplier = 0.8f;
        expMultiplier = 0.8f;
        hpMultiplier = 1.2f;
        mpMultiplier = 0.8f;
        atkMultiplier = 0.8f;
        defMultiplier = 1.2f;
        dropItem = "ITEM_MATERIAL_ZOMBIE_BRAIN";
        break;

    case MonsterType::Goblin:
        name = "고블린";
        regionMultiplier = 0.8f;
        expMultiplier = 0.8f;
        hpMultiplier = 0.9f;
        mpMultiplier = 1.0f;
        atkMultiplier = 1.2f;
        defMultiplier = 0.8f;
        dropItem = "ITEM_MATERIAL_GOBLIN_EAR";
        break;

    case MonsterType::WildWolf:
        name = "야생 늑대";
        regionMultiplier = 0.8f;
        expMultiplier = 0.8f;
        hpMultiplier = 1.0f;
        mpMultiplier = 0.8f;
        atkMultiplier = 1.3f;
        defMultiplier = 0.9f;
        dropItem = "ITEM_MATERIAL_WILD_WOLF_FANG";
        break;

    case MonsterType::Chimera:
        name = "키메라";
        regionMultiplier = 0.8f;
        expMultiplier = 0.8f;
        hpMultiplier = 1.1f;
        mpMultiplier = 1.1f;
        atkMultiplier = 1.1f;
        defMultiplier = 1.1f;
        dropItem = "ITEM_MATERIAL_CHIMERA_HEAD";
        break;


        // 검은 숲
    case MonsterType::Ghost:
        name = "고스트";
        regionMultiplier = 1.0f;
        expMultiplier = 1.0f;
        hpMultiplier = 0.8f;
        mpMultiplier = 1.3f;
        atkMultiplier = 1.2f;
        defMultiplier = 0.8f;
        dropItem = "ITEM_MATERIAL_GHOST_ECTOPLASM";
        break;

    case MonsterType::Succubus:
        name = "서큐버스";
        regionMultiplier = 1.0f;
        expMultiplier = 1.0f;
        hpMultiplier = 0.9f;
        mpMultiplier = 1.4f;
        atkMultiplier = 1.1f;
        defMultiplier = 0.8f;
        dropItem = "ITEM_MATERIAL_SUCCUBUS_HORN";
        break;

    case MonsterType::Incubus:
        name = "인큐버스";
        regionMultiplier = 1.0f;
        expMultiplier = 1.0f;
        hpMultiplier = 1.0f;
        mpMultiplier = 1.2f;
        atkMultiplier = 1.3f;
        defMultiplier = 0.9f;
        dropItem = "ITEM_MATERIAL_INCUBUS_TAIL";
        break;

    case MonsterType::Ghoul:
        name = "구울";
        regionMultiplier = 1.0f;
        expMultiplier = 1.0f;
        hpMultiplier = 1.3f;
        mpMultiplier = 0.8f;
        atkMultiplier = 0.9f;
        defMultiplier = 1.3f;
        dropItem = "ITEM_MATERIAL_GHOUL_CLAW";
        break;

    case MonsterType::Werewolf:
        name = "웨어울프";
        regionMultiplier = 1.0f;
        expMultiplier = 1.0f;
        hpMultiplier = 1.2f;
        mpMultiplier = 0.9f;
        atkMultiplier = 1.4f;
        defMultiplier = 1.0f;
        dropItem = "ITEM_MATERIAL_WEREWOLF_FUR";
        break;


        // 스산한 협곡
    case MonsterType::Gargoyle:
        name = "가고일";
        regionMultiplier = 1.15f;
        expMultiplier = 1.15f;
        hpMultiplier = 1.0f;
        mpMultiplier = 0.8f;
        atkMultiplier = 0.9f;
        defMultiplier = 1.5f;
        dropItem = "ITEM_MATERIAL_GARGOYLE_EYE";
        break;

    case MonsterType::Margoyle:
        name = "마고일";
        regionMultiplier = 1.15f;
        expMultiplier = 1.15f;
        hpMultiplier = 1.2f;
        mpMultiplier = 0.9f;
        atkMultiplier = 1.0f;
        defMultiplier = 1.7f;
        dropItem = "ITEM_MATERIAL_MARGOYLE_WING";
        break;

    case MonsterType::Mummy:
        name = "미라";
        regionMultiplier = 1.15f;
        expMultiplier = 1.15f;
        hpMultiplier = 1.5f;
        mpMultiplier = 0.8f;
        atkMultiplier = 1.0f;
        defMultiplier = 1.2f;
        dropItem = "ITEM_MATERIAL_MUMMY_BANDAGE";
        break;

    case MonsterType::Daemon:
        name = "데몬";
        regionMultiplier = 1.15f;
        expMultiplier = 1.15f;
        hpMultiplier = 0.9f;
        mpMultiplier = 1.4f;
        atkMultiplier = 1.6f;
        defMultiplier = 1.0f;
        dropItem = "ITEM_MATERIAL_DAEMON_FINGER";
        break;

    case MonsterType::Golem:
        name = "골렘";
        regionMultiplier = 1.15f;
        expMultiplier = 1.15f;
        hpMultiplier = 1.8f;
        mpMultiplier = 0.6f;
        atkMultiplier = 1.1f;
        defMultiplier = 2.0f;
        dropItem = "ITEM_MATERIAL_GOLEM_HEART";
        break;


        // 로야 빙원
    case MonsterType::Griffon:
        name = "그리폰";
        regionMultiplier = 1.3f;
        expMultiplier = 1.3f;
        hpMultiplier = 1.2f;
        mpMultiplier = 1.2f;
        atkMultiplier = 1.3f;
        defMultiplier = 1.5f;
        dropItem = "ITEM_MATERIAL_GRIFFON_EGG";
        break;

    case MonsterType::Vampire:
        name = "뱀파이어";
        regionMultiplier = 1.3f;
        expMultiplier = 1.3f;
        hpMultiplier = 1.0f;
        mpMultiplier = 1.5f;
        atkMultiplier = 1.5f;
        defMultiplier = 1.0f;
        dropItem = "ITEM_MATERIAL_VAMPIRE_CAPE";
        break;

    case MonsterType::Siren:
        name = "세이렌";
        regionMultiplier = 1.3f;
        expMultiplier = 1.3f;
        hpMultiplier = 1.0f;
        mpMultiplier = 1.8f;
        atkMultiplier = 1.2f;
        defMultiplier = 1.0f;
        dropItem = "ITEM_MATERIAL_SIREN_SCALE";
        break;

    case MonsterType::Minotaur:
        name = "미노타우르스";
        regionMultiplier = 1.3f;
        expMultiplier = 1.3f;
        hpMultiplier = 2.0f;
        mpMultiplier = 0.8f;
        atkMultiplier = 1.3f;
        defMultiplier = 1.5f;
        dropItem = "ITEM_MATERIAL_MINOTAUR_HOOF";
        break;


        // 로야 빙원의 강화몹
    case MonsterType::IceElemental:
        name = "얼음 정령";
        bonusExp = 100;
        regionMultiplier = 1.3f;
        expMultiplier = 1.3f;
        hpMultiplier = 3.0f;
        mpMultiplier = 3.5f;
        atkMultiplier = 2.5f;
        defMultiplier = 2.8f;
        dropItem = "ITEM_MATERIAL_ICE_ELEMENTAL_CORE";
        break;


        // 라플라 화산
    case MonsterType::HellHound:
        name = "헬 하운드";
        regionMultiplier = 1.5f;
        expMultiplier = 1.5f;
        hpMultiplier = 1.3f;
        mpMultiplier = 1.3f;
        atkMultiplier = 1.8f;
        defMultiplier = 1.2f;
        dropItem = "ITEM_MATERIAL_HELL_HOUND_COLLAR";
        break;

    case MonsterType::Wyvern:
        name = "와이번";
        regionMultiplier = 1.5f;
        expMultiplier = 1.5f;
        hpMultiplier = 2.0f;
        mpMultiplier = 1.0f;
        atkMultiplier = 1.8f;
        defMultiplier = 1.8f;
        dropItem = "ITEM_MATERIAL_WYVERN_POISON";
        break;

    case MonsterType::Salamander:
        name = "살라맨더";
        regionMultiplier = 1.5f;
        expMultiplier = 1.5f;
        hpMultiplier = 1.5f;
        mpMultiplier = 2.0f;
        atkMultiplier = 1.8f;
        defMultiplier = 1.3f;
        dropItem = "ITEM_MATERIAL_SALAMANDER_SKIN";
        break;

    case MonsterType::Manticore:
        name = "맨티코어";
        regionMultiplier = 1.5f;
        expMultiplier = 1.5f;
        hpMultiplier = 1.8f;
        mpMultiplier = 1.8f;
        atkMultiplier = 1.8f;
        defMultiplier = 1.8f;
        dropItem = "ITEM_MATERIAL_MANTICORE_TAIL";
        break;


        // 라플라 화산의 강화몹
    case MonsterType::Phoenix:
        name = "피닉스";
        bonusExp = 200;
        regionMultiplier = 1.5f;
        expMultiplier = 1.5f;
        hpMultiplier = 4.0f;
        mpMultiplier = 4.5f;
        atkMultiplier = 3.2f;
        defMultiplier = 3.0f;
        dropItem = "ITEM_MATERIAL_PHOENIX_FEATHER";
        break;

    default:
        throw std::invalid_argument(
            "Unknown MonsterType"
        );

    }
}

// 플레이어 스탯 기반으로 몬스터 실제 스탯 생성
void Monster::generateStats(
    int playerLevel,
    int playerMaxHp,
    int playerMaxMp,
    int playerPower,
    int playerDefence)
{

    // 기본 몬스터 능력치

    int baseHp =
        randomRange(
            playerLevel * 20,
            playerLevel * 30
        );


    int baseAtk =
        randomRange(
            playerLevel * 5,
            playerLevel * 10
        );



    // 플레이어 능력치 반영

    int hpFromPlayer =
        randomRange(
            playerMaxHp / 5,
            playerMaxHp / 3
        );


    int mpFromPlayer =
        randomRange(
            playerMaxMp / 5,
            playerMaxMp / 2
        );


    int atkFromPlayer =
        randomRange(
            playerPower / 2,
            playerPower
        );


    int defFromPlayer =
        randomRange(
            playerDefence / 2,
            playerDefence
        );



    // 최종 스탯 계산

    int finalHp =
        static_cast<int>(
            (baseHp + hpFromPlayer)
            *
            regionMultiplier
            *
            hpMultiplier
            );


    int finalMp =
        static_cast<int>(
            mpFromPlayer
            *
            regionMultiplier
            *
            mpMultiplier
            );


    int finalAtk =
        static_cast<int>(
            (baseAtk + atkFromPlayer)
            *
            regionMultiplier
            *
            atkMultiplier
            );


    int finalDef =
        static_cast<int>(
            (defFromPlayer + playerLevel)
            *
            regionMultiplier
            *
            defMultiplier
            );



    // 최소값 보정

    sethp(
        std::max(
            1,
            finalHp
        )
    );


    setmp(
        std::max(
            0,
            finalMp
        )
    );


    setatk(
        std::max(
            1,
            finalAtk
        )
    );


    setdef(
        std::max(
            0,
            finalDef
        )
    );
}

void Monster::Skill(Effect<Monster>& effect) {
    Player& player = Player::GetInstance();
    Effect<Player>& playerEffect = Effect<Player>::GetPlayerInstance(player);
    if (this->name == "슬라임") {
        std::cout << "[" << this->name << "] 스킬 사용!\n";
        std::cout << "방어구 손상(대상:player): 5Turn/3 DefenceDown\n";
        playerEffect.ReceiveEffect(EffectType::DefenceDown, 3, 5);
    }
    else if (this->name == "좀비") {
        std::cout << "[" << this->name << "] 스킬 사용!\n";
        std::cout << "재생(대상:monster): 10Turn/10 Regen\n";
        effect.ReceiveEffect(EffectType::Regen, 1, 10);
    }
    else if (this->name == "고블린") {
        std::cout << "[" << this->name << "] 스킬 사용!\n";
        std::cout << "방망이 타격(대상:player): 4Turn/8 Damage\n";
        playerEffect.ReceiveEffect(EffectType::Bleeding, 2, 4);
    }
    else if (this->name == "야생 늑대") {
        std::cout << "[" << this->name << "] 스킬 사용!\n";
        std::cout << "투기 강화(대상:monster): 2Turn/3 PowerUp\n";
        effect.ReceiveEffect(EffectType::PowerUp, 3, 2);
    }
    else if (this->name == "키메라") {
        std::cout << "키메라가 스킬을 사용했습니다.\n";
        std::cout << "독(대상:player): 10Turn/10 Damage\n";
        playerEffect.ReceiveEffect(EffectType::Poison, 1, 10);
    }
    else if (this->name == "고스트") {
        std::cout << "[" << this->name << "] 스킬 사용!\n";
        std::cout << "정신 침식(대상:player): 2Turn/1 ManaBurn\n";
        playerEffect.ReceiveEffect(EffectType::ManaBurn, 2, 1);
    }
    else if (this->name == "서큐버스") {
        std::cout << "[" << this->name << "] 스킬 사용!\n";
        std::cout << "매혹(대상:player): 2Turn/2 PowerDown\n";
        playerEffect.ReceiveEffect(EffectType::PowerDown, 2, 2);
    }
    else if (this->name == "인큐버스") {
        std::cout << "[" << this->name << "] 스킬 사용!\n";
        std::cout << "매혹(대상:player): 2Turn/2 DefenceDown\n";
        playerEffect.ReceiveEffect(EffectType::DefenceDown, 2, 2);
    }
    else if (this->name == "구울") {
        std::cout << "[" << this->name << "] 스킬 사용!\n";
        std::cout << "마나 침식(대상:player): 3Turn/1 ManaBurn\n";
        playerEffect.ReceiveEffect(EffectType::ManaBurn, 1, 3);
    }
    else if (this->name == "웨어울프") {
        std::cout << "[" << this->name << "] 스킬 사용!\n";
        std::cout << "고급 투기 강화(대상:monster): 4Turn/3 PowerUp\n";
        effect.ReceiveEffect(EffectType::PowerUp, 3, 4);
    }
    else if (this->name == "가고일") {
        std::cout << "[" << this->name << "] 스킬 사용!\n";
        std::cout << "경화(대상:monster): 3Turn/4 DefenceUp\n";
        effect.ReceiveEffect(EffectType::DefenceUp, 4, 3);
    }
    else if (this->name == "마고일") {
        std::cout << "[" << this->name << "] 스킬 사용!\n";
        std::cout << "칼날 경화(대상:monster): 2Turn/3 PowerUp\n";
        effect.ReceiveEffect(EffectType::PowerUp, 3, 2);
    }
    else if (this->name == "미라") {
        std::cout << "[" << this->name << "] 스킬 사용!\n";
        std::cout << "방어구 부식(대상:player): 5Turn/5 DefenceDown\n";
        playerEffect.ReceiveEffect(EffectType::DefenceDown, 5, 5);
    }
    else if (this->name == "데몬") {
        std::cout << "[" << this->name << "] 스킬 사용!\n";
        std::cout << "저주(대상:player): 3Turn/1 ManaBurn + 2 PowerDown\n";
        playerEffect.ReceiveEffect(EffectType::ManaBurn, 1, 3);
        playerEffect.ReceiveEffect(EffectType::PowerDown, 2, 3);
    }
    else if (this->name == "골렘") {
        std::cout << "[" << this->name << "] 스킬 사용!\n";
        std::cout << "고급 경화(대상:monster): 3Turn/6 DefenceUp\n";
        effect.ReceiveEffect(EffectType::DefenceUp, 6, 3);
    }
    else if (this->name == "그리폰") {
        std::cout << "[" << this->name << "] 스킬 사용!\n";
        std::cout << "순풍(대상:monster): 3Turn/4 PowerUp\n";
        effect.ReceiveEffect(EffectType::PowerUp, 4, 3);
    }
    else if (this->name == "뱀파이어") {
        std::cout << "[" << this->name << "] 스킬 사용!\n";
        std::cout << "출혈(대상:player): 5Turn/60 Damage\n";
        playerEffect.ReceiveEffect(EffectType::Bleeding, 12, 5);
    }
    else if (this->name == "세이렌") {
        std::cout << "[" << this->name << "] 스킬 사용!\n";
        std::cout << "고급 매혹(대상:player): 3Turn/3 PowerDown\n";
        playerEffect.ReceiveEffect(EffectType::PowerDown, 3, 3);
    }
    else if (this->name == "미노타우르스") {
        std::cout << "[" << this->name << "] 스킬 사용!\n";
        std::cout << "방어구 경파(대상:player): 5Turn/7 DefenceDown\n";
        playerEffect.ReceiveEffect(EffectType::DefenceDown, 7, 5);
    }
    else if (this->name == "얼음 정령") {
        std::cout << "[" << this->name << "] 스킬 사용!\n";
        std::cout << "서리 강화(대상:monster): 3Turn/8 PowerUp\n";
        effect.ReceiveEffect(EffectType::PowerUp, 8, 3);
    }
    else if (this->name == "헬 하운드") {
        std::cout << "[" << this->name << "] 스킬 사용!\n";
        std::cout << "심각한 저주(대상:player): 3Turn/3 ManaBurn + 5 PowerDown\n";
        playerEffect.ReceiveEffect(EffectType::ManaBurn, 3, 3);
        playerEffect.ReceiveEffect(EffectType::PowerDown, 5, 3);
    }
    else if (this->name == "살라맨더") {
        std::cout << "[" << this->name << "] 스킬 사용!\n";
        std::cout << "방어구 완파(대상:player): 8Turn/10 DefenceDown\n";
        playerEffect.ReceiveEffect(EffectType::DefenceDown, 10, 8);
    }
    else if (this->name == "와이번") {
        std::cout << "[" << this->name << "] 스킬 사용!\n";
        std::cout << "심각한 출혈(대상:player): 5Turn/80 Damage\n";
        playerEffect.ReceiveEffect(EffectType::Bleeding, 16, 5);
    }
    else if (this->name == "맨티코어") {
        std::cout << "[" << this->name << "] 스킬 사용!\n";
        std::cout << "맹독(대상:player): 5Turn/40 Damage\n";
        playerEffect.ReceiveEffect(EffectType::Poison, 8, 5);
    }
    else if (this->name == "피닉스") {
        std::cout << "[" << this->name << "] 스킬 사용!\n";
        std::cout << "극재생(대상:monster): 10Turn/100 Regen\n";
        effect.ReceiveEffect(EffectType::Regen, 10, 10);
    }
    else {
        throw std::out_of_range("Unknown Monster");
    }
}