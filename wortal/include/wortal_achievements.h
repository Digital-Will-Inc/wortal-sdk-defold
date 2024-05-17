#pragma once

#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_HTML5)

class WortalAchievements {
public:
    typedef void (*OnGetAchievementsCallback)(const char* achievements, const char* error);
    typedef void (*OnUnlockAchievementCallback)(const int unlockResult, const char* error);

    static int GetAchievementsAsync(lua_State* L);
    static int UnlockAchievementAsync(lua_State* L);

private:
    static void OnGetAchievements(const char* achievements, const char* error);
    static void OnUnlockAchievement(const int unlockResult, const char* error);
};

extern "C" {
    void Wortal_achievements_getAchievementsAsync(const char* achievements, WortalAchievements::OnGetAchievementsCallback callback);
    void Wortal_achievements_unlockAchievementAsync(const char* achievementId, WortalAchievements::OnUnlockAchievementCallback callback);
}

#endif
