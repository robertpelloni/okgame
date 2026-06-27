#include "stdafx.h"
#include "TournamentManager.h"
#include <algorithm>
#include <random>
#include <chrono>

std::string TournamentManager::currentTournamentId = "";
std::string TournamentManager::currentTournamentName = "";
TournamentFormat TournamentManager::currentFormat = TournamentFormat::SINGLE_ELIMINATION;
bool TournamentManager::isTournamentActive = false;
std::vector<std::string> TournamentManager::participants;
std::vector<std::shared_ptr<TournamentMatch>> TournamentManager::matches;

void TournamentManager::init() {
    isTournamentActive = false;
    currentTournamentId = "";
    currentTournamentName = "";
    participants.clear();
    matches.clear();
}

void TournamentManager::update() {
    if (isTournamentActive) {
        // Handle orchestration, bracket updates, etc.
    }
}

void TournamentManager::render() {
    // Render tournament brackets or overlay if active
}

void TournamentManager::startTournament(const std::string& name, TournamentFormat format) {
    currentTournamentName = name;
    currentTournamentId = name + "_id";
    currentFormat = format;
    isTournamentActive = true;
    matches.clear();
    Main::log.info("Tournament started: " + name);
}

void TournamentManager::joinTournament(const std::string& tournamentId) {
    currentTournamentId = tournamentId;
    isTournamentActive = true;
    participants.push_back("LocalPlayer"); // placeholder
    Main::log.info("Joined tournament: " + tournamentId);
}

void TournamentManager::leaveTournament() {
    isTournamentActive = false;
    currentTournamentId = "";
    participants.clear();
    matches.clear();
    Main::log.info("Left tournament");
}

void TournamentManager::generateBrackets() {
    if (participants.size() < 2) {
        Main::log.warn("Not enough participants to generate brackets.");
        return;
    }

    matches.clear();
    std::vector<std::string> shuffledPlayers = participants;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(shuffledPlayers.begin(), shuffledPlayers.end(), std::default_random_engine(seed));

    for (size_t i = 0; i < shuffledPlayers.size(); i += 2) {
        auto match = std::make_shared<TournamentMatch>();
        match->player1 = shuffledPlayers[i];
        if (i + 1 < shuffledPlayers.size()) {
            match->player2 = shuffledPlayers[i + 1];
        } else {
            match->player2 = "BYE";
            match->winner = match->player1;
            match->isCompleted = true;
        }
        match->round = 1;
        matches.push_back(match);
    }

    Main::log.info("Tournament brackets generated for " + std::to_string(participants.size()) + " players.");
}

void TournamentManager::submitMatchResult(const std::string& player1, const std::string& player2, const std::string& winner) {
    for (auto& match : matches) {
        if (!match->isCompleted && match->player1 == player1 && match->player2 == player2) {
            match->winner = winner;
            match->isCompleted = true;
            Main::log.info("Tournament match completed: " + winner + " wins.");
            return;
        }
    }
    Main::log.warn("Tournament match not found or already completed.");
}
