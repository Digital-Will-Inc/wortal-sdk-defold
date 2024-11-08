#include "wortal.h"
#include "wortal_achievements.h"
#include "wortal_ads.h"
#include "wortal_analytics.h"
#include "wortal_context.h"
#include "wortal_iap.h"
#include "wortal_leaderboard.h"
#include "wortal_notifications.h"
#include "wortal_player.h"
#include "wortal_session.h"
#include "wortal_stats.h"
#include "wortal_tournament.h"
#include "luautils.h"
#include <dmsdk/sdk.h>

#define EXTENSION_NAME Wortal
#define LIB_NAME "Wortal"
#define MODULE_NAME "wortal"
#define VERSION "3.0.1"

#if defined(DM_PLATFORM_HTML5)

lua_Listener onInitializeListener;
lua_Listener onStartGameListener;
lua_Listener onPauseListener;
lua_Listener onResumeListener;
lua_Listener onHapticFeedbackListener;

void Wortal::OnInitialize(const int success, const char *error)
{
    lua_State *L = onInitializeListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onInitializeListener);
    lua_pushboolean(L, success);
    lua_pushstring(L, error);

    int ret = lua_pcall(L, 3, 0, 0);
    if (ret != 0)
    {
        lua_pop(L, 1);
    }

    assert(top == lua_gettop(L));
}

void Wortal::OnStartGame(const int success, const char *error)
{
    lua_State *L = onStartGameListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onStartGameListener);
    lua_pushboolean(L, success);
    lua_pushstring(L, error);

    int ret = lua_pcall(L, 3, 0, 0);
    if (ret != 0)
    {
        lua_pop(L, 1);
    }

    assert(top == lua_gettop(L));
}

void Wortal::OnPause(const int success)
{
    lua_State *L = onPauseListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onPauseListener);
    lua_pushboolean(L, success);

    int ret = lua_pcall(L, 2, 0, 0);
    if (ret != 0)
    {
        lua_pop(L, 1);
    }

    assert(top == lua_gettop(L));
}

void Wortal::OnResume(const int success)
{
    lua_State *L = onResumeListener.m_L;
    int top = lua_gettop(L);

    lua_pushListener(L, onResumeListener);
    lua_pushBoolean(L, success);

    int ret = lua_pcall(L, 2, 0, 0);
    if (ret != 0)
    {
        lua_pop(L, 1);
    }

    assert(top == lua_gettop(L));
}

void Wortal::OnHapticFeedback(const int success, const char *error)
{
    lua_State *L = onHapticFeedbackListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onHapticFeedbackListener);
    lua_pushboolean(L, success);
    lua_pushstring(L, error);

    int ret = lua_pcall(L, 3, 0, 0);
    if (ret != 0)
    {
        lua_pop(L, 1);
    }

    assert(top == lua_gettop(L));
}

int Wortal::IsInitialized(lua_State *L)
{
    int top = lua_gettop(onInitializeListener.m_L);

    lua_pushboolean(onInitializeListener.m_L, Wortal_isInitialized());

    assert(top + 1 == lua_gettop(onInitializeListener.m_L));
    return 1;
}

int Wortal::InitializeAsync(lua_State *L)
{
    int top = lua_gettop(L);

    luaL_checklistener(L, 1, onInitializeListener);

    Wortal_initializeAsync(Wortal::OnInitialize);

    assert(top == lua_gettop(L));
    return 0;
}

int Wortal::StartGameAsync(lua_State *L)
{
    int top = lua_gettop(L);

    luaL_checklistener(L, 1, onStartGameListener);

    Wortal_startGameAsync(Wortal::OnStartGame);

    assert(top == lua_gettop(L));
    return 0;
}

int Wortal::SetLoadingProgress(lua_State *L)
{
    int top = lua_gettop(L);

    int progress = luaL_checkinteger(L, 1);
    Wortal_setLoadingProgress(progress);

    assert(top == lua_gettop(L));
    return 0;
}

int Wortal::SetPauseCallback(lua_State *L)
{
    int top = lua_gettop(L);

    luaL_checklistener(L, 1, onPauseListener);

    Wortal_onPause(Wortal::OnPause);

    assert(top == lua_gettop(L));
    return 0;
}

int Wortal::SetResumeCallback(lua_State *L)
{
    int top = lua_gettop(L);

    luaL_checklistener(L, 1, onResumeListener);

    Wortal_onResume(Wortal::OnResume);

    assert(top == lua_gettop(L));
    return 0;
}

int Wortal::PerformHapticFeedback(lua_State *L)
{
    int top = lua_gettop(L);

    luaL_checklistener(L, 1, onHapticFeedbackListener);

    Wortal_performHapticFeedback(Wortal::OnHapticFeedback);

    assert(top == lua_gettop(L));
    return 0;
}

int Wortal::GetSupportedAPIs(lua_State *L)
{
    int top = lua_gettop(L);

    const char *data = Wortal_getSupportedAPIs();
    if (data)
    {
        lua_pushstring(L, data);
    }
    else
    {
        lua_pushnil(L);
    }

    assert(top + 1 == lua_gettop(L));
    return 1;
}

static const luaL_reg Module_methods[] = {

    {"initialize", Wortal::InitializeAsync},
    {"start_game", Wortal::StartGameAsync},
    {"is_initialized", Wortal::IsInitialized},
    {"set_loading_progress", Wortal::SetLoadingProgress},
    {"on_pause", Wortal::SetPauseCallback},
    {"on_resume", Wortal::SetResumeCallback},
    {"perform_haptic_feedback", Wortal::PerformHapticFeedback},
    {"get_supported_apis", Wortal::GetSupportedAPIs},

    {"achievements_get_achievements", WortalAchievements::GetAchievementsAsync},
    {"achievements_unlock_achievement", WortalAchievements::UnlockAchievementAsync},

    {"ads_is_ad_blocked", WortalAds::IsAdBlocked},
    {"ads_show_interstitial", WortalAds::ShowInterstitial},
    {"ads_show_rewarded", WortalAds::ShowRewarded},
    {"ads_show_banner", WortalAds::ShowBanner},

    {"analytics_log_level_start", WortalAnalytics::LogLevelStart},
    {"analytics_log_level_end", WortalAnalytics::LogLevelEnd},
    {"analytics_log_level_up", WortalAnalytics::LogLevelUp},
    {"analytics_log_score", WortalAnalytics::LogScore},
    {"analytics_log_tutorial_start", WortalAnalytics::LogTutorialStart},
    {"analytics_log_tutorial_end", WortalAnalytics::LogTutorialEnd},
    {"analytics_log_game_choice", WortalAnalytics::LogGameChoice},
    {"analytics_log_social_invite", WortalAnalytics::LogSocialInvite},
    {"analytics_log_social_share", WortalAnalytics::LogSocialShare},
    {"analytics_log_purchase", WortalAnalytics::LogPurchase},
    {"analytics_log_purchase_subscription", WortalAnalytics::LogPurchaseSubscription},

    {"context_get_id", WortalContext::GetID},
    {"context_get_type", WortalContext::GetType},
    {"context_get_players", WortalContext::GetPlayersAsync},
    {"context_choose", WortalContext::ChooseAsync},
    {"context_invite", WortalContext::InviteAsync},
    {"context_share", WortalContext::ShareAsync},
    {"context_share_link", WortalContext::ShareLinkAsync},
    {"context_update", WortalContext::UpdateAsync},
    {"context_switch", WortalContext::SwitchAsync},
    {"context_create", WortalContext::CreateAsync},
    {"context_is_size_between", WortalContext::IsSizeBetween},

    {"iap_is_enabled", WortalIAP::IsEnabled},
    {"iap_get_catalog", WortalIAP::GetCatalogAsync},
    {"iap_get_purchases", WortalIAP::GetPurchasesAsync},
    {"iap_make_purchase", WortalIAP::MakePurchaseAsync},
    {"iap_consume_purchase", WortalIAP::ConsumePurchaseAsync},

    {"leaderboard_get_leaderboard", WortalLeaderboard::GetLeaderboardAsync},
    {"leaderboard_send_entry", WortalLeaderboard::SendEntryAsync},
    {"leaderboard_get_entries", WortalLeaderboard::GetEntriesAsync},
    {"leaderboard_get_player_entry", WortalLeaderboard::GetPlayerEntryAsync},
    {"leaderboard_get_entry_count", WortalLeaderboard::GetEntryCountAsync},
    {"leaderboard_get_connected_players_entries", WortalLeaderboard::GetConnectedPlayersEntriesAsync},

    {"notifications_schedule", WortalNotifications::ScheduleAsync},
    {"notifications_get_history", WortalNotifications::GetHistoryAsync},
    {"notifications_cancel", WortalNotifications::CancelAsync},
    {"notifications_cancel_all", WortalNotifications::CancelAllAsync},

    {"player_get_id", WortalPlayer::GetID},
    {"player_get_name", WortalPlayer::GetName},
    {"player_get_photo", WortalPlayer::GetPhoto},
    {"player_is_first_play", WortalPlayer::IsFirstPlay},
    {"player_get_data", WortalPlayer::GetDataAsync},
    {"player_set_data", WortalPlayer::SetDataAsync},
    {"player_flush_data", WortalPlayer::FlushDataAsync},
    {"player_get_connected_players", WortalPlayer::GetConnectedPlayersAsync},
    {"player_get_signed_info", WortalPlayer::GetSignedPlayerInfoAsync},
    {"player_get_asid", WortalPlayer::GetASIDAsync},
    {"player_get_signed_asid", WortalPlayer::GetSignedASIDAsync},
    {"player_can_subscribe_bot", WortalPlayer::CanSubscribeBotAsync},
    {"player_subscribe_bot", WortalPlayer::SubscribeBotAsync},

    {"session_get_entry_point_data", WortalSession::GetEntryPointData},
    {"session_get_locale", WortalSession::GetLocale},
    {"session_get_traffic_source", WortalSession::GetTrafficSource},
    {"session_set_session_data", WortalSession::SetSessionData},
    {"session_get_entry_point", WortalSession::GetEntryPointAsync},
    {"session_get_platform", WortalSession::GetPlatform},
    {"session_get_device", WortalSession::GetDevice},
    {"session_get_orientation", WortalSession::GetOrientation},
    {"session_on_orientation_change", WortalSession::OnOrientationChange},
    {"session_switch_game", WortalSession::SwitchGameAsync},

    {"stats_get_stats", WortalStats::GetStatsAsync},
    {"stats_post_stats", WortalStats::PostStatsAsync},

    {"tournament_get_current", WortalTournament::GetCurrentAsync},
    {"tournament_get_all", WortalTournament::GetAllAsync},
    {"tournament_post_score", WortalTournament::PostScoreAsync},
    {"tournament_create", WortalTournament::CreateAsync},
    {"tournament_share", WortalTournament::ShareAsync},
    {"tournament_join", WortalTournament::JoinAsync},

    {0, 0}};

static void LuaInit(lua_State *L)
{
    int top = lua_gettop(L);

    luaL_register(L, MODULE_NAME, Module_methods);

    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}

dmExtension::Result InitializeWortalSdk(dmExtension::Params *params)
{
    LuaInit(params->m_L);
    return dmExtension::RESULT_OK;
}

dmExtension::Result FinalizeWortalSdk(dmExtension::Params *params)
{
    return dmExtension::RESULT_OK;
}

#else // unsupported platforms

dmExtension::Result InitializeWortalSdk(dmExtension::Params *params)
{
    return dmExtension::RESULT_OK;
}

dmExtension::Result FinalizeWortalSdk(dmExtension::Params *params)
{
    return dmExtension::RESULT_OK;
}

#endif

DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, 0, 0, InitializeWortalSdk, 0, 0, FinalizeWortalSdk)
