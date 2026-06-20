//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once

#include "bobtypes.h"

class Logger;

class BobsGameUserStats
{
public:

	long long userID = 0;
	string userName = "";

	string isGameTypeOrSequence = "";
	string gameTypeName = "";
	string gameTypeUUID = "";
	string gameSequenceName = "";
	string gameSequenceUUID = "";
	string difficultyName = "";
	string objectiveString = "";

	int totalGamesPlayed = 0;
	int singlePlayerGamesPlayed = 0;
	int tournamentGamesPlayed = 0;
	int localMultiplayerGamesPlayed = 0;

	int tournamentGamesWon = 0;
	int tournamentGamesLost = 0;

	int singlePlayerGamesCompleted = 0;
	int singlePlayerGamesLost = 0;
	int singlePlayerHighestLevelReached = 0;

	long long totalTimePlayed = 0;
	long long longestGameLength = 0;
	long long averageGameLength = 0;
	long long fastestClearedLength = 0;

	double eloScore = 1200.0;

	long long firstTimePlayed = 0;
	long long lastTimePlayed = 0;

	long long planesWalkerPoints = 0;

	long long totalBlocksMade = 0;
	long long totalPiecesMade = 0;
	long long totalBlocksCleared = 0;
	long long totalPiecesPlaced = 0;

	long long totalCombosMade = 0;
	int biggestCombo = 0;
	int mostBlocksCleared = 0;

	string longestTimeStatsUUID = "";
	string fastestTimeClearedStatsUUID = "";
	string mostBlocksClearedStatsUUID = "";

	// TODO: implement JSON encoding/decoding if needed, using rapidjson or similar
};
