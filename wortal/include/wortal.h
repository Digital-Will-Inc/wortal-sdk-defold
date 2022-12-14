#pragma once

#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_HTML5)

// Ads callbacks
typedef void (*OnBeforeAdCallback)(const int success);
typedef void (*OnAfterAdCallback)(const int success);
typedef void (*OnAdDismissedCallback)(const int success);
typedef void (*OnAdViewedCallback)(const int success);

// Context callbacks
typedef void (*OnContextCallback)(const int success, const char* error);
typedef void (*OnContextShareCallback)(const int shareResult, const char* error);

// IAP callbacks
typedef void (*OnGetCatalogCallback)(const char* catalog, const char* error);
typedef void (*OnGetPurchasesCallback)(const char* purchases, const char* error);
typedef void (*OnMakePurchaseCallback)(const char* purchase, const char* error);
typedef void (*OnConsumePurchaseCallback)(const int success, const char* error);

// Leaderboard callbacks
typedef void (*OnGetLeaderboardCallback)(const char* leaderboard, const char* error);
typedef void (*OnLeaderboardSendEntryCallback)(const char* entry, const char* error);
typedef void (*OnLeaderboardGetEntriesCallback)(const char* entries, const char* error);
typedef void (*OnLeaderboardGetPlayerEntryCallback)(const char* entry, const char* error);
typedef void (*OnLeaderboardGetEntryCountCallback)(const int count, const char* error);
typedef void (*OnLeaderboardGetConnectedPlayersEntriesCallback)(const char* entries, const char* error);

// Player callbacks
typedef void (*OnPlayerGetDataCallback)(const char* data, const char* error);
typedef void (*OnPlayerSetDataCallback)(const int success, const char* error);
typedef void (*OnGetConnectedPlayersCallback)(const char* players, const char* error);
typedef void (*OnGetSignedPlayerInfoCallback)(const char* info, const char* error);

// Session callbacks
typedef void (*OnGetEntryPointCallback)(const char* data, const char* error);

extern "C" {

    // Ads API
    void Wortal_ads_showInterstitial(const char* type, const char* description, OnBeforeAdCallback beforeAdCallback,
    OnAfterAdCallback afterAdCallback);

    void Wortal_ads_showRewarded(const char* description, OnBeforeAdCallback beforeAdCallback,
    OnAfterAdCallback afterAdCallback, OnAdDismissedCallback adDismissedCallback, OnAdViewedCallback adViewedCallback);

    // Analytics API
    void Wortal_analytics_logLevelStart(const char* level);
    void Wortal_analytics_logLevelEnd(const char* level, const char* score, const int wasCompleted);
    void Wortal_analytics_logLevelUp(const char* level);
    void Wortal_analytics_logScore(const char* score);
    void Wortal_analytics_logTutorialStart(const char* tutorial);
    void Wortal_analytics_logTutorialEnd(const char* tutorial, const int wasCompleted);
    void Wortal_analytics_logGameChoice(const char* decision, const char* choice);

    // Context API
    char* Wortal_context_getID();
    void Wortal_context_chooseAsync(const char* payload, OnContextCallback callback);
    void Wortal_context_shareAsync(const char* payload, OnContextShareCallback callback);
    void Wortal_context_updateAsync(const char* payload, OnContextCallback callback);
    void Wortal_context_switchAsync(const char* contextId, OnContextCallback callback);
    void Wortal_context_createAsync(const char* playerId, OnContextCallback callback);

    // In-App Purchasing API
    int Wortal_iap_isEnabled();
    void Wortal_iap_getCatalogAsync(OnGetCatalogCallback callback);
    void Wortal_iap_getPurchasesAsync(OnGetPurchasesCallback callback);
    void Wortal_iap_makePurchaseAsync(const char* purchaseConfig, OnMakePurchaseCallback callback);
    void Wortal_iap_consumePurchaseAsync(const char* token, OnConsumePurchaseCallback callback);

    // Leaderboard API
    void Wortal_leaderboard_getLeaderboardAsync(const char* leaderboard, OnGetLeaderboardCallback callback);
    void Wortal_leaderboard_sendEntryAsync(const char* leaderboard, const int score, const char* details, OnLeaderboardSendEntryCallback callback);
    void Wortal_leaderboard_getEntriesAsync(const char* leaderboard, const int count, const int offset, OnLeaderboardGetEntriesCallback callback);
    void Wortal_leaderboard_getPlayerEntryAsync(const char* leaderboard, OnLeaderboardGetPlayerEntryCallback callback);
    void Wortal_leaderboard_getEntryCountAsync(const char* leaderboard, OnLeaderboardGetEntryCountCallback callback);
    void Wortal_leaderboard_getConnectedPlayersEntriesAsync(const char* leaderboard, const int count, const int offset, OnLeaderboardGetConnectedPlayersEntriesCallback callback);

    // Player API
    char* Wortal_player_getID();
    char* Wortal_player_getName();
    char* Wortal_player_getPhoto();
    int Wortal_player_isFirstPlay();
    void Wortal_player_getDataAsync(const char* keys, OnPlayerGetDataCallback callback);
    void Wortal_player_setDataAsync(const char* data, OnPlayerSetDataCallback callback);
    void Wortal_player_getConnectedPlayersAsync(const char* payload, OnGetConnectedPlayersCallback callback);
    void Wortal_player_getSignedPlayerInfoAsync(OnGetSignedPlayerInfoCallback callback);

    // Session API
    char* Wortal_session_getEntryPointData();
    char* Wortal_session_getLocale();
    char* Wortal_session_getTrafficSource();
    void Wortal_session_setSessionData(const char* data);
    void Wortal_session_getEntryPointAsync(OnGetEntryPointCallback callback);
}

#endif
