#pragma once

#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_HTML5)

class WortalTournament {
public:
    typedef void (*OnTournamentGetCurrentCallback)(const char* tournament, const char* error);
    typedef void (*OnTournamentGetAllCallback)(const char* tournaments, const char* error);
    typedef void (*OnTournamentPostScoreCallback)(const int success, const char* error);
    typedef void (*OnTournamentCreateCallback)(const char* tournament, const char* error);
    typedef void (*OnTournamentShareCallback)(const int success, const char* error);
    typedef void (*OnTournamentJoinCallback)(const int success, const char* error);

    static int GetCurrentAsync(lua_State* L);
    static int GetAllAsync(lua_State* L);
    static int PostScoreAsync(lua_State* L);
    static int CreateAsync(lua_State* L);
    static int ShareAsync(lua_State* L);
    static int JoinAsync(lua_State* L);

private:
    static void OnTournamentGetCurrent(const char* tournament, const char* error);
    static void OnTournamentGetAll(const char* tournaments, const char* error);
    static void OnTournamentPostScore(const int success, const char* error);
    static void OnTournamentCreate(const char* tournament, const char* error);
    static void OnTournamentShare(const int success, const char* error);
    static void OnTournamentJoin(const int success, const char* error);
};

extern "C" {
    void Wortal_tournament_getCurrentAsync(WortalTournament::OnTournamentGetCurrentCallback callback);
    void Wortal_tournament_getAllAsync(WortalTournament::OnTournamentGetAllCallback callback);
    void Wortal_tournament_postScoreAsync(const int score, WortalTournament::OnTournamentPostScoreCallback callback);
    void Wortal_tournament_createAsync(const char* payload, WortalTournament::OnTournamentCreateCallback callback);
    void Wortal_tournament_shareAsync(const char* payload, WortalTournament::OnTournamentShareCallback callback);
    void Wortal_tournament_joinAsync(const char* tournamentID, WortalTournament::OnTournamentJoinCallback callback);
}

#endif
