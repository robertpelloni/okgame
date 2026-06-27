#include "stdafx.h"
#include "SteamworksAPI.h"
#include "SteamManager.h"

bool SteamworksAPI::init() {
    SteamManager::init();
    return SteamManager::isSteamRunning();
}

void SteamworksAPI::shutdown() {
    SteamManager::shutdown();
}

void SteamworksAPI::initSteamUser() {
    if (!SteamManager::isSteamRunning()) return;
    // Core user init
}

void SteamworksAPI::initSteamFriends() {
    if (!SteamManager::isSteamRunning()) return;
    // Core friends init
}

void SteamworksAPI::initSteamCloud() {
    if (!SteamManager::isSteamRunning()) return;
    // Core cloud init
}
