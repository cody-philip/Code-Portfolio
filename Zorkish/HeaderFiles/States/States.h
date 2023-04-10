#pragma once

#include "GameState.h"
#include "Types.h"
#include "HeaderFiles/Game/WorldGraph.h"
#include "HeaderFiles/Game/GameManager.h"
#include "HeaderFiles/Commands/CommandParse.h"
#include "HeaderFiles/Commands/Invoker.h"
#include "HeaderFiles/Commands/Commands.h"

#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

class S_About : public GameState {
public:
    void render() override;
    state execute(std::string command) override;
};

class S_GamePlay : public GameState {
public:
    S_GamePlay() = default;

    void render() override;
    state execute(std::string command) override;
    static void loadWorld();
};

class S_HallOfFame : public GameState {
public:
    void render() override;
    state execute(std::string command) override;
};

class S_Help : public GameState {
public:
    void render() override;
    state execute(std::string command) override;
};

class S_HiScore : public GameState {
public:
    void render() override;
    state execute(std::string command) override;
};

class S_MainMenu : public GameState {
public:
    void render() override;
    state execute(std::string command) override;
};

class S_SelectAdventure : public GameState {
public:
    void render() override;
    state execute(std::string command) override;
};