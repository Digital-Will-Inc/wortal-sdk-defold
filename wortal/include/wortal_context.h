#pragma once

#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_HTML5)

class WortalContext {
public:
    typedef void (*OnContextCallback)(const int success, const char* error);
    typedef void (*OnContextGetPlayersCallback)(const char* players, const char* error);
    typedef void (*OnContextShareCallback)(const int shareResult, const char* error);

    static int GetID(lua_State* L);
    static int GetType(lua_State* L);
    static int GetPlayersAsync(lua_State* L);
    static int ChooseAsync(lua_State* L);
    static int InviteAsync(lua_State* L);
    static int ShareAsync(lua_State* L);
    static int ShareLinkAsync(lua_State* L);
    static int UpdateAsync(lua_State* L);
    static int SwitchAsync(lua_State* L);
    static int CreateAsync(lua_State* L);
    static int IsSizeBetween(lua_State* L);

private:
    static void OnGetPlayers(const char* players, const char* error);
    static void OnContextChoose(const int success, const char* error);
    static void OnContextInvite(const int success, const char* error);
    static void OnContextShare(const int shareResult, const char* error);
    static void OnContextShareLink(const int success, const char* error);
    static void OnContextUpdate(const int success, const char* error);
    static void OnContextSwitch(const int success, const char* error);
    static void OnContextCreate(const int success, const char* error);
};

extern "C" {
    char* Wortal_context_getID();
    char* Wortal_context_getType();
    void Wortal_context_getPlayersAsync(WortalContext::OnContextGetPlayersCallback callback);
    void Wortal_context_chooseAsync(const char* payload, WortalContext::OnContextCallback callback);
    void Wortal_context_inviteAsync(const char* payload, WortalContext::OnContextCallback callback);
    void Wortal_context_shareAsync(const char* payload, WortalContext::OnContextShareCallback callback);
    void Wortal_context_shareLinkAsync(const char* payload, WortalContext::OnContextCallback callback);
    void Wortal_context_updateAsync(const char* payload, WortalContext::OnContextCallback callback);
    void Wortal_context_switchAsync(const char* contextId, WortalContext::OnContextCallback callback);
    void Wortal_context_createAsync(const char* playerId, WortalContext::OnContextCallback callback);
    char* Wortal_context_isSizeBetween(const int min, const int max);
}

#endif
