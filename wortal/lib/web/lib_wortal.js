var WortalLib = {

    $Ads: {
        _beforeAdCallbackPtr: null,
        _afterAdCallbackPtr: null,
        _adDismissedCallbackPtr: null,
        _adViewedCallbackPtr: null,

        beforeAdCallback: function () {
            {{{ makeDynCall("vi", "Ads._beforeAdCallbackPtr") }}}(1);
        },

        afterAdCallback: function () {
            {{{ makeDynCall("vi", "Ads._afterAdCallbackPtr") }}}(1);
        },

        adDismissedCallback: function () {
            {{{ makeDynCall("vi", "Ads._adDismissedCallbackPtr") }}}(1);
        },

        adViewedCallback: function () {
            {{{ makeDynCall("vi", "Ads._adViewedCallbackPtr") }}}(1);
        },
    },

    $Utils: {
        allocateString: function(str) {
            return allocate(intArrayFromString(str), ALLOC_STACK);
        },
        toObjectFromJsonString: function(str) {
            return JSON.parse(UTF8ToString(str));
        }
    },

    //////////////////////////////////////////////////////////////////////
    // Ads API
    //////////////////////////////////////////////////////////////////////

    Wortal_ads_showInterstitial: function (placement, description, beforeAdCallback, afterAdCallback) {
        Ads._beforeAdCallbackPtr = beforeAdCallback;
        Ads._afterAdCallbackPtr = afterAdCallback;

        window.Wortal.ads.showInterstitial(UTF8ToString(placement), UTF8ToString(description),
            Ads.beforeAdCallback, Ads.afterAdCallback);
    },

    Wortal_ads_showRewarded: function (description, beforeAdCallback, afterAdCallback, adDismissedCallback, adViewedCallback) {
        Ads._beforeAdCallbackPtr = beforeAdCallback;
        Ads._afterAdCallbackPtr = afterAdCallback;
        Ads._adDismissedCallbackPtr = adDismissedCallback;
        Ads._adViewedCallbackPtr = adViewedCallback;

        window.Wortal.ads.showRewarded(UTF8ToString(description), Ads.beforeAdCallback, Ads.afterAdCallback,
            Ads.adDismissedCallback, Ads.adViewedCallback);
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

    Wortal_context_getID: function () {
        const id = window.Wortal.context.getId();
        if (id) {
            return Utils.allocateString(id);
        } else {
            return null;
        }
    },

    Wortal_context_chooseAsync: function (payload, callback) {
        window.Wortal.context.chooseAsync(Utils.toObjectFromJsonString(payload))
            .then(() => {
                {{{ makeDynCall("vii", "callback") }}}(1, 0);
            })
            .catch(error => {
                console.error(error);
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(error.code));
            });
    },

    Wortal_context_shareAsync: function (payload, callback) {
        window.Wortal.context.shareAsync(Utils.toObjectFromJsonString(payload))
            .then(shareResult => {
                {{{ makeDynCall("vii", "callback") }}}(shareResult, 0);
            })
            .catch(error => {
                console.error(error);
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(error.code));
            });
    },

    Wortal_context_updateAsync: function (payload, callback) {
        window.Wortal.context.updateAsync(Utils.toObjectFromJsonString(payload))
            .then(() => {
                {{{ makeDynCall("vii", "callback") }}}(1, 0);
            })
            .catch(error => {
                console.error(error);
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(error.code));
            });
    },

    Wortal_context_switchAsync: function (contextId, callback) {
        window.Wortal.context.switchAsync(UTF8ToString(contextId))
            .then(() => {
                {{{ makeDynCall("vii", "callback") }}}(1, 0);
            })
            .catch(error => {
                console.error(error);
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(error.code));
            });
    },

    Wortal_context_createAsync: function (playerId, callback) {
        window.Wortal.context.createAsync(UTF8ToString(playerId))
            .then(() => {
                {{{ makeDynCall("vii", "callback") }}}(1, 0);
            })
            .catch(error => {
                console.error(error);
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(error.code));
            });
    },

    //////////////////////////////////////////////////////////////////////
    // In-App Purchases API
    //////////////////////////////////////////////////////////////////////

    Wortal_iap_isEnabled: function () {
        return window.Wortal.iap.isEnabled() ? 1 : 0;
    },

    Wortal_iap_getCatalogAsync: function (callback) {
        window.Wortal.iap.getCatalogAsync()
            .then(catalog => {
                {{{ makeDynCall("vii", "callback") }}}(Utils.allocateString(JSON.stringify(catalog)), 0);
            })
            .catch(error => {
                console.error(error);
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(error.code));
            });
    },

    Wortal_iap_getPurchasesAsync: function (callback) {
        window.Wortal.iap.getPurchasesAsync()
            .then(purchases => {
                {{{ makeDynCall("vii", "callback") }}}(Utils.allocateString(JSON.stringify(purchases)), 0);
            })
            .catch(error => {
                console.error(error);
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(error.code));
            });
    },

    Wortal_iap_makePurchaseAsync: function (purchaseConfig, callback) {
        window.Wortal.iap.makePurchaseAsync(Utils.toObjectFromJsonString(purchaseConfig))
            .then(purchase => {
                {{{ makeDynCall("vii", "callback") }}}(Utils.allocateString(JSON.stringify(purchase)), 0);
            })
            .catch(error => {
                console.error(error);
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(error.code));
            });
    },

    Wortal_iap_consumePurchaseAsync: function (token, callback) {
        window.Wortal.iap.consumePurchaseAsync(UTF8ToString(token))
            .then(() => {
                {{{ makeDynCall("vii", "callback") }}}(1, 0);
            })
            .catch(error => {
                console.error(error);
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(error.code));
            });
    }

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

autoAddDeps(WortalLib, '$Ads');
autoAddDeps(WortalLib, '$Utils');
mergeInto(LibraryManager.library, WortalLib);
