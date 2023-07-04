#pragma once

#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_HTML5)

class WortalPlayer {
public:
    typedef void (*OnPlayerGetDataCallback)(const char* data, const char* error);
    typedef void (*OnPlayerSetDataCallback)(const int success, const char* error);
    typedef void (*OnPlayerFlushDataCallback)(const int success, const char* error);
    typedef void (*OnGetConnectedPlayersCallback)(const char* players, const char* error);
    typedef void (*OnGetSignedPlayerInfoCallback)(const char* info, const char* error);
    typedef void (*OnGetASIDCallback)(const char* asid, const char* error);
    typedef void (*OnGetSignedASIDCallback)(const char* signedASID, const char* error);
    typedef void (*OnCanSubscribeBotCallback)(const int canSubscribe, const char* error);
    typedef void (*OnSubscribeBotCallback)(const int success, const char* error);

    static int GetID(lua_State* L);
    static int GetName(lua_State* L);
    static int GetPhoto(lua_State* L);
    static int IsFirstPlay(lua_State* L);
    static int GetDataAsync(lua_State* L);
    static int SetDataAsync(lua_State* L);
    static int FlushDataAsync(lua_State* L);
    static int GetConnectedPlayersAsync(lua_State* L);
    static int GetSignedPlayerInfoAsync(lua_State* L);
    static int GetASIDAsync(lua_State* L);
    static int GetSignedASIDAsync(lua_State* L);
    static int CanSubscribeBotAsync(lua_State* L);
    static int SubscribeBotAsync(lua_State* L);

private:
    static void OnGetData(const char* data, const char* error);
    static void OnSetData(const int success, const char* error);
    static void OnFlushData(const int success, const char* error);
    static void OnGetConnectedPlayers(const char* players, const char* error);
    static void OnGetSignedPlayerInfo(const char* info, const char* error);
    static void OnGetASID(const char* asid, const char* error);
    static void OnGetSignedASID(const char* asid, const char* error);
    static void OnCanSubscribeBot(const int canSubscribe, const char* error);
    static void OnSubscribeBot(const int success, const char* error);
};

extern "C" {
    char* Wortal_player_getID();
    char* Wortal_player_getName();
    char* Wortal_player_getPhoto();
    int Wortal_player_isFirstPlay();
    void Wortal_player_getDataAsync(const char* keys, WortalPlayer::OnPlayerGetDataCallback callback);
    void Wortal_player_setDataAsync(const char* data, WortalPlayer::OnPlayerSetDataCallback callback);
    void Wortal_player_flushDataAsync(WortalPlayer::OnPlayerFlushDataCallback callback);
    void Wortal_player_getConnectedPlayersAsync(const char* payload, WortalPlayer::OnGetConnectedPlayersCallback callback);
    void Wortal_player_getSignedPlayerInfoAsync(WortalPlayer::OnGetSignedPlayerInfoCallback callback);
    void Wortal_player_getASIDAsync(WortalPlayer::OnGetASIDCallback callback);
    void Wortal_player_getSignedASIDAsync(WortalPlayer::OnGetSignedASIDCallback callback);
    void Wortal_player_canSubscribeBotAsync(WortalPlayer::OnCanSubscribeBotCallback callback);
    void Wortal_player_subscribeBotAsync(WortalPlayer::OnSubscribeBotCallback callback);
}

#endif
