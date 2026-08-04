// Copyright 2026/08/03 minjung

#pragma once

class GameManager {
public:
    void Run();

private:
    void Init();
    void VillageMenu() const;
    int GetMenuChoice() const;
    void HandleMenuChoice(int choice, bool& isRunning);
    void EnterBattle();
};