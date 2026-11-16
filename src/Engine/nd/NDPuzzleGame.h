#pragma once
#include "bobtypes.h"
#include "NDGameEngine.h"
#include "ND.h"
#include "src/Puzzle/GameLogic.h"
#include "src/Puzzle/PuzzlePlayer.h"
#include "src/Utility/ControlsManager.h"
#include <memory>

class NDPuzzleGame : public NDGameEngine {
private:
    std::shared_ptr<GameLogic> puzzleGame;
    std::shared_ptr<PuzzlePlayer> puzzlePlayer;

public:
    NDPuzzleGame(ND* nd) : NDGameEngine(nd) {}

    void init() override {
        puzzleGame = std::make_shared<GameLogic>();
        puzzlePlayer = std::make_shared<PuzzlePlayer>(puzzleGame);
        puzzleGame->player = puzzlePlayer.get();
        puzzleGame->initGame();
        puzzleGame->start();
    }

    void cleanup() override {
        puzzleGame = nullptr;
        puzzlePlayer = nullptr;
    }

    void update(float dt) override {
        if (puzzleGame && puzzlePlayer) {
            shared_ptr<ControlsManager> cm = getControlsManager();
            if (cm) {
                puzzlePlayer->UP_HELD = cm->MINIGAME_UP_HELD;
                puzzlePlayer->DOWN_HELD = cm->MINIGAME_DOWN_HELD;
                puzzlePlayer->LEFT_HELD = cm->MINIGAME_LEFT_HELD;
                puzzlePlayer->RIGHT_HELD = cm->MINIGAME_RIGHT_HELD;
                puzzlePlayer->ROTATECW_HELD = cm->MINIGAME_A_HELD;
                puzzlePlayer->ROTATECCW_HELD = cm->MINIGAME_B_HELD;
                puzzlePlayer->SLAM_HELD = cm->MINIGAME_X_HELD;
                puzzlePlayer->HOLDRAISE_HELD = cm->MINIGAME_Y_HELD;
            }
            puzzleGame->update();
        }
    }

    void render() override {
        if (puzzleGame) {
            // Render logic here
        }
    }

    void titleMenuUpdate() override {}
};
