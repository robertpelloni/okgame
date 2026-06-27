#pragma once
#include "bobtypes.h"
#include <string>
#include <vector>
#include <memory>

enum class TournamentFormat {
    SINGLE_ELIMINATION,
    DOUBLE_ELIMINATION,
    ROUND_ROBIN
};

struct TournamentMatch {
    std::string player1;
    std::string player2;
    std::string winner;
    int round;
    bool isCompleted = false;
};

class TournamentManager {
public:
    static void init();
    static void update();
    static void render();

    static void startTournament(const std::string& name, TournamentFormat format = TournamentFormat::SINGLE_ELIMINATION);
    static void joinTournament(const std::string& tournamentId);
    static void leaveTournament();
    static void generateBrackets();
    static void submitMatchResult(const std::string& player1, const std::string& player2, const std::string& winner);

    static std::string currentTournamentId;
    static std::string currentTournamentName;
    static TournamentFormat currentFormat;
    static bool isTournamentActive;
    static std::vector<std::string> participants;
    static std::vector<std::shared_ptr<TournamentMatch>> matches;
};
