#pragma once
#include <string>

class SteamworksAPI {
public:
    static bool init();
    static void shutdown();

    static void initSteamUser();
    static void initSteamFriends();
    static void initSteamCloud();
};
