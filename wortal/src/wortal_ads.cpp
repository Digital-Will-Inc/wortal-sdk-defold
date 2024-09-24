#include "wortal_ads.h"
#include "luautils.h"

#if defined(DM_PLATFORM_HTML5)

lua_Listener onBeforeAdListener;
lua_Listener onAfterAdListener;
lua_Listener onAdDismissedListener;
lua_Listener onAdViewedListener;
lua_Listener onNoFillListener;

void WortalAds::OnBeforeAd(const int success)
{
    lua_State *L = onBeforeAdListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onBeforeAdListener);
    lua_pushboolean(L, success);

    int ret = lua_pcall(L, 2, 0, 0);
    if (ret != 0)
    {
        lua_pop(L, 1);
    }

    assert(top == lua_gettop(L));
}

void WortalAds::OnAfterAd(const int success)
{
    lua_State *L = onAfterAdListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onAfterAdListener);
    lua_pushboolean(L, success);

    int ret = lua_pcall(L, 2, 0, 0);
    if (ret != 0)
    {
        lua_pop(L, 1);
    }

    assert(top == lua_gettop(L));
}

void WortalAds::OnAdDismissed(const int success)
{
    lua_State *L = onAdDismissedListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onAdDismissedListener);
    lua_pushboolean(L, success);

    int ret = lua_pcall(L, 2, 0, 0);
    if (ret != 0)
    {
        lua_pop(L, 1);
    }

    assert(top == lua_gettop(L));
}

void WortalAds::OnAdViewed(const int success)
{
    lua_State *L = onAdViewedListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onAdViewedListener);
    lua_pushboolean(L, success);

    int ret = lua_pcall(L, 2, 0, 0);
    if (ret != 0)
    {
        lua_pop(L, 1);
    }

    assert(top == lua_gettop(L));
}

void WortalAds::OnNoFill(const int success)
{
    lua_State *L = onNoFillListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onNoFillListener);
    lua_pushboolean(L, success);

    int ret = lua_pcall(L, 2, 0, 0);
    if (ret != 0)
    {
        lua_pop(L, 1);
    }

    assert(top == lua_gettop(L));
}

int WortalAds::IsAdBlocked(lua_State *L)
{
    int top = lua_gettop(L);

    lua_pushboolean(L, Wortal_ads_isAdBlocked());

    assert(top + 1 == lua_gettop(L));
    return 1;
}

int WortalAds::ShowInterstitial(lua_State *L)
{
    int top = lua_gettop(L);

    const char *type = luaL_checkstring(L, 1);
    const char *description = luaL_checkstring(L, 2);
    luaL_checklistener(L, 3, onBeforeAdListener);
    luaL_checklistener(L, 4, onAfterAdListener);
    luaL_checklistener(L, 5, onNoFillListener);

    Wortal_ads_showInterstitial(type, description, WortalAds::OnBeforeAd, WortalAds::OnAfterAd, WortalAds::OnNoFill);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalAds::ShowRewarded(lua_State *L)
{
    int top = lua_gettop(L);

    const char *description = luaL_checkstring(L, 1);
    luaL_checklistener(L, 2, onBeforeAdListener);
    luaL_checklistener(L, 3, onAfterAdListener);
    luaL_checklistener(L, 4, onAdDismissedListener);
    luaL_checklistener(L, 5, onAdViewedListener);
    luaL_checklistener(L, 6, onNoFillListener);

    Wortal_ads_showRewarded(description, WortalAds::OnBeforeAd, WortalAds::OnAfterAd, WortalAds::OnAdDismissed, WortalAds::OnAdViewed, WortalAds::OnNoFill);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalAds::ShowBanner(lua_State *L)
{
    int top = lua_gettop(L);

    const int shouldShow = luaL_checkinteger(L, 1);
    const char *position = luaL_checkstring(L, 2);

    Wortal_ads_showBanner(shouldShow, position);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalAds::IsEnabled(lua_State *L)
{
    int top = lua_gettop(L);

    lua_pushboolean(L, Wortal_ads_isEnabled());

    assert(top + 1 == lua_gettop(L));
    return 1;
}

#endif
