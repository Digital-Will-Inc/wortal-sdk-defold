#include "wortal_session.h"
#include "luautils.h"

#if defined(DM_PLATFORM_HTML5)

lua_Listener onSessionGetEntryPointListener;
lua_Listener onOrientationChangeListener;
lua_Listener onSwitchGameListener;

void WortalSession::OnGetEntryPoint(const char* entryPoint, const char* error) {
    lua_State* L = onSessionGetEntryPointListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onSessionGetEntryPointListener);
    if (entryPoint) {
        lua_pushstring(L, entryPoint);
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

void WortalSession::OnOrientationChange(const char* orientation) {
    lua_State* L = onOrientationChangeListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onOrientationChangeListener);
    if (orientation) {
        lua_pushstring(L, orientation);
    }
    else {
        lua_pushnil(L);
    }

    int ret = lua_pcall(L, 2, 0, 0);
    if (ret != 0) {
        lua_pop(L, 1);
    }

    assert(top == lua_gettop(L));
}

void WortalSession::OnSwitchGame(const int success, const char* error) {
    lua_State* L = onSwitchGameListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onSwitchGameListener);
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

int WortalSession::GetEntryPointData(lua_State* L) {
    int top = lua_gettop(L);

    const char* data = Wortal_session_getEntryPointData();
    if (data) {
        lua_pushstring(L, data);
    }
    else {
        lua_pushnil(L);
    }

    assert(top + 1 == lua_gettop(L));
    return 1;
}

int WortalSession::GetLocale(lua_State* L) {
    int top = lua_gettop(L);

    const char* data = Wortal_session_getLocale();
    if (data) {
        lua_pushstring(L, data);
    }
    else {
        lua_pushnil(L);
    }

    assert(top + 1 == lua_gettop(L));
    return 1;
}

int WortalSession::GetTrafficSource(lua_State* L) {
    int top = lua_gettop(L);

    const char* data = Wortal_session_getTrafficSource();
    if (data) {
        lua_pushstring(L, data);
    }
    else {
        lua_pushnil(L);
    }

    assert(top + 1 == lua_gettop(L));
    return 1;
}

int WortalSession::SetSessionData(lua_State* L) {
    int top = lua_gettop(L);

    const char* data = luaL_checkstring(L, 1);
    Wortal_session_setSessionData(data);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalSession::GetEntryPointAsync(lua_State* L) {
    int top = lua_gettop(L);

    luaL_checklistener(L, 1, onSessionGetEntryPointListener);
    Wortal_session_getEntryPointAsync(WortalSession::OnGetEntryPoint);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalSession::GetPlatform(lua_State* L) {
    int top = lua_gettop(L);

    const char* data = Wortal_session_getPlatform();
    if (data) {
        lua_pushstring(L, data);
    }
    else {
        lua_pushnil(L);
    }

    assert(top + 1 == lua_gettop(L));
    return 1;
}

int WortalSession::GetDevice(lua_State* L) {
    int top = lua_gettop(L);

    const char* data = Wortal_session_getDevice();
    if (data) {
        lua_pushstring(L, data);
    }
    else {
        lua_pushnil(L);
    }

    assert(top + 1 == lua_gettop(L));
    return 1;
}

int WortalSession::GetOrientation(lua_State* L) {
    int top = lua_gettop(L);

    const char* data = Wortal_session_getOrientation();
    if (data) {
        lua_pushstring(L, data);
    }
    else {
        lua_pushnil(L);
    }

    assert(top + 1 == lua_gettop(L));
    return 1;
}

int WortalSession::OnOrientationChange(lua_State* L) {
    int top = lua_gettop(L);

    luaL_checklistener(L, 1, onOrientationChangeListener);
    Wortal_session_onOrientationChange(WortalSession::OnOrientationChange);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalSession::SwitchGameAsync(lua_State* L) {
    int top = lua_gettop(L);

    const char* gameID = luaL_checkstring(L, 1);
    luaL_checklistener(L, 2, onSwitchGameListener);
    Wortal_session_switchGameAsync(gameID, WortalSession::OnSwitchGame);

    assert(top == lua_gettop(L));
    return 0;
}

#endif
