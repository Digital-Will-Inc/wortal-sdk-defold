#include "wortal_analytics.h"
#include "luautils.h"

#if defined(DM_PLATFORM_HTML5)

int WortalAnalytics::LogLevelStart(lua_State* L) {
    int top = lua_gettop(L);

    const char* level = luaL_checkstring(L, 1);
    Wortal_analytics_logLevelStart(level);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalAnalytics::LogLevelEnd(lua_State* L) {
    int top = lua_gettop(L);

    const char* level = luaL_checkstring(L, 1);
    const char* score = luaL_checkstring(L, 2);
    const int wasCompleted = luaL_checknumber(L, 3);
    Wortal_analytics_logLevelEnd(level, score, wasCompleted);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalAnalytics::LogLevelUp(lua_State* L) {
    int top = lua_gettop(L);

    const char* level = luaL_checkstring(L, 1);
    Wortal_analytics_logLevelUp(level);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalAnalytics::LogScore(lua_State* L) {
    int top = lua_gettop(L);

    const char* score = luaL_checkstring(L, 1);
    Wortal_analytics_logScore(score);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalAnalytics::LogTutorialStart(lua_State* L) {
    int top = lua_gettop(L);

    const char* tutorial = luaL_checkstring(L, 1);
    Wortal_analytics_logTutorialStart(tutorial);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalAnalytics::LogTutorialEnd(lua_State* L) {
    int top = lua_gettop(L);

    const char* tutorial = luaL_checkstring(L, 1);
    const int wasCompleted = luaL_checknumber(L, 2);
    Wortal_analytics_logTutorialEnd(tutorial, wasCompleted);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalAnalytics::LogGameChoice(lua_State* L) {
    int top = lua_gettop(L);

    const char* decision = luaL_checkstring(L, 1);
    const char* choice = luaL_checkstring(L, 2);
    Wortal_analytics_logGameChoice(decision, choice);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalAnalytics::LogSocialInvite(lua_State* L) {
    int top = lua_gettop(L);

    const char* placement = luaL_checkstring(L, 1);
    Wortal_analytics_logSocialInvite(placement);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalAnalytics::LogSocialShare(lua_State* L) {
    int top = lua_gettop(L);

    const char* placement = luaL_checkstring(L, 1);
    Wortal_analytics_logSocialShare(placement);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalAnalytics::LogPurchase(lua_State* L) {
    int top = lua_gettop(L);

    const char* productID = luaL_checkstring(L, 1);
    const char* details = luaL_checkstring(L, 2);
    Wortal_analytics_logPurchase(productID, details);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalAnalytics::LogPurchaseSubscription(lua_State* L) {
    int top = lua_gettop(L);

    const char* productID = luaL_checkstring(L, 1);
    const char* details = luaL_checkstring(L, 2);
    Wortal_analytics_logPurchaseSubscription(productID, details);

    assert(top == lua_gettop(L));
    return 0;
}

#endif
