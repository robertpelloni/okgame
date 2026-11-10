#ifndef STEAMMANAGER_H
#define STEAMMANAGER_H

#include "stdafx.h"
#include <vector>
#include <utility>

#ifdef HAVE_STEAMWORKS
#include <steam/steam_api.h>
#endif

class SteamManager {
public:
    static void init();
    static void update();
    static void shutdown();

    static void setAchievement(const string& id);
    static bool getAchievement(const string& id, bool* achieved);
    static bool clearAchievement(const string& id);
    static bool isOverlayEnabled();
    static void activateGameOverlay(const string& dialog);
    static bool setRichPresence(const string& key, const string& value);
    static void clearRichPresence();
    static bool resetAllStats(bool achievementsToo);
    static void setStat(const string& id, int value);
    static bool getStat(const string& id, int* value);
    static void setStat(const string& id, float value);
    static bool getStat(const string& id, float* value);

    static bool isSteamRunning();
    static uint64_t getSteamID();
    static string getPersonaName();

    static vector<pair<uint64_t, string>> getFriends();

    static bool writeCloudFile(const string& filename, const string& data);
    static string readCloudFile(const string& filename);
    static bool isCloudEnabled();

private:
#ifdef HAVE_STEAMWORKS
    // Steam callbacks
    // STEAM_CALLBACK(SteamManager, onUserStatsReceived, UserStatsReceived_t);
#endif
};

#endif
