var WortalAds = {

    $Ads: {
        _beforeAdCallbackPtr: null,
        _afterAdCallbackPtr: null,
        _adDismissedCallbackPtr: null,
        _adViewedCallbackPtr: null,
        _noFillCallbackPtr: null,

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

        noFillCallback: function () {
            {{{ makeDynCall("vi", "Ads._noFillCallbackPtr") }}}(1);
        }
    },

    Wortal_ads_showInterstitial: function (placement, description, beforeAdCallback, afterAdCallback, noFillCallback) {
        Ads._beforeAdCallbackPtr = beforeAdCallback;
        Ads._afterAdCallbackPtr = afterAdCallback;
        Ads._noFillCallbackPtr = noFillCallback;

        window.Wortal.ads.showInterstitial(UTF8ToString(placement), UTF8ToString(description),
            Ads.beforeAdCallback, Ads.afterAdCallback, Ads.noFillCallback);
    },

    Wortal_ads_showRewarded: function (description, beforeAdCallback, afterAdCallback, adDismissedCallback,
                                       adViewedCallback, noFillCallback) {
        Ads._beforeAdCallbackPtr = beforeAdCallback;
        Ads._afterAdCallbackPtr = afterAdCallback;
        Ads._adDismissedCallbackPtr = adDismissedCallback;
        Ads._adViewedCallbackPtr = adViewedCallback;
        Ads._noFillCallbackPtr = noFillCallback;

        window.Wortal.ads.showRewarded(UTF8ToString(description), Ads.beforeAdCallback, Ads.afterAdCallback,
            Ads.adDismissedCallback, Ads.adViewedCallback, Ads.noFillCallback);
    },

}

autoAddDeps(WortalLib, '$Ads');
autoAddDeps(WortalLib, '$Utils');
mergeInto(LibraryManager.library, WortalAds);
