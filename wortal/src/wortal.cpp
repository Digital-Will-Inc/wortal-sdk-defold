#include "wortal.h"
#include "luautils.h"
#include <dmsdk/sdk.h>

#define EXTENSION_NAME Wortal
#define LIB_NAME "Wortal"
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

static void Wortal_Ads_OnBeforeAd(const int success) {
    lua_State* L = onBeforeAdListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onBeforeAdListener);
    lua_pushboolean(L, success);

    int ret = lua_pcall(L, 2, 0, 0);
    if (ret != 0) {
        lua_pop(L, 1);
    }

    assert(top == lua_gettop(L));
}

static void Wortal_Ads_OnAfterAd(const int success) {
    lua_State* L = onAfterAdListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onAfterAdListener);
    lua_pushboolean(L, success);

    int ret = lua_pcall(L, 2, 0, 0);
    if (ret != 0) {
        lua_pop(L, 1);
    }

    assert(top == lua_gettop(L));
}

static void Wortal_Ads_OnAdDismissed(const int success) {
    lua_State* L = onAdDismissedListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onAdDismissedListener);
    lua_pushboolean(L, success);

    int ret = lua_pcall(L, 2, 0, 0);
    if (ret != 0) {
        lua_pop(L, 1);
    }

    assert(top == lua_gettop(L));
}

static void Wortal_Ads_OnAdViewed(const int success) {
    lua_State* L = onAdViewedListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onAdViewedListener);
    lua_pushboolean(L, success);

    int ret = lua_pcall(L, 2, 0, 0);
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

static void Wortal_Context_OnContextChoose(const int success, const char* error) {
    lua_State* L = onContextChooseListener.m_L;
	int top = lua_gettop(L);

    lua_pushlistener(L, onContextChooseListener);
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

static void Wortal_Context_OnContextShare(const int shareResult, const char* error) {
    lua_State* L = onContextShareListener.m_L;
	int top = lua_gettop(L);

    lua_pushlistener(L, onContextShareListener);
    lua_pushnumber(L, shareResult);
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

static void Wortal_Context_OnContextUpdate(const int success, const char* error) {
    lua_State* L = onContextUpdateListener.m_L;
	int top = lua_gettop(L);

    lua_pushlistener(L, onContextUpdateListener);
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

static void Wortal_Context_OnContextSwitch(const int success, const char* error) {
    lua_State* L = onContextSwitchListener.m_L;
	int top = lua_gettop(L);

    lua_pushlistener(L, onContextSwitchListener);
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

static void Wortal_Context_OnContextCreate(const int success, const char* error) {
    lua_State* L = onContextCreateListener.m_L;
	int top = lua_gettop(L);

    lua_pushlistener(L, onContextCreateListener);
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
    Wortal_context_chooseAsync(payload, (OnContextCallback)Wortal_Context_OnContextChoose);

	assert(top == lua_gettop(L));
	return 0;
}

static int Wortal_Context_ShareAsync(lua_State* L) {
    int top = lua_gettop(L);

    const char* payload = luaL_checkstring(L, 1);
    luaL_checklistener(L, 2, onContextShareListener);
    Wortal_context_shareAsync(payload, (OnContextShareCallback)Wortal_Context_OnContextShare);

	assert(top == lua_gettop(L));
	return 0;
}

static int Wortal_Context_UpdateAsync(lua_State* L) {
    int top = lua_gettop(L);

    const char* payload = luaL_checkstring(L, 1);
    luaL_checklistener(L, 2, onContextUpdateListener);
    Wortal_context_updateAsync(payload, (OnContextCallback)Wortal_Context_OnContextUpdate);

	assert(top == lua_gettop(L));
	return 0;
}

static int Wortal_Context_SwitchAsync(lua_State* L) {
    int top = lua_gettop(L);

    const char* contextId = luaL_checkstring(L, 1);
    luaL_checklistener(L, 2, onContextSwitchListener);
    Wortal_context_switchAsync(contextId, (OnContextCallback)Wortal_Context_OnContextSwitch);

	assert(top == lua_gettop(L));
	return 0;
}

static int Wortal_Context_CreateAsync(lua_State* L) {
    int top = lua_gettop(L);

    const char* playerId = luaL_checkstring(L, 1);
    luaL_checklistener(L, 2, onContextCreateListener);
    Wortal_context_createAsync(playerId, (OnContextCallback)Wortal_Context_OnContextCreate);

	assert(top == lua_gettop(L));
	return 0;
}

//////////////////////////////////////////////////////////////////////
// In-App Purchasing API
//////////////////////////////////////////////////////////////////////

lua_Listener onIAPGetCatalogListener;
lua_Listener onIAPGetPurchasesListener;
lua_Listener onIAPMakePurchaseListener;
lua_Listener onIAPConsumePurchaseListener;

static void Wortal_IAP_OnGetCatalog(const char* catalog, const char* error) {
    lua_State* L = onIAPGetCatalogListener.m_L;
	int top = lua_gettop(L);

    lua_pushlistener(L, onIAPGetCatalogListener);
    if (catalog) {
        lua_pushstring(L, catalog);
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

static void Wortal_IAP_OnGetPurchases(const char* purchases, const char* error) {
    lua_State* L = onIAPGetPurchasesListener.m_L;
	int top = lua_gettop(L);

    lua_pushlistener(L, onIAPGetPurchasesListener);
    if (purchases) {
        lua_pushstring(L, purchases);
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

static void Wortal_IAP_OnMakePurchase(const char* purchase, const char* error) {
    lua_State* L = onIAPMakePurchaseListener.m_L;
	int top = lua_gettop(L);

    lua_pushlistener(L, onIAPMakePurchaseListener);
    if (purchase) {
        lua_pushstring(L, purchase);
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

static void Wortal_IAP_OnConsumePurchase(const int success, const char* error) {
    lua_State* L = onIAPConsumePurchaseListener.m_L;
	int top = lua_gettop(L);

    lua_pushlistener(L, onIAPConsumePurchaseListener);
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

static int Wortal_IAP_IsEnabled(lua_State* L) {
    int top = lua_gettop(L);

    int enabled = Wortal_iap_isEnabled();
    lua_pushboolean(L, enabled);

    assert(top + 1 == lua_gettop(L));
    return 1;
}

static int Wortal_IAP_GetCatalogAsync(lua_State* L) {
    int top = lua_gettop(L);

    luaL_checklistener(L, 1, onIAPGetCatalogListener);
    Wortal_iap_getCatalogAsync((OnGetCatalogCallback)Wortal_IAP_OnGetCatalog);

    assert(top == lua_gettop(L));
	return 0;
}

static int Wortal_IAP_GetPurchasesAsync(lua_State* L) {
    int top = lua_gettop(L);

    luaL_checklistener(L, 1, onIAPGetPurchasesListener);
    Wortal_iap_getPurchasesAsync((OnGetPurchasesCallback)Wortal_IAP_OnGetPurchases);

	assert(top == lua_gettop(L));
	return 0;
}

static int Wortal_IAP_MakePurchaseAsync(lua_State* L) {
    int top = lua_gettop(L);

    const char* purchaseConfig = luaL_checkstring(L, 1);
    luaL_checklistener(L, 2, onIAPMakePurchaseListener);
    Wortal_iap_makePurchaseAsync(purchaseConfig, (OnMakePurchaseCallback)Wortal_IAP_OnMakePurchase);

    assert(top == lua_gettop(L));
	return 0;
}

static int Wortal_IAP_ConsumePurchaseAsync(lua_State* L) {
    int top = lua_gettop(L);

    const char* token = luaL_checkstring(L, 1);
    luaL_checklistener(L, 2, onIAPConsumePurchaseListener);
    Wortal_iap_consumePurchaseAsync(token, (OnConsumePurchaseCallback)Wortal_IAP_OnConsumePurchase);

    assert(top == lua_gettop(L));
	return 0;
}

//////////////////////////////////////////////////////////////////////
// Leaderbord API
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Player API
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Session API
//////////////////////////////////////////////////////////////////////

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

    // In-App Purchasing API
    {"iap_is_enabled", Wortal_IAP_IsEnabled},
    {"iap_get_catalog", Wortal_IAP_GetCatalogAsync},
    {"iap_get_purchases", Wortal_IAP_GetPurchasesAsync},
    {"iap_make_purchase", Wortal_IAP_MakePurchaseAsync},
    {"iap_consume_purchase", Wortal_IAP_ConsumePurchaseAsync},

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
