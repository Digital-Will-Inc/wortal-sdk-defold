#pragma once

#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_HTML5)

class WortalLeaderboard {
public:
    typedef void (*OnGetLeaderboardCallback)(const char* leaderboard, const char* error);
    typedef void (*OnLeaderboardSendEntryCallback)(const char* entry, const char* error);
    typedef void (*OnLeaderboardGetEntriesCallback)(const char* entries, const char* error);
    typedef void (*OnLeaderboardGetPlayerEntryCallback)(const char* entry, const char* error);
    typedef void (*OnLeaderboardGetEntryCountCallback)(const int count, const char* error);
    typedef void (*OnLeaderboardGetConnectedPlayersEntriesCallback)(const char* entries, const char* error);

    static int GetLeaderboardAsync(lua_State* L);
    static int SendEntryAsync(lua_State* L);
    static int GetEntriesAsync(lua_State* L);
    static int GetPlayerEntryAsync(lua_State* L);
    static int GetEntryCountAsync(lua_State* L);
    static int GetConnectedPlayersEntriesAsync(lua_State* L);

private:
    static void OnGetLeaderboard(const char* leaderboard, const char* error);
    static void OnSendEntry(const char* entry, const char* error);
    static void OnGetEntries(const char* entries, const char* error);
    static void OnGetPlayerEntry(const char* entry, const char* error);
    static void OnGetEntryCount(const int count, const char* error);
    static void OnGetConnectedPlayersEntries(const char* entries, const char* error);
};

extern "C" {
    void Wortal_leaderboard_getLeaderboardAsync(const char* leaderboard, WortalLeaderboard::OnGetLeaderboardCallback callback);
    void Wortal_leaderboard_sendEntryAsync(const char* leaderboard, const int score, const char* details, WortalLeaderboard::OnLeaderboardSendEntryCallback callback);
    void Wortal_leaderboard_getEntriesAsync(const char* leaderboard, const int count, const int offset, WortalLeaderboard::OnLeaderboardGetEntriesCallback callback);
    void Wortal_leaderboard_getPlayerEntryAsync(const char* leaderboard, WortalLeaderboard::OnLeaderboardGetPlayerEntryCallback callback);
    void Wortal_leaderboard_getEntryCountAsync(const char* leaderboard, WortalLeaderboard::OnLeaderboardGetEntryCountCallback callback);
    void Wortal_leaderboard_getConnectedPlayersEntriesAsync(const char* leaderboard, const int count, const int offset, WortalLeaderboard::OnLeaderboardGetConnectedPlayersEntriesCallback callback);
}

#endif
