#pragma once

#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_HTML5)

class Wortal
{
public:
    typedef void (*OnPauseCallback)(const int success);
    typedef void (*OnResumeCallback)(const int success);
    typedef void (*OnHapticFeedbackCallback)(const int success, const char *error);
    typedef void (*OnInitializeCallback)(const int success, const char *error);
    typedef void (*OnStartGameCallback)(const int success, const char *error);

    static int IsInitialized(lua_State *L);
    static int InitializeAsync(lua_State *L);
    static int StartGameAsync(lua_State *L);
    static int SetLoadingProgress(lua_State *L);
    static int SetPauseCallback(lua_State *L);
    static int SetResumeCallback(lua_State *L);
    static int PerformHapticFeedback(lua_State *L);
    static int GetSupportedAPIs(lua_State *L);

private:
    static void OnInitialize(const int success, const char *error);
    static void OnStartGame(const int success, const char *error);
    static void OnPause(const int success);
    static void OnResume(const int success);
    static void OnHapticFeedback(const int success, const char *error);
};

extern "C"
{
    int Wortal_isInitialized();
    void Wortal_initializeAsync(Wortal::OnInitializeCallback callback);
    void Wortal_startGameAsync(Wortal::OnStartGameCallback callback);
    void Wortal_setLoadingProgress(const int progress);
    void Wortal_onPause(Wortal::OnPauseCallback callback);
    void Wortal_onResume(Wortal::OnResumeCallback callback);
    void Wortal_performHapticFeedback(Wortal::OnHapticFeedbackCallback callback);
    char *Wortal_getSupportedAPIs();
}

#endif
