#pragma once
#include "bobtypes.h"
#include <string>
#include <vector>

class TournamentManager {
public:
    static void init();
    static void update();
    static void render();

    static void startTournament(const std::string& name);
    static void joinTournament(const std::string& tournamentId);
    static void leaveTournament();

    static std::string currentTournamentId;
    static bool isTournamentActive;
    static std::vector<std::string> participants;
};
