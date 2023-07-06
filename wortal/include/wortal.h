#pragma once

#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_HTML5)

class Wortal {
public:
    typedef void (*OnPauseCallback)(const int success);
    typedef void (*OnHapticFeedbackCallback)(const int success, const char* error);

    static int SetPauseCallback(lua_State* L);
    static int PerformHapticFeedback(lua_State* L);
    static int GetSupportedAPIs(lua_State* L);

private:
    static void OnPause(const int success);
    static void OnHapticFeedback(const int success, const char* error);
};

extern "C" {
    void Wortal_onPause(Wortal::OnPauseCallback callback);
    void Wortal_performHapticFeedback(Wortal::OnHapticFeedbackCallback callback);
    char* Wortal_getSupportedAPIs();
}

#endif
