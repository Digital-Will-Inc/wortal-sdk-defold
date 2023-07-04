#pragma once

#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_HTML5)

class WortalAds {
public:
    typedef void (*OnBeforeAdCallback)(const int success);
    typedef void (*OnAfterAdCallback)(const int success);
    typedef void (*OnAdDismissedCallback)(const int success);
    typedef void (*OnAdViewedCallback)(const int success);
    typedef void (*OnNoFillCallback)(const int success);

    static int ShowInterstitial(lua_State* L);
    static int ShowRewarded(lua_State* L);

private:
    static void OnBeforeAd(const int success);
    static void OnAfterAd(const int success);
    static void OnAdDismissed(const int success);
    static void OnAdViewed(const int success);
    static void OnNoFill(const int success);
};

extern "C" {
    void Wortal_ads_showInterstitial(const char* type,
                                     const char* description,
                                     WortalAds::OnBeforeAdCallback beforeAdCallback,
                                     WortalAds::OnAfterAdCallback afterAdCallback,
                                     WortalAds::OnNoFillCallback noFillCallback);

    void Wortal_ads_showRewarded(const char* description,
                                 WortalAds::OnBeforeAdCallback beforeAdCallback,
                                 WortalAds::OnAfterAdCallback afterAdCallback,
                                 WortalAds::OnAdDismissedCallback adDismissedCallback,
                                 WortalAds::OnAdViewedCallback adViewedCallback,
                                 WortalAds::OnNoFillCallback noFillCallback);
}

#endif
