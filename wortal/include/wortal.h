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

// Player callbacks

// Session callbacks

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
}

#endif
