#include "wortal_achievements.h"
#include "luautils.h"

#if defined(DM_PLATFORM_HTML5)

lua_Listener onGetAchievementsListener;
lua_Listener onUnlockAchievementListener;

void WortalAchievements::OnGetAchievements(const char* achievements, const char* error) {
    lua_State* L = onGetAchievementsListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onGetAchievementsListener);
    if (achievements) {
        lua_pushstring(L, achievements);
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

void WortalAchievements::OnUnlockAchievement(const int unlockResult, const char* error) {
    lua_State* L = onUnlockAchievementListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onUnlockAchievementListener);
    lua_pushboolean(L, unlockResult);
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

int WortalAchievements::GetAchievementsAsync(lua_State* L) {
    int top = lua_gettop(L);

    luaL_checklistener(L, 1, onGetAchievementsListener);
    Wortal_achievements_getAchievementsAsync(WortalAchievements::OnGetAchievements);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalAchievements::UnlockAchievementAsync(lua_State* L) {
    int top = lua_gettop(L);

    luaL_checklistener(L, 1, onUnlockAchievementListener);
    const char* achievementId = luaL_checkstring(L, 2);
    Wortal_achievements_unlockAchievementAsync(achievementId, WortalAchievements::OnUnlockAchievement);

    assert(top == lua_gettop(L));
    return 0;
}

#endif
