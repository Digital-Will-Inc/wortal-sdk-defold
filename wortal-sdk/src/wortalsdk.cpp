#include "wortalsdk.h"
#include "luautils.h"
#include <dmsdk/sdk.h>

#define EXTENSION_NAME WortalSDK
#define LIB_NAME "WortalSdk"
#define MODULE_NAME "wortal"
#define VERSION "2.0.0"

#if defined(DM_PLATFORM_HTML5)

//////////////////////////////////////////////////////////////////////
// API error handler
//////////////////////////////////////////////////////////////////////
lua_Listener onErrorListener;

static void Wortal_OnError(const char* error) {
    lua_State* L = onErrorListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onErrorListener);
    lua_pushstring(L, error);

    int ret = lua_pcall(L, 2, 0, 0);
    if (ret != 0) {
        lua_pop(L, 1);
    }

    assert(top == lua_gettop(L));
}

//////////////////////////////////////////////////////////////////////
// Ads API
//////////////////////////////////////////////////////////////////////

lua_Listener onBeforeAdListener;
lua_Listener onAfterAdListener;
lua_Listener onAdDismissedListener;
lua_Listener onAdViewedListener;

static void Wortal_Ads_OnBeforeAd() {
    lua_State* L = onBeforeAdListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onBeforeAdListener);

    int ret = lua_pcall(L, 1, 0, 0);
    if (ret != 0) {
        lua_pop(L, 1);
    }

    assert(top == lua_gettop(L));
}

static void Wortal_Ads_OnAfterAd() {
    lua_State* L = onAfterAdListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onAfterAdListener);

    int ret = lua_pcall(L, 1, 0, 0);
    if (ret != 0) {
        lua_pop(L, 1);
    }

    assert(top == lua_gettop(L));
}

static void Wortal_Ads_OnAdDismissed() {
    lua_State* L = onAdDismissedListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onAdDismissedListener);

    int ret = lua_pcall(L, 1, 0, 0);
    if (ret != 0) {
        lua_pop(L, 1);
    }

    assert(top == lua_gettop(L));
}

static void Wortal_Ads_OnAdViewed() {
    lua_State* L = onAdViewedListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onAdViewedListener);

    int ret = lua_pcall(L, 1, 0, 0);
    if (ret != 0) {
        lua_pop(L, 1);
    }

    assert(top == lua_gettop(L));
}

static int Wortal_Ads_ShowInterstitial(lua_State* L) {
    int top = lua_gettop(L);

    const char* type = luaL_checkstring(L, 1);
    const char* description = luaL_checkstring(L, 2);
    luaL_checklistener(L, 3, onBeforeAdListener);
    luaL_checklistener(L, 4, onAfterAdListener);

    Wortal_ads_showInterstitial(type,description, (OnBeforeAdCallback)Wortal_Ads_OnBeforeAd,
                                (OnAfterAdCallback)Wortal_Ads_OnAfterAd);

    assert(top == lua_gettop(L));
    return 0;
}

static int Wortal_Ads_ShowRewarded(lua_State* L) {
    int top = lua_gettop(L);

    const char* description = luaL_checkstring(L, 1);
    luaL_checklistener(L, 2, onBeforeAdListener);
    luaL_checklistener(L, 3, onAfterAdListener);
    luaL_checklistener(L, 4, onAdDismissedListener);
    luaL_checklistener(L, 5, onAdViewedListener);

    Wortal_ads_showRewarded(description, (OnBeforeAdCallback)Wortal_Ads_OnBeforeAd, (OnAfterAdCallback)Wortal_Ads_OnAfterAd,
        (OnAdDismissedCallback)Wortal_Ads_OnAdDismissed, (OnAdViewedCallback)Wortal_Ads_OnAdViewed);

    assert(top == lua_gettop(L));
    return 0;
}

//////////////////////////////////////////////////////////////////////
// Analytics API
//////////////////////////////////////////////////////////////////////

static int Wortal_Analytics_LogLevelStart(lua_State* L) {
    int top = lua_gettop(L);

    const char* level = luaL_checkstring(L, 1);
    Wortal_analytics_logLevelStart(level);

    assert(top == lua_gettop(L));
    return 0;
}

static int Wortal_Analytics_LogLevelEnd(lua_State* L) {
    int top = lua_gettop(L);

    const char* level = luaL_checkstring(L, 1);
    const char* score = luaL_checkstring(L, 2);
    const int wasCompleted = luaL_checknumber(L, 3);
    Wortal_analytics_logLevelEnd(level, score, wasCompleted);

    assert(top == lua_gettop(L));
    return 0;
}

static int Wortal_Analytics_LogLevelUp(lua_State* L) {
    int top = lua_gettop(L);

    const char* level = luaL_checkstring(L, 1);
    Wortal_analytics_logLevelUp(level);

    assert(top == lua_gettop(L));
    return 0;
}

static int Wortal_Analytics_LogScore(lua_State* L) {
    int top = lua_gettop(L);

    const char* score = luaL_checkstring(L, 1);
    Wortal_analytics_logScore(score);

    assert(top == lua_gettop(L));
    return 0;
}

static int Wortal_Analytics_LogTutorialStart(lua_State* L) {
    int top = lua_gettop(L);

    const char* tutorial = luaL_checkstring(L, 1);
    Wortal_analytics_logTutorialStart(tutorial);

    assert(top == lua_gettop(L));
    return 0;
}

static int Wortal_Analytics_LogTutorialEnd(lua_State* L) {
    int top = lua_gettop(L);

    const char* tutorial = luaL_checkstring(L, 1);
    const int wasCompleted = luaL_checknumber(L, 2);
    Wortal_analytics_logTutorialEnd(tutorial, wasCompleted);

    assert(top == lua_gettop(L));
    return 0;
}

static int Wortal_Analytics_LogGameChoice(lua_State* L) {
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

lua_Listener onContextChooseListener;
lua_Listener onContextShareListener;
lua_Listener onContextUpdateListener;
lua_Listener onContextSwitchListener;
lua_Listener onContextCreateListener;

static void Wortal_Context_OnContextChoose() {
    lua_State* L = onContextChooseListener.m_L;
	int top = lua_gettop(L);

    lua_pushlistener(L, onContextChooseListener);
    int ret = lua_pcall(L, 1, 0, 0);
    if (ret != 0) {
        lua_pop(L, 1);
    }

    assert(top == lua_gettop(L));
}

static void Wortal_Context_OnContextShare(const int shareResult) {
    lua_State* L = onContextShareListener.m_L;
	int top = lua_gettop(L);

    lua_pushlistener(L, onContextShareListener);
    lua_pushnumber(L, shareResult);

	int ret = lua_pcall(L, 3, 0, 0);
	if (ret != 0) {
		lua_pop(L, 1);
	}

	assert(top == lua_gettop(L));
}

static void Wortal_Context_OnContextUpdate() {
    lua_State* L = onContextUpdateListener.m_L;
	int top = lua_gettop(L);

    lua_pushlistener(L, onContextUpdateListener);
    int ret = lua_pcall(L, 1, 0, 0);
    if (ret != 0) {
        lua_pop(L, 1);
    }

    assert(top == lua_gettop(L));
}

static void Wortal_Context_OnContextSwitch() {
    lua_State* L = onContextSwitchListener.m_L;
	int top = lua_gettop(L);

    lua_pushlistener(L, onContextSwitchListener);
    int ret = lua_pcall(L, 1, 0, 0);
    if (ret != 0) {
        lua_pop(L, 1);
    }

    assert(top == lua_gettop(L));
}

static void Wortal_Context_OnContextCreate() {
    lua_State* L = onContextCreateListener.m_L;
	int top = lua_gettop(L);

    lua_pushlistener(L, onContextCreateListener);
    int ret = lua_pcall(L, 1, 0, 0);
    if (ret != 0) {
        lua_pop(L, 1);
    }

    assert(top == lua_gettop(L));
}

static int Wortal_Context_GetID(lua_State* L) {
    int top = lua_gettop(L);

    const char* data = Wortal_context_getID();
    if (data) {
        lua_pushstring(L, data);
    }
    else {
        lua_pushnil(L);
    }

    assert(top + 1 == lua_gettop(L));
    return 1;
}

static int Wortal_Context_ChooseAsync(lua_State* L) {
    int top = lua_gettop(L);

    const char* payload = luaL_checkstring(L, 1);
    luaL_checklistener(L, 2, onContextChooseListener);
    luaL_checklistener(L, 3, onErrorListener);
    Wortal_context_chooseAsync(payload, (OnContextCallback)Wortal_Context_OnContextChoose, (OnErrorCallback)Wortal_OnError);

	assert(top == lua_gettop(L));
	return 0;
}

static int Wortal_Context_ShareAsync(lua_State* L) {
    int top = lua_gettop(L);

    const char* payload = luaL_checkstring(L, 1);
    luaL_checklistener(L, 2, onContextShareListener);
    luaL_checklistener(L, 3, onErrorListener);
    Wortal_context_shareAsync(payload, (OnContextShareCallback)Wortal_Context_OnContextShare, (OnErrorCallback)Wortal_OnError);

	assert(top == lua_gettop(L));
	return 0;
}

static int Wortal_Context_UpdateAsync(lua_State* L) {
    int top = lua_gettop(L);

    const char* payload = luaL_checkstring(L, 1);
    luaL_checklistener(L, 2, onContextUpdateListener);
    luaL_checklistener(L, 3, onErrorListener);
    Wortal_context_updateAsync(payload, (OnContextCallback)Wortal_Context_OnContextUpdate, (OnErrorCallback)Wortal_OnError);

	assert(top == lua_gettop(L));
	return 0;
}

static int Wortal_Context_SwitchAsync(lua_State* L) {
    int top = lua_gettop(L);

    const char* contextId = luaL_checkstring(L, 1);
    luaL_checklistener(L, 2, onContextSwitchListener);
    luaL_checklistener(L, 3, onErrorListener);
    Wortal_context_switchAsync(contextId, (OnContextCallback)Wortal_Context_OnContextSwitch, (OnErrorCallback)Wortal_OnError);

	assert(top == lua_gettop(L));
	return 0;
}

static int Wortal_Context_CreateAsync(lua_State* L) {
    int top = lua_gettop(L);

    const char* playerId = luaL_checkstring(L, 1);
    luaL_checklistener(L, 2, onContextCreateListener);
    luaL_checklistener(L, 3, onErrorListener);
    Wortal_context_createAsync(playerId, (OnContextCallback)Wortal_Context_OnContextCreate, (OnErrorCallback)Wortal_OnError);

	assert(top == lua_gettop(L));
	return 0;
}

// Functions exposed to Lua
static const luaL_reg Module_methods[] = {
    // Ads API
    {"ads_show_interstitial", Wortal_Ads_ShowInterstitial},
    {"ads_show_rewarded", Wortal_Ads_ShowRewarded},

    // Analytics API
    {"analytics_log_level_start", Wortal_Analytics_LogLevelStart},
    {"analytics_log_level_end", Wortal_Analytics_LogLevelEnd},
    {"analytics_log_level_up", Wortal_Analytics_LogLevelUp},
    {"analytics_log_score", Wortal_Analytics_LogScore},
    {"analytics_log_tutorial_start", Wortal_Analytics_LogTutorialStart},
    {"analytics_log_tutorial_end", Wortal_Analytics_LogTutorialEnd},
    {"analytics_log_game_choice", Wortal_Analytics_LogGameChoice},

    // Context API
    {"context_get_id", Wortal_Context_GetID},
    {"context_choose", Wortal_Context_ChooseAsync},
    {"context_share", Wortal_Context_ShareAsync},
    {"context_update", Wortal_Context_UpdateAsync},
    {"context_switch", Wortal_Context_SwitchAsync},
    {"context_create", Wortal_Context_CreateAsync},

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

dmExtension::Result InitializeWortalSdk(dmExtension::Params *params) {
    return dmExtension::RESULT_OK;
}

dmExtension::Result FinalizeWortalSdk(dmExtension::Params *params) {
    return dmExtension::RESULT_OK;
}

#endif

DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, 0, 0, InitializeWortalSdk, 0, 0, FinalizeWortalSdk)
