#define EXTENSION_NAME wortalsdk
#define LIB_NAME "WortalSdk"
#define MODULE_NAME "wortal_sdk"

#include <dmsdk/sdk.h>

#define VERSION "1.0.0"

#if defined(DM_PLATFORM_HTML5)

typedef void (*BeforeAdCallback)();
typedef void (*AfterAdCallback)();
typedef void (*AdDismissedCallback)();
typedef void (*AdViewedCallback)();

extern "C" {
    void js_showInterstitial(const char* type, const char* description, BeforeAdCallback beforeAdCallback,
    AfterAdCallback afterAdCallback);

    void js_showRewarded(const char* description, BeforeAdCallback beforeAdCallback,
    AfterAdCallback afterAdCallback, AdDismissedCallback adDismissedCallback, AdViewedCallback adViewedCallback);

    void js_logLevelStart(const char* level);
    void js_logLevelEnd(const char* level, const char* score);
    void js_logLevelUp(const char* level);
    void js_logScore(const char* score);
    void js_logGameChoice(const char* decision, const char* choice);
}

static dmScript::LuaCallbackInfo* beforeAdCallback = 0x0;
static dmScript::LuaCallbackInfo* afterAdCallback = 0x0;
static dmScript::LuaCallbackInfo* adDismissedCallback = 0x0;
static dmScript::LuaCallbackInfo* adViewedCallback = 0x0;

static void WortalSdk_BeforeAdCallback()
{
    if (!dmScript::IsCallbackValid(beforeAdCallback))
    {
        dmLogError("[Wortal] BeforeAd callback is invalid. Pass a function to trigger on callback.");
        return;
    }

    lua_State* L = dmScript::GetCallbackLuaContext(beforeAdCallback);
    DM_LUA_STACK_CHECK(L, 0);

    if (!dmScript::SetupCallback(beforeAdCallback))
    {
        dmLogError("[Wortal] SetupCallback failed for beforeAdCallback.");
        return;
    }

    int ret = dmScript::PCall(L, 1, 0);
    (void)ret;

    dmScript::TeardownCallback(beforeAdCallback);
    if (beforeAdCallback != 0x0)
    {
        dmScript::DestroyCallback(beforeAdCallback);
        beforeAdCallback = 0x0;
    }
}

static void WortalSdk_AfterAdCallback()
{
    if (!dmScript::IsCallbackValid(afterAdCallback))
    {
        dmLogError("[Wortal] AfterAd callback is invalid. Pass a function to trigger on callback.");
        return;
    }

    lua_State* L = dmScript::GetCallbackLuaContext(afterAdCallback);
    DM_LUA_STACK_CHECK(L, 0);

    if (!dmScript::SetupCallback(afterAdCallback))
    {
        dmLogError("[Wortal] SetupCallback failed for afterAdCallback.");
        return;
    }

    int ret = dmScript::PCall(L, 1, 0);
    (void)ret;

    dmScript::TeardownCallback(afterAdCallback);
    if (afterAdCallback != 0x0)
    {
        dmScript::DestroyCallback(afterAdCallback);
        afterAdCallback = 0x0;
    }
}

static void WortalSdk_AdDismissedCallback()
{
    if (!dmScript::IsCallbackValid(adDismissedCallback))
    {
        dmLogError("[Wortal] AdDismissed callback is invalid. Pass a function to trigger on callback.");
        return;
    }

    lua_State* L = dmScript::GetCallbackLuaContext(adDismissedCallback);
    DM_LUA_STACK_CHECK(L, 0);

    if (!dmScript::SetupCallback(adDismissedCallback))
    {
        dmLogError("[Wortal] SetupCallback failed for adDismissedCallback.");
        return;
    }

    int ret = dmScript::PCall(L, 1, 0);
    (void)ret;

    dmScript::TeardownCallback(adDismissedCallback);
    if (adDismissedCallback != 0x0)
    {
        dmScript::DestroyCallback(adDismissedCallback);
        adDismissedCallback = 0x0;
    }
}

static void WortalSdk_AdViewedCallback()
{
    if (!dmScript::IsCallbackValid(adViewedCallback))
    {
        dmLogError("[Wortal] AdViewed callback is invalid. Pass a function to trigger on callback.");
        return;
    }

    lua_State* L = dmScript::GetCallbackLuaContext(adViewedCallback);
    DM_LUA_STACK_CHECK(L, 0);

    if (!dmScript::SetupCallback(adViewedCallback))
    {
        dmLogError("[Wortal] SetupCallback failed for adViewedCallback.");
        return;
    }

    int ret = dmScript::PCall(L, 1, 0);
    (void)ret;

    dmScript::TeardownCallback(adViewedCallback);
    if (adViewedCallback != 0x0)
    {
        dmScript::DestroyCallback(adViewedCallback);
        adViewedCallback = 0x0;
    }
}

static int WortalSdk_ShowInterstitial(lua_State* L)
{
    const char* type = luaL_checkstring(L, 1);
    const char* description = luaL_checkstring(L, 2);

    int beforeAd = lua_type(L, 3);
    if (beforeAd != LUA_TFUNCTION) {
        luaL_error(L, "[Wortal] BeforeAd callback is invalid. Pass a function to trigger on callback.");
        return 0;
    }

    int afterAd = lua_type(L, 4);
    if (afterAd != LUA_TFUNCTION) {
        luaL_error(L, "[Wortal] AfterAd callback is invalid. Pass a function to trigger on callback.");
        return 0;
    }

    DM_LUA_STACK_CHECK(L, 0);
    beforeAdCallback = dmScript::CreateCallback(L, 3);
    afterAdCallback = dmScript::CreateCallback(L, 4);

    js_showInterstitial(type, description, (BeforeAdCallback)WortalSdk_BeforeAdCallback, (AfterAdCallback)WortalSdk_AfterAdCallback);

    return 0;
}

static int WortalSdk_ShowRewarded(lua_State* L)
{
    const char* description = luaL_checkstring(L, 1);

    int beforeAd = lua_type(L, 2);
    if (beforeAd != LUA_TFUNCTION) {
        luaL_error(L, "[Wortal] BeforeAd callback is invalid. Pass a function to trigger on callback.");
        return 0;
    }

    int afterAd = lua_type(L, 3);
    if (afterAd != LUA_TFUNCTION) {
        luaL_error(L, "[Wortal] AfterAd callback is invalid. Pass a function to trigger on callback.");
        return 0;
    }

    int adDismissed = lua_type(L, 4);
    if (adDismissed != LUA_TFUNCTION) {
        luaL_error(L, "[Wortal] AdDismissed callback is invalid. Pass a function to trigger on callback.");
        return 0;
    }

    int adViewed = lua_type(L, 5);
    if (adViewed != LUA_TFUNCTION) {
        luaL_error(L, "[Wortal] AdViewed callback is invalid. Pass a function to trigger on callback.");
        return 0;
    }

    DM_LUA_STACK_CHECK(L, 0);
    beforeAdCallback = dmScript::CreateCallback(L, 2);
    afterAdCallback = dmScript::CreateCallback(L, 3);
    adDismissedCallback = dmScript::CreateCallback(L, 4);
    adViewedCallback = dmScript::CreateCallback(L, 5);

    js_showRewarded(description, (BeforeAdCallback)WortalSdk_BeforeAdCallback, (AfterAdCallback)WortalSdk_AfterAdCallback,
        (AdDismissedCallback)WortalSdk_AdDismissedCallback, (AdViewedCallback)WortalSdk_AdViewedCallback);

    return 0;
}

static int WortalSdk_LogLevelStart(lua_State* L)
{
    const char* level = luaL_checkstring(L, 1);
    DM_LUA_STACK_CHECK(L, 0);
    js_logLevelStart(level);
    return 0;
}

static int WortalSdk_LogLevelEnd(lua_State* L)
{
    const char* level = luaL_checkstring(L, 1);
    const char* score = luaL_checkstring(L, 2);
    DM_LUA_STACK_CHECK(L, 0);
    js_logLevelEnd(level, score);
    return 0;
}

static int WortalSdk_LogLevelUp(lua_State* L)
{
    const char* level = luaL_checkstring(L, 1);
    DM_LUA_STACK_CHECK(L, 0);
    js_logLevelUp(level);
    return 0;
}

static int WortalSdk_LogScore(lua_State* L)
{
    const char* score = luaL_checkstring(L, 1);
    DM_LUA_STACK_CHECK(L, 0);
    js_logScore(score);
    return 0;
}

static int WortalSdk_LogGameChoice(lua_State* L)
{
    const char* decision = luaL_checkstring(L, 1);
    const char* choice = luaL_checkstring(L, 2);
    DM_LUA_STACK_CHECK(L, 0);
    js_logGameChoice(decision, choice);
    return 0;
}

// Functions exposed to Lua
static const luaL_reg Module_methods[] =
{
    {"show_interstitial", WortalSdk_ShowInterstitial},
    {"show_rewarded", WortalSdk_ShowRewarded},
    {"log_level_start", WortalSdk_LogLevelStart},
    {"log_level_end", WortalSdk_LogLevelEnd},
    {"log_level_up", WortalSdk_LogLevelUp},
    {"log_score", WortalSdk_LogScore},
    {"log_game_choice", WortalSdk_LogGameChoice},
    {0, 0}
};

static void LuaInit(lua_State* L)
{
    int top = lua_gettop(L);

    luaL_register(L, MODULE_NAME, Module_methods);

    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}

dmExtension::Result InitializeWortalSdk(dmExtension::Params* params)
{
    LuaInit(params->m_L);
    return dmExtension::RESULT_OK;
}

dmExtension::Result FinalizeWortalSdk(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

#else // unsupported platforms

dmExtension::Result InitializeWortalSdk(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

dmExtension::Result FinalizeWortalSdk(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

#endif

DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, 0, 0, InitializeWortalSdk, 0, 0, FinalizeWortalSdk)
