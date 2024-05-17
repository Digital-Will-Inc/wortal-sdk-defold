#include "wortal_stats.h"
#include "luautils.h"

#if defined(DM_PLATFORM_HTML5)

lua_Listener onGetStatsListener;
lua_Listener onPostStatsListener;

void WortalStats::OnGetStats(const char* stats, const char* error) {
    lua_State* L = onGetStatsListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onGetStatsListener);
    if (stats) {
        lua_pushstring(L, stats);
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

void WortalStats::OnPostStats(const int success, const char* error) {
    lua_State* L = onPostStatsListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onPostStatsListener);
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

int WortalStats::GetStatsAsync(lua_State* L) {
    int top = lua_gettop(L);

    luaL_checklistener(L, 1, onGetStatsListener);
    const char* level = luaL_checkstring(L, 2);
    const char* payload = luaL_checkstring(L, 3);
    Wortal_stats_getStatsAsync(level, payload, WortalStats::OnGetStats);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalStats::PostStatsAsync(lua_State* L) {
    int top = lua_gettop(L);

    luaL_checklistener(L, 1, onPostStatsListener);
    const char* level = luaL_checkstring(L, 2);
    const int value = luaL_checkint(L, 3);
    const char* payload = luaL_checkstring(L, 4);
    Wortal_stats_postStatsAsync(level, value, payload, WortalStats::OnPostStats);

    assert(top == lua_gettop(L));
    return 0;
}

#endif
