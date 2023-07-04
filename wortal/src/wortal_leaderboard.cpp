#include "wortal_leaderboard.h"
#include "luautils.h"

#if defined(DM_PLATFORM_HTML5)

lua_Listener onLeaderboardGetLeaderboardListener;
lua_Listener onLeaderboardSendEntryListener;
lua_Listener onLeaderboardGetEntriesListener;
lua_Listener onLeaderboardGetPlayerEntryListener;
lua_Listener onLeaderboardGetEntryCountListener;
lua_Listener onLeaderboardGetConnectedPlayersEntriesListener;

void WortalLeaderboard::OnGetLeaderboard(const char* leaderboard, const char* error) {
    lua_State* L = onLeaderboardGetLeaderboardListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onLeaderboardGetLeaderboardListener);
    if (leaderboard) {
        lua_pushstring(L, leaderboard);
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

void WortalLeaderboard::OnSendEntry(const char* entry, const char* error) {
    lua_State* L = onLeaderboardSendEntryListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onLeaderboardSendEntryListener);
    if (entry) {
        lua_pushstring(L, entry);
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

void WortalLeaderboard::OnGetEntries(const char* entries, const char* error) {
    lua_State* L = onLeaderboardGetEntriesListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onLeaderboardGetEntriesListener);
    if (entries) {
        lua_pushstring(L, entries);
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

void WortalLeaderboard::OnGetPlayerEntry(const char* entry, const char* error) {
    lua_State* L = onLeaderboardGetPlayerEntryListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onLeaderboardGetPlayerEntryListener);
    if (entry) {
        lua_pushstring(L, entry);
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

void WortalLeaderboard::OnGetEntryCount(const int count, const char* error) {
    lua_State* L = onLeaderboardGetEntryCountListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onLeaderboardGetEntryCountListener);
    lua_pushnumber(L, count);
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

void WortalLeaderboard::OnGetConnectedPlayersEntries(const char* entries, const char* error) {
    lua_State* L = onLeaderboardGetConnectedPlayersEntriesListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onLeaderboardGetConnectedPlayersEntriesListener);
    if (entries) {
        lua_pushstring(L, entries);
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

int WortalLeaderboard::GetLeaderboardAsync(lua_State* L) {
    int top = lua_gettop(L);

    const char* leaderboard = luaL_checkstring(L, 1);
    luaL_checklistener(L, 2, onLeaderboardGetLeaderboardListener);
    Wortal_leaderboard_getLeaderboardAsync(leaderboard, WortalLeaderboard::OnGetLeaderboard);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalLeaderboard::SendEntryAsync(lua_State* L) {
    int top = lua_gettop(L);

    const char* leaderboard = luaL_checkstring(L, 1);
    const int score = luaL_checknumber(L, 2);
    const char* details;
    if (lua_isstring(L, 3)) {
        details = luaL_checkstring(L, 3);
        luaL_checklistener(L, 4, onLeaderboardSendEntryListener);
    }
    else {
        details = "";
        luaL_checklistener(L, 3, onLeaderboardSendEntryListener);
    }
    Wortal_leaderboard_sendEntryAsync(leaderboard, score, details, WortalLeaderboard::OnSendEntry);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalLeaderboard::GetEntriesAsync(lua_State* L) {
    int top = lua_gettop(L);

    const char* leaderboard = luaL_checkstring(L, 1);
    const int count = luaL_checknumber(L, 2);
    int offset;
    if (lua_isnumber(L, 3)) {
        offset = luaL_checknumber(L, 3);
        luaL_checklistener(L, 4, onLeaderboardGetEntriesListener);
    }
    else {
        offset = 0;
        luaL_checklistener(L, 3, onLeaderboardGetEntriesListener);
    }
    Wortal_leaderboard_getEntriesAsync(leaderboard, count, offset, WortalLeaderboard::OnGetEntries);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalLeaderboard::GetPlayerEntryAsync(lua_State* L) {
    int top = lua_gettop(L);

    const char* leaderboard = luaL_checkstring(L, 1);
    luaL_checklistener(L, 2, onLeaderboardGetPlayerEntryListener);
    Wortal_leaderboard_getPlayerEntryAsync(leaderboard, WortalLeaderboard::OnGetPlayerEntry);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalLeaderboard::GetEntryCountAsync(lua_State* L) {
    int top = lua_gettop(L);

    const char* leaderboard = luaL_checkstring(L, 1);
    luaL_checklistener(L, 2, onLeaderboardGetEntryCountListener);
    Wortal_leaderboard_getEntryCountAsync(leaderboard, WortalLeaderboard::OnGetEntryCount);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalLeaderboard::GetConnectedPlayersEntriesAsync(lua_State* L) {
    int top = lua_gettop(L);

    const char* leaderboard = luaL_checkstring(L, 1);
    const int count = luaL_checknumber(L, 2);
    int offset;
    if (lua_isnumber(L, 3)) {
        offset = luaL_checknumber(L, 3);
        luaL_checklistener(L, 4, onLeaderboardGetConnectedPlayersEntriesListener);
    }
    else {
        offset = 0;
        luaL_checklistener(L, 3, onLeaderboardGetConnectedPlayersEntriesListener);
    }
    Wortal_leaderboard_getConnectedPlayersEntriesAsync(leaderboard, count, offset, WortalLeaderboard::OnGetConnectedPlayersEntries);

    assert(top == lua_gettop(L));
    return 0;
}

#endif
