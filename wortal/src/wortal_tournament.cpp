#include "wortal_tournament.h"
#include "luautils.h"

#if defined(DM_PLATFORM_HTML5)

lua_Listener onTournamentGetCurrentListener;
lua_Listener onTournamentGetAllListener;
lua_Listener onTournamentPostScoreListener;
lua_Listener onTournamentCreateListener;
lua_Listener onTournamentShareListener;
lua_Listener onTournamentJoinListener;

void WortalTournament::OnTournamentGetCurrent(const char* tournament, const char* error) {
    lua_State* L = onTournamentGetCurrentListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onTournamentGetCurrentListener);
    if (tournament) {
        lua_pushstring(L, tournament);
    }
    else {
        lua_pushnil(L);
    }
    if (error) {
        lua_pushstring(L, error);
    }
    else {
        lua_pushnil(L);
    }

    int ret = lua_pcall(L, 3, 0, 0);
    if (ret != 0) {
        lua_pop(L, 1);
    }

    assert(top == lua_gettop(L));
}

void WortalTournament::OnTournamentGetAll(const char* tournaments, const char* error) {
    lua_State* L = onTournamentGetAllListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onTournamentGetAllListener);
    if (tournaments) {
        lua_pushstring(L, tournaments);
    }
    else {
        lua_pushnil(L);
    }
    if (error) {
        lua_pushstring(L, error);
    }
    else {
        lua_pushnil(L);
    }

    int ret = lua_pcall(L, 3, 0, 0);
    if (ret != 0) {
        lua_pop(L, 1);
    }

    assert(top == lua_gettop(L));
}

void WortalTournament::OnTournamentPostScore(const int success, const char* error) {
    lua_State* L = onTournamentPostScoreListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onTournamentPostScoreListener);
    lua_pushboolean(L, success);
    if (error) {
        lua_pushstring(L, error);
    }
    else {
        lua_pushnil(L);
    }

    int ret = lua_pcall(L, 3, 0, 0);
    if (ret != 0) {
        lua_pop(L, 1);
    }

    assert(top == lua_gettop(L));
}

void WortalTournament::OnTournamentCreate(const char* tournament, const char* error) {
    lua_State* L = onTournamentCreateListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onTournamentCreateListener);
    if (tournament) {
        lua_pushstring(L, tournament);
    }
    else {
        lua_pushnil(L);
    }
    if (error) {
        lua_pushstring(L, error);
    }
    else {
        lua_pushnil(L);
    }

    int ret = lua_pcall(L, 3, 0, 0);
    if (ret != 0) {
        lua_pop(L, 1);
    }

    assert(top == lua_gettop(L));
}

void WortalTournament::OnTournamentShare(const int success, const char* error) {
    lua_State* L = onTournamentShareListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onTournamentShareListener);
    lua_pushboolean(L, success);
    if (error) {
        lua_pushstring(L, error);
    }
    else {
        lua_pushnil(L);
    }

    int ret = lua_pcall(L, 3, 0, 0);
    if (ret != 0) {
        lua_pop(L, 1);
    }

    assert(top == lua_gettop(L));
}

void WortalTournament::OnTournamentJoin(const int success, const char* error) {
    lua_State* L = onTournamentJoinListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onTournamentJoinListener);
    lua_pushboolean(L, success);
    if (error) {
        lua_pushstring(L, error);
    }
    else {
        lua_pushnil(L);
    }

    int ret = lua_pcall(L, 3, 0, 0);
    if (ret != 0) {
        lua_pop(L, 1);
    }

    assert(top == lua_gettop(L));
}

int WortalTournament::GetCurrentAsync(lua_State* L) {
    int top = lua_gettop(L);

    luaL_checklistener(L, 1, onTournamentGetCurrentListener);

    Wortal_tournament_getCurrentAsync(WortalTournament::OnTournamentGetCurrent);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalTournament::GetAllAsync(lua_State* L) {
    int top = lua_gettop(L);

    luaL_checklistener(L, 1, onTournamentGetAllListener);

    Wortal_tournament_getAllAsync(WortalTournament::OnTournamentGetAll);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalTournament::PostScoreAsync(lua_State* L) {
    int top = lua_gettop(L);

    luaL_checklistener(L, 1, onTournamentPostScoreListener);

    int score = luaL_checkinteger(L, 2);

    Wortal_tournament_postScoreAsync(score, WortalTournament::OnTournamentPostScore);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalTournament::CreateAsync(lua_State* L) {
    int top = lua_gettop(L);

    luaL_checklistener(L, 1, onTournamentCreateListener);

    const char* payload = luaL_checkstring(L, 2);

    Wortal_tournament_createAsync(payload, WortalTournament::OnTournamentCreate);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalTournament::ShareAsync(lua_State* L) {
    int top = lua_gettop(L);

    luaL_checklistener(L, 1, onTournamentShareListener);

    const char* payload = luaL_checkstring(L, 2);

    Wortal_tournament_shareAsync(payload, WortalTournament::OnTournamentShare);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalTournament::JoinAsync(lua_State* L) {
    int top = lua_gettop(L);

    luaL_checklistener(L, 1, onTournamentJoinListener);

    const char* tournamentID = luaL_checkstring(L, 2);

    Wortal_tournament_joinAsync(tournamentID, WortalTournament::OnTournamentJoin);

    assert(top == lua_gettop(L));
    return 0;
}

#endif
