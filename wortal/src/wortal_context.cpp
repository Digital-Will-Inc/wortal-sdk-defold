#include "wortal_context.h"
#include "luautils.h"

#if defined(DM_PLATFORM_HTML5)

lua_Listener onContextGetPlayersListener;
lua_Listener onContextChooseListener;
lua_Listener onContextShareListener;
lua_Listener onContextShareLinkListener;
lua_Listener onContextUpdateListener;
lua_Listener onContextSwitchListener;
lua_Listener onContextCreateListener;

void WortalContext::OnGetPlayers(const char* players, const char* error)
{
    lua_State* L = onContextGetPlayersListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onContextGetPlayersListener);
    if (players) {
        lua_pushstring(L, players);
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

void WortalContext::OnContextChoose(const int success, const char* error) {
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

void WortalContext::OnContextShare(const int shareResult, const char* error) {
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

void WortalContext::OnContextShareLink(const int success, const char* error) {
    lua_State* L = onContextShareLinkListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onContextShareLinkListener);
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

void WortalContext::OnContextUpdate(const int success, const char* error) {
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

void WortalContext::OnContextSwitch(const int success, const char* error) {
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

void WortalContext::OnContextCreate(const int success, const char* error) {
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

int WortalContext::GetID(lua_State* L) {
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

int WortalContext::GetType(lua_State* L) {
    int top = lua_gettop(L);

    const char* data = Wortal_context_getType();
    if (data) {
        lua_pushstring(L, data);
    }
    else {
        lua_pushnil(L);
    }

    assert(top + 1 == lua_gettop(L));
    return 1;
}

int WortalContext::GetPlayersAsync(lua_State* L) {
    int top = lua_gettop(L);

    luaL_checklistener(L, 1, onContextGetPlayersListener);
    Wortal_context_getPlayersAsync(WortalContext::OnGetPlayers);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalContext::ChooseAsync(lua_State* L) {
    int top = lua_gettop(L);

    const char* payload = luaL_checkstring(L, 1);
    luaL_checklistener(L, 2, onContextChooseListener);
    Wortal_context_chooseAsync(payload, WortalContext::OnContextChoose);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalContext::ShareAsync(lua_State* L) {
    int top = lua_gettop(L);

    const char* payload = luaL_checkstring(L, 1);
    luaL_checklistener(L, 2, onContextShareListener);
    Wortal_context_shareAsync(payload, WortalContext::OnContextShare);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalContext::ShareLinkAsync(lua_State* L) {
    int top = lua_gettop(L);

    const char* payload = luaL_checkstring(L, 1);
    luaL_checklistener(L, 2, onContextShareLinkListener);
    Wortal_context_shareAsync(payload, WortalContext::OnContextShareLink);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalContext::UpdateAsync(lua_State* L) {
    int top = lua_gettop(L);

    const char* payload = luaL_checkstring(L, 1);
    luaL_checklistener(L, 2, onContextUpdateListener);
    Wortal_context_updateAsync(payload, WortalContext::OnContextUpdate);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalContext::SwitchAsync(lua_State* L) {
    int top = lua_gettop(L);

    const char* contextId = luaL_checkstring(L, 1);
    luaL_checklistener(L, 2, onContextSwitchListener);
    Wortal_context_switchAsync(contextId, WortalContext::OnContextSwitch);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalContext::CreateAsync(lua_State* L) {
    int top = lua_gettop(L);

    const char* playerId = luaL_checkstring(L, 1);
    luaL_checklistener(L, 2, onContextCreateListener);
    Wortal_context_createAsync(playerId, WortalContext::OnContextCreate);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalContext::IsSizeBetween(lua_State* L) {
    int top = lua_gettop(L);

    int min = luaL_checknumber(L, 1);
    int max = luaL_checknumber(L, 2);

    const char* data = Wortal_context_isSizeBetween(min, max);
    if (data) {
        lua_pushstring(L, data);
    }
    else {
        lua_pushnil(L);
    }

    assert(top + 1 == lua_gettop(L));
    return 1;
}

#endif
