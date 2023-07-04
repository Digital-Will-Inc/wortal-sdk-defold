#pragma once

#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_HTML5)

class Wortal {
public:
    typedef void (*OnPauseCallback)(const int success);

    static int SetPauseCallback(lua_State* L);

private:
    static void OnPause(const int success);
};

extern "C" {
    void Wortal_onPause(Wortal::OnPauseCallback callback);
}

#endif
