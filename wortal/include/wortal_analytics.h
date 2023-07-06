#pragma once

#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_HTML5)

class WortalAnalytics {
public:
    static int LogLevelStart(lua_State* L);
    static int LogLevelEnd(lua_State* L);
    static int LogLevelUp(lua_State* L);
    static int LogScore(lua_State* L);
    static int LogTutorialStart(lua_State* L);
    static int LogTutorialEnd(lua_State* L);
    static int LogGameChoice(lua_State* L);
    static int LogSocialInvite(lua_State* L);
    static int LogSocialShare(lua_State* L);
    static int LogPurchase(lua_State* L);
    static int LogPurchaseSubscription(lua_State* L);
};

extern "C" {
    void Wortal_analytics_logLevelStart(const char* level);
    void Wortal_analytics_logLevelEnd(const char* level, const char* score, const int wasCompleted);
    void Wortal_analytics_logLevelUp(const char* level);
    void Wortal_analytics_logScore(const char* score);
    void Wortal_analytics_logTutorialStart(const char* tutorial);
    void Wortal_analytics_logTutorialEnd(const char* tutorial, const int wasCompleted);
    void Wortal_analytics_logGameChoice(const char* decision, const char* choice);
    void Wortal_analytics_logSocialInvite(const char* placement);
    void Wortal_analytics_logSocialShare(const char* placement);
    void Wortal_analytics_logPurchase(const char* productID, const char* details);
    void Wortal_analytics_logPurchaseSubscription(const char* productID, const char* details);
}

#endif
