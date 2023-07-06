#include "wortal_notifications.h"
#include "luautils.h"

#if defined(DM_PLATFORM_HTML5)

lua_Listener onNotificationsScheduleListener;
lua_Listener onNotificationsGetHistoryListener;
lua_Listener onNotificationsCancelListener;
lua_Listener onNotificationsCancelAllListener;

void WortalNotifications::OnSchedule(const char* result, const char* error) {
    lua_State* L = onNotificationsScheduleListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onNotificationsScheduleListener);
    if (result) {
        lua_pushstring(L, result);
    }
    else {
        lua_pushnil(L);
    }
    if (error) {
        lua_pushstring(L, error);
    }
    else {
        lua_pushnil(L);
    }

    int ret = lua_pcall(L, 3, 0, 0);
    if (ret != 0) {
        lua_pop(L, 1);
    }

    assert(top == lua_gettop(L));
}

void WortalNotifications::OnGetHistory(const char* notifications, const char* error) {
    lua_State* L = onNotificationsGetHistoryListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onNotificationsGetHistoryListener);
    if (notifications) {
        lua_pushstring(L, notifications);
    }
    else {
        lua_pushnil(L);
    }
    if (error) {
        lua_pushstring(L, error);
    }
    else {
        lua_pushnil(L);
    }

    int ret = lua_pcall(L, 3, 0, 0);
    if (ret != 0) {
        lua_pop(L, 1);
    }

    assert(top == lua_gettop(L));
}

void WortalNotifications::OnCancel(const int success, const char* error) {
    lua_State* L = onNotificationsCancelListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onNotificationsCancelListener);
    lua_pushboolean(L, success);
    if (error) {
        lua_pushstring(L, error);
    }
    else {
        lua_pushnil(L);
    }

    int ret = lua_pcall(L, 3, 0, 0);
    if (ret != 0) {
        lua_pop(L, 1);
    }

    assert(top == lua_gettop(L));
}

void WortalNotifications::OnCancelAll(const int success, const char* error) {
    lua_State* L = onNotificationsCancelAllListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onNotificationsCancelAllListener);
    lua_pushboolean(L, success);
    if (error) {
        lua_pushstring(L, error);
    }
    else {
        lua_pushnil(L);
    }

    int ret = lua_pcall(L, 3, 0, 0);
    if (ret != 0) {
        lua_pop(L, 1);
    }

    assert(top == lua_gettop(L));
}

int WortalNotifications::ScheduleAsync(lua_State* L) {
    int top = lua_gettop(L);

    const char* payload = luaL_checkstring(L, 1);
    luaL_checklistener(L, 2, onNotificationsScheduleListener);
    Wortal_notifications_scheduleAsync(payload, WortalNotifications::OnSchedule);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalNotifications::GetHistoryAsync(lua_State* L) {
    int top = lua_gettop(L);

    luaL_checklistener(L, 1, onNotificationsGetHistoryListener);
    Wortal_notifications_getHistoryAsync(WortalNotifications::OnGetHistory);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalNotifications::CancelAsync(lua_State* L) {
    int top = lua_gettop(L);

    const char* id = luaL_checkstring(L, 1);
    luaL_checklistener(L, 2, onNotificationsCancelListener);
    Wortal_notifications_cancelAsync(id, WortalNotifications::OnCancel);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalNotifications::CancelAllAsync(lua_State* L) {
    int top = lua_gettop(L);

    const char* label = luaL_checkstring(L, 1);
    luaL_checklistener(L, 2, onNotificationsCancelAllListener);
    Wortal_notifications_cancelAllAsync(label, WortalNotifications::OnCancelAll);

    assert(top == lua_gettop(L));
    return 0;
}

#endif
