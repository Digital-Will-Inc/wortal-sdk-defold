#pragma once

#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_HTML5)

class WortalNotifications {
public:
    typedef void (*OnScheduleCallback)(const char* result, const char* error);
    typedef void (*OnGetHistoryCallback)(const char* notifications, const char* error);
    typedef void (*OnCancelCallback)(const int success, const char* error);
    typedef void (*OnCancelAllCallback)(const int success, const char* error);

    static int ScheduleAsync(lua_State* L);
    static int GetHistoryAsync(lua_State* L);
    static int CancelAsync(lua_State* L);
    static int CancelAllAsync(lua_State* L);

private:
    static void OnSchedule(const char* result, const char* error);
    static void OnGetHistory(const char* notifications, const char* error);
    static void OnCancel(const int success, const char* error);
    static void OnCancelAll(const int success, const char* error);
};

extern "C" {
    void Wortal_notifications_scheduleAsync(const char* payload, WortalNotifications::OnScheduleCallback callback);
    void Wortal_notifications_getHistoryAsync(WortalNotifications::OnGetHistoryCallback callback);
    void Wortal_notifications_cancelAsync(const char* id, WortalNotifications::OnCancelCallback callback);
    void Wortal_notifications_cancelAllAsync(const char* label, WortalNotifications::OnCancelAllCallback callback);
}

#endif
