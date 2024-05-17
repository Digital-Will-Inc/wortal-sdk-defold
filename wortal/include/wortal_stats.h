#pragma once

#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_HTML5)

class WortalStats {
public:
    typedef void (*OnGetStatsCallback)(const char* stats, const char* error);
    typedef void (*OnPostStatsCallback)(const int success, const char* error);

    static int GetStatsAsync(lua_State* L);
    static int PostStatsAsync(lua_State* L);

private:
    static void OnGetStats(const char* stats, const char* error);
    static void OnPostStats(const int success, const char* error);
};

extern "C" {
    void Wortal_stats_getStatsAsync(const char* level, const char* payload, WortalStats::OnGetStatsCallback callback);
    void Wortal_stats_postStatsAsync(const char* level, const int value, const char* payload, WortalStats::OnPostStatsCallback callback);
}

#endif
