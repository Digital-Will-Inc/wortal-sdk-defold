#pragma once

#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_HTML5)

class WortalSession
{
public:
    typedef void (*OnGetEntryPointCallback)(const char *data, const char *error);
    typedef void (*OnOrientationChangeCallback)(const char *orientation);
    typedef void (*OnSwitchGameCallback)(const int success, const char *error);
    typedef void (*OnAudioStatusChangeCallback)(const bool *isAudioEnabled);

    static int GetEntryPointData(lua_State *L);
    static int GameplayStart(lua_State *L);
    static int GameplayStop(lua_State *L);
    static int HappyTime(lua_State *L);
    static int GetLocale(lua_State *L);
    static int GetTrafficSource(lua_State *L);
    static int SetSessionData(lua_State *L);
    static int GetEntryPointAsync(lua_State *L);
    static int GetPlatform(lua_State *L);
    static int GetDevice(lua_State *L);
    static int GetOrientation(lua_State *L);
    static int OnOrientationChange(lua_State *L);
    static int SwitchGameAsync(lua_State *L);
    static int IsAudioEnabled(lua_State *L);

private:
    static void OnGetEntryPoint(const char *entryPoint, const char *error);
    static void OnOrientationChange(const char *orientation);
    static void OnSwitchGame(const int success, const char *error);
    static void OnAudioStatusChange(const bool *isAudioEnabled);
};

extern "C"
{
    char *Wortal_session_getEntryPointData();
    void Wortal_session_gameplayStart();
    void Wortal_session_gameplayStop();
    void Wortal_session_happyTime();
    char *Wortal_session_getLocale();
    char *Wortal_session_getTrafficSource();
    void Wortal_session_setSessionData(const char *data);
    void Wortal_session_getEntryPointAsync(WortalSession::OnGetEntryPointCallback callback);
    char *Wortal_session_getPlatform();
    char *Wortal_session_getDevice();
    char *Wortal_session_getOrientation();
    void Wortal_session_onOrientationChange(WortalSession::OnOrientationChangeCallback callback);
    void Wortal_session_switchGameAsync(const char *gameID, WortalSession::OnSwitchGameCallback callback);
    int Wortal_session_isAudioEnabled();
    void Wortal_session_onAudioStatusChange(WortalSession::OnAudioStatusChangeCallback callback);
}

#endif
