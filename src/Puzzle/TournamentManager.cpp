#include "stdafx.h"
#include "TournamentManager.h"

std::string TournamentManager::currentTournamentId = "";
bool TournamentManager::isTournamentActive = false;
std::vector<std::string> TournamentManager::participants;

void TournamentManager::init() {
    isTournamentActive = false;
    currentTournamentId = "";
    participants.clear();
}

void TournamentManager::update() {
    if (isTournamentActive) {
        // Handle orchestration, bracket updates, etc.
    }
}

void TournamentManager::render() {
    // Render tournament brackets or overlay if active
}

void TournamentManager::startTournament(const std::string& name) {
    currentTournamentId = name + "_id";
    isTournamentActive = true;
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
    Main::log.info("Left tournament");
}
