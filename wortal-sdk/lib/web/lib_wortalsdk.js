var LibWortalSdk = {

    $WortalSdk: {

        _beforeAdCallbackPtr: null,
        _afterAdCallbackPtr: null,
        _adDismissedCallbackPtr: null,
        _adViewedCallbackPtr: null,

        beforeAdCallback: function () {
            {{{ makeDynCall("v", "WortalSdk._beforeAdCallbackPtr") }}}();
        },

        afterAdCallback: function () {
            {{{ makeDynCall("v", "WortalSdk._afterAdCallbackPtr") }}}();
        },

        adDismissedCallback: function () {
            {{{ makeDynCall("v", "WortalSdk._adDismissedCallbackPtr") }}}();
        },

        adViewedCallback: function () {
            {{{ makeDynCall("v", "WortalSdk._adViewedCallbackPtr") }}}();
        },
    },

    //////////////////////////////////////////////////////////////////////
    // Ads API
    //////////////////////////////////////////////////////////////////////

    Wortal_ads_showInterstitial: function (placement, description, beforeAdCallback, afterAdCallback) {
        WortalSdk._beforeAdCallbackPtr = beforeAdCallback;
        WortalSdk._afterAdCallbackPtr = afterAdCallback;

        window.Wortal.ads.showInterstitial(UTF8ToString(placement), UTF8ToString(description),
            WortalSdk.beforeAdCallback, WortalSdk.afterAdCallback);
    },

    Wortal_ads_showRewarded: function (description, beforeAdCallback, afterAdCallback, adDismissedCallback, adViewedCallback) {
        WortalSdk._beforeAdCallbackPtr = beforeAdCallback;
        WortalSdk._afterAdCallbackPtr = afterAdCallback;
        WortalSdk._adDismissedCallbackPtr = adDismissedCallback;
        WortalSdk._adViewedCallbackPtr = adViewedCallback;

        window.Wortal.ads.showRewarded(UTF8ToString(description), WortalSdk.beforeAdCallback, WortalSdk.afterAdCallback,
            WortalSdk.adDismissedCallback, WortalSdk.adViewedCallback);
    },

    //////////////////////////////////////////////////////////////////////
    // Analytics API
    //////////////////////////////////////////////////////////////////////

    Wortal_analytics_logLevelStart: function (level) {
        window.Wortal.analytics.logLevelStart(UTF8ToString(level));
    },

    Wortal_analytics_logLevelEnd: function (level, score, wasCompleted) {
        const completed = wasCompleted > 0;
        window.Wortal.analytics.logLevelEnd(UTF8ToString(level), UTF8ToString(score), completed);
    },

    Wortal_analytics_logLevelUp: function (level) {
        window.Wortal.analytics.logLevelUp(UTF8ToString(level));
    },

    Wortal_analytics_logScore: function (score) {
        window.Wortal.analytics.logScore(UTF8ToString(score));
    },

    Wortal_analytics_logTutorialStart: function (tutorial) {
        window.Wortal.analytics.logTutorialStart(UTF8ToString(tutorial));
    },

    Wortal_analytics_logTutorialEnd: function (tutorial, wasCompleted) {
        const completed = wasCompleted > 0;
        window.Wortal.analytics.logTutorialEnd(UTF8ToString(tutorial), completed);
    },

    Wortal_analytics_logGameChoice: function (decision, choice) {
        window.Wortal.analytics.logGameChoice(UTF8ToString(decision), UTF8ToString(choice))
    },

    //////////////////////////////////////////////////////////////////////
    // Context API
    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
    // In-App Purchases API
    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
    // Leaderboard API
    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
    // Player API
    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
    // Session API
    //////////////////////////////////////////////////////////////////////
}

autoAddDeps(LibWortalSdk, '$WortalSdk');
mergeInto(LibraryManager.library, LibWortalSdk);
