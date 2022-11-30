#include "wortalsdk.h"
#include "luautils.h"
#include <dmsdk/sdk.h>

#define EXTENSION_NAME WortalSDK
#define LIB_NAME "WortalSdk"
#define MODULE_NAME "wortal"
#define VERSION "2.0.0"

#if defined(DM_PLATFORM_HTML5)

//////////////////////////////////////////////////////////////////////
// Ads API
//////////////////////////////////////////////////////////////////////

lua_Listener onBeforeAdListener;
lua_Listener onAfterAdListener;
lua_Listener onAdDismissedListener;
lua_Listener onAdViewedListener;

static void WortalSdk_OnBeforeAd() {
    lua_State* L = onBeforeAdListener.m_L;
	int top = lua_gettop(L);

    lua_pushlistener(L, onBeforeAdListener);

    int ret = lua_pcall(L, 1, 0, 0);
	if (ret != 0) {
		dmLogInfo("[Wortal] OnBeforeAd callback contains an error.");
		lua_pop(L, 1);
	}

    assert(top == lua_gettop(L));
}

static void WortalSdk_OnAfterAd() {
    lua_State* L = onAfterAdListener.m_L;
	int top = lua_gettop(L);

    lua_pushlistener(L, onAfterAdListener);

    int ret = lua_pcall(L, 1, 0, 0);
	if (ret != 0) {
		dmLogInfo("[Wortal] OnAfterAd callback contains an error.");
		lua_pop(L, 1);
	}

    assert(top == lua_gettop(L));
}

static void WortalSdk_OnAdDismissed() {
    lua_State* L = onAdDismissedListener.m_L;
	int top = lua_gettop(L);

    lua_pushlistener(L, onAdDismissedListener);

    int ret = lua_pcall(L, 1, 0, 0);
	if (ret != 0) {
		dmLogInfo("[Wortal] OnAdDismissed callback contains an error.");
		lua_pop(L, 1);
	}

    assert(top == lua_gettop(L));
}

static void WortalSdk_OnAdViewed() {
    lua_State* L = onAdViewedListener.m_L;
	int top = lua_gettop(L);

    lua_pushlistener(L, onAdViewedListener);

    int ret = lua_pcall(L, 1, 0, 0);
	if (ret != 0) {
		dmLogInfo("[Wortal] OnAdViewed callback contains an error.");
		lua_pop(L, 1);
	}

    assert(top == lua_gettop(L));
}

static int WortalSdk_ShowInterstitial(lua_State* L) {
    int top = lua_gettop(L);

    const char* type = luaL_checkstring(L, 1);
    const char* description = luaL_checkstring(L, 2);
    luaL_checklistener(L, 3, onBeforeAdListener);
    luaL_checklistener(L, 4, onAfterAdListener);

    Wortal_ads_showInterstitial(type,description, (OnBeforeAdCallback)WortalSdk_OnBeforeAd,
                                (OnAfterAdCallback)WortalSdk_OnAfterAd);

    assert(top == lua_gettop(L));
    return 0;
}

static int WortalSdk_ShowRewarded(lua_State* L) {
    int top = lua_gettop(L);

    const char* description = luaL_checkstring(L, 1);
    luaL_checklistener(L, 2, onBeforeAdListener);
    luaL_checklistener(L, 3, onAfterAdListener);
    luaL_checklistener(L, 4, onAdDismissedListener);
    luaL_checklistener(L, 5, onAdViewedListener);

    Wortal_ads_showRewarded(description, (OnBeforeAdCallback)WortalSdk_OnBeforeAd, (OnAfterAdCallback)WortalSdk_OnAfterAd,
        (OnAdDismissedCallback)WortalSdk_OnAdDismissed, (OnAdViewedCallback)WortalSdk_OnAdViewed);

    assert(top == lua_gettop(L));
    return 0;
}

//////////////////////////////////////////////////////////////////////
// Analytics API
//////////////////////////////////////////////////////////////////////

static int WortalSdk_LogLevelStart(lua_State* L) {
    int top = lua_gettop(L);

    const char* level = luaL_checkstring(L, 1);
    Wortal_analytics_logLevelStart(level);

    assert(top == lua_gettop(L));
    return 0;
}

static int WortalSdk_LogLevelEnd(lua_State* L) {
    int top = lua_gettop(L);

    const char* level = luaL_checkstring(L, 1);
    const char* score = luaL_checkstring(L, 2);
    const int wasCompleted = luaL_checknumber(L, 3);
    Wortal_analytics_logLevelEnd(level, score, wasCompleted);

    assert(top == lua_gettop(L));
    return 0;
}

static int WortalSdk_LogLevelUp(lua_State* L) {
    int top = lua_gettop(L);

    const char* level = luaL_checkstring(L, 1);
    Wortal_analytics_logLevelUp(level);

    assert(top == lua_gettop(L));
    return 0;
}

static int WortalSdk_LogScore(lua_State* L) {
    int top = lua_gettop(L);

    const char* score = luaL_checkstring(L, 1);
    Wortal_analytics_logScore(score);

    assert(top == lua_gettop(L));
    return 0;
}

static int WortalSdk_LogTutorialStart(lua_State* L) {
    int top = lua_gettop(L);

    const char* tutorial = luaL_checkstring(L, 1);
    Wortal_analytics_logTutorialStart(tutorial);

    assert(top == lua_gettop(L));
    return 0;
}

static int WortalSdk_LogTutorialEnd(lua_State* L) {
    int top = lua_gettop(L);

    const char* tutorial = luaL_checkstring(L, 1);
    const int wasCompleted = luaL_checknumber(L, 2);
    Wortal_analytics_logTutorialEnd(tutorial, wasCompleted);

    assert(top == lua_gettop(L));
    return 0;
}

static int WortalSdk_LogGameChoice(lua_State* L) {
    int top = lua_gettop(L);

    const char* decision = luaL_checkstring(L, 1);
    const char* choice = luaL_checkstring(L, 2);
    Wortal_analytics_logGameChoice(decision, choice);

    assert(top == lua_gettop(L));
    return 0;
}

//////////////////////////////////////////////////////////////////////
// Context API
//////////////////////////////////////////////////////////////////////

// Functions exposed to Lua
static const luaL_reg Module_methods[] = {
    {"ads_show_interstitial", WortalSdk_ShowInterstitial},
    {"ads_show_rewarded", WortalSdk_ShowRewarded},

    {"analytics_log_level_start", WortalSdk_LogLevelStart},
    {"analytics_log_level_end", WortalSdk_LogLevelEnd},
    {"analytics_log_level_up", WortalSdk_LogLevelUp},
    {"analytics_log_score", WortalSdk_LogScore},
    {"analytics_log_tutorial_start", WortalSdk_LogTutorialStart},
    {"analytics_log_tutorial_end", WortalSdk_LogTutorialEnd},
    {"analytics_log_game_choice", WortalSdk_LogGameChoice},

    {0, 0}
};

static void LuaInit(lua_State* L) {
    int top = lua_gettop(L);

    luaL_register(L, MODULE_NAME, Module_methods);

    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}

dmExtension::Result InitializeWortalSdk(dmExtension::Params* params) {
    LuaInit(params->m_L);
    return dmExtension::RESULT_OK;
}

dmExtension::Result FinalizeWortalSdk(dmExtension::Params* params) {
    return dmExtension::RESULT_OK;
}

#else // unsupported platforms

dmExtension::Result InitializeWortalSdk(dmExtension::Params* params) {
    return dmExtension::RESULT_OK;
}

dmExtension::Result FinalizeWortalSdk(dmExtension::Params* params) {
    return dmExtension::RESULT_OK;
}

#endif

DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, 0, 0, InitializeWortalSdk, 0, 0, FinalizeWortalSdk)
