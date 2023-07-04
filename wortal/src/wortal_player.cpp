#include "wortal_player.h"
#include "luautils.h"

#if defined(DM_PLATFORM_HTML5)

lua_Listener onPlayerGetDataListener;
lua_Listener onPlayerSetDataListener;
lua_Listener onPlayerFlushDataListener;
lua_Listener onPlayerGetConnectedPlayersListener;
lua_Listener onPlayerGetSignedInfoListener;
lua_Listener onPlayerGetASIDListener;
lua_Listener onPlayerGetSignedASIDListener;
lua_Listener onPlayerCanSubscribeBotListener;
lua_Listener onPlayerSubscribeBotListener;

void WortalPlayer::OnGetData(const char* data, const char* error) {
    lua_State* L = onPlayerGetDataListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onPlayerGetDataListener);
    if (data) {
        lua_pushstring(L, data);
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

void WortalPlayer::OnSetData(const int success, const char* error) {
    lua_State* L = onPlayerSetDataListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onPlayerSetDataListener);
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

void WortalPlayer::OnFlushData(const int success, const char* error) {
    lua_State* L = onPlayerFlushDataListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onPlayerFlushDataListener);
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

void WortalPlayer::OnGetConnectedPlayers(const char* players, const char* error) {
    lua_State* L = onPlayerGetConnectedPlayersListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onPlayerGetConnectedPlayersListener);
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

void WortalPlayer::OnGetSignedPlayerInfo(const char* info, const char* error) {
    lua_State* L = onPlayerGetSignedInfoListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onPlayerGetSignedInfoListener);
    if (info) {
        lua_pushstring(L, info);
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

void WortalPlayer::OnGetASID(const char* asid, const char* error) {
    lua_State* L = onPlayerGetASIDListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onPlayerGetASIDListener);
    if (asid) {
        lua_pushstring(L, asid);
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

void WortalPlayer::OnGetSignedASID(const char* asid, const char* error) {
    lua_State* L = onPlayerGetSignedASIDListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onPlayerGetSignedASIDListener);
    if (asid) {
        lua_pushstring(L, asid);
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

void WortalPlayer::OnCanSubscribeBot(const int canSubscribe, const char* error) {
    lua_State* L = onPlayerCanSubscribeBotListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onPlayerCanSubscribeBotListener);
    lua_pushboolean(L, canSubscribe);
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

void WortalPlayer::OnSubscribeBot(const int success, const char* error) {
    lua_State* L = onPlayerSubscribeBotListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onPlayerSubscribeBotListener);
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

int WortalPlayer::GetID(lua_State* L) {
    int top = lua_gettop(L);

    const char* data = Wortal_player_getID();
    if (data) {
        lua_pushstring(L, data);
    }
    else {
        lua_pushnil(L);
    }

    assert(top + 1 == lua_gettop(L));
    return 1;
}

int WortalPlayer::GetName(lua_State* L) {
    int top = lua_gettop(L);

    const char* data = Wortal_player_getName();
    if (data) {
        lua_pushstring(L, data);
    }
    else {
        lua_pushnil(L);
    }

    assert(top + 1 == lua_gettop(L));
    return 1;
}

int WortalPlayer::GetPhoto(lua_State* L) {
    int top = lua_gettop(L);

    const char* data = Wortal_player_getPhoto();
    if (data) {
        lua_pushstring(L, data);
    }
    else {
        lua_pushnil(L);
    }

    assert(top + 1 == lua_gettop(L));
    return 1;
}

int WortalPlayer::IsFirstPlay(lua_State* L) {
    int top = lua_gettop(L);

    int data = Wortal_player_isFirstPlay();
    lua_pushboolean(L, data);

    assert(top + 1 == lua_gettop(L));
    return 1;
}

int WortalPlayer::GetDataAsync(lua_State* L) {
    int top = lua_gettop(L);

    const char* keys = luaL_checkstring(L, 1);
    luaL_checklistener(L, 2, onPlayerGetDataListener);
    Wortal_player_getDataAsync(keys, WortalPlayer::OnGetData);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalPlayer::SetDataAsync(lua_State* L) {
    int top = lua_gettop(L);

    const char* data = luaL_checkstring(L, 1);
    luaL_checklistener(L, 2, onPlayerSetDataListener);
    Wortal_player_setDataAsync(data, WortalPlayer::OnSetData);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalPlayer::FlushDataAsync(lua_State* L) {
    int top = lua_gettop(L);

    luaL_checklistener(L, 1, onPlayerFlushDataListener);
    Wortal_player_flushDataAsync(WortalPlayer::OnFlushData);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalPlayer::GetConnectedPlayersAsync(lua_State* L) {
    int top = lua_gettop(L);

    if (lua_isstring(L, 1)) {
        const char* payload = luaL_checkstring(L, 1);
        luaL_checklistener(L, 2, onPlayerGetConnectedPlayersListener);
        Wortal_player_getConnectedPlayersAsync(payload, WortalPlayer::OnGetConnectedPlayers);
    }
    else {
        const char* payload = "";
        luaL_checklistener(L, 1, onPlayerGetConnectedPlayersListener);
        Wortal_player_getConnectedPlayersAsync(payload, WortalPlayer::OnGetConnectedPlayers);
    }

    assert(top == lua_gettop(L));
    return 0;
}

int WortalPlayer::GetSignedPlayerInfoAsync(lua_State* L) {
    int top = lua_gettop(L);

    luaL_checklistener(L, 1, onPlayerGetSignedInfoListener);
    Wortal_player_getSignedPlayerInfoAsync(WortalPlayer::OnGetSignedPlayerInfo);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalPlayer::GetASIDAsync(lua_State* L) {
    int top = lua_gettop(L);

    luaL_checklistener(L, 1, onPlayerGetASIDListener);
    Wortal_player_getASIDAsync(WortalPlayer::OnGetASID);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalPlayer::GetSignedASIDAsync(lua_State* L) {
    int top = lua_gettop(L);

    luaL_checklistener(L, 1, onPlayerGetSignedASIDListener);
    Wortal_player_getSignedASIDAsync(WortalPlayer::OnGetSignedASID);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalPlayer::CanSubscribeBotAsync(lua_State* L) {
    int top = lua_gettop(L);

    luaL_checklistener(L, 1, onPlayerCanSubscribeBotListener);
    Wortal_player_canSubscribeBotAsync(WortalPlayer::OnCanSubscribeBot);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalPlayer::SubscribeBotAsync(lua_State* L) {
    int top = lua_gettop(L);

    luaL_checklistener(L, 1, onPlayerSubscribeBotListener);
    Wortal_player_subscribeBotAsync(WortalPlayer::OnSubscribeBot);

    assert(top == lua_gettop(L));
    return 0;
}

#endif
