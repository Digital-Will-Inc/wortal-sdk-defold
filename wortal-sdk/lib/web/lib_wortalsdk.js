// https://kripken.github.io/emscripten-site/docs/porting/connecting_cpp_and_javascript/Interacting-with-code.html

var LibWortalSdk = {

    $WortalSdk: {

        _beforeAdCallbackPtr: null,
        _afterAdCallbackPtr: null,
        _adDismissedCallbackPtr: null,
        _adViewedCallbackPtr: null,

        beforeAdCallback: function () {
            console.log("Calling before ad..");
            {{{ makeDynCall("v", "WortalSdk._beforeAdCallbackPtr") }}}();
        },

        afterAdCallback: function () {
            console.log("Calling after ad..");
            {{{ makeDynCall("v", "WortalSdk._afterAdCallbackPtr") }}}();
        },

        adDismissedCallback: function () {
            console.log("Calling ad dismissed..");
            {{{ makeDynCall("v", "WortalSdk._adDismissedCallbackPtr") }}}();
        },

        adViewedCallback: function () {
            console.log("Calling ad viewed..");
            {{{ makeDynCall("v", "WortalSdk._adViewedCallbackPtr") }}}();
        },
    },

    js_showInterstitial: function (placement, description, beforeAdCallback, afterAdCallback) {
        WortalSdk._beforeAdCallbackPtr = beforeAdCallback;
        WortalSdk._afterAdCallbackPtr = afterAdCallback;
        var callbacks = {
            beforeAd: WortalSdk.beforeAdCallback,
            afterAd: WortalSdk.afterAdCallback,
            noShow: WortalSdk.afterAdCallback,
            noBreak: WortalSdk.afterAdCallback,
            adBreakDone: () => console.log("AdBreakDone")
        };
        window.triggerWortalAd(UTF8ToString(placement), gameData.linkInterstitialId, UTF8ToString(description), callbacks);
    },

   js_showRewarded: function (description, beforeAdCallback, afterAdCallback, adDismissedCallback, adViewedCallback) {
        WortalSdk._beforeAdCallbackPtr = beforeAdCallback;
        WortalSdk._afterAdCallbackPtr = afterAdCallback;
        WortalSdk._adDismissedCallbackPtr = adDismissedCallback;
        WortalSdk._adViewedCallbackPtr = adViewedCallback;
        var callbacks = {
            beforeAd: WortalSdk.beforeAdCallback,
            afterAd: WortalSdk.afterAdCallback,
            noShow: WortalSdk.afterAdCallback,
            noBreak: WortalSdk.afterAdCallback,
            adDismissed: WortalSdk.adDismissedCallback,
            adViewed: WortalSdk.adViewedCallback,
            beforeReward: (showAdFn) => showAdFn(),
            adBreakDone: () => console.log("AdBreakDone")
        };
        window.triggerWortalAd('reward', gameData.linkRewardedId, UTF8ToString(description), callbacks);
    },

    js_logLevelStart: function (level) {
        if (gameData.levelTimerHandle != null) {
            clearInterval(gameData.levelTimerHandle);
            gameData.levelTimerHandle = null;
        }
        gameData.levelName = level;
        gameData.levelTimer = 0;
        gameData.levelTimerHandle = setInterval(() => gameData.levelTimer += 1, 1000);
        _logEvent("LevelStart", {
            game: gameData.gameName,
            level: level,
        });
    },

    js_logLevelEnd: function (level, score) {
        if (gameData.levelTimerHandle != null) {
            clearInterval(gameData.levelTimerHandle);
            gameData.levelTimerHandle = null;
        }
        if (gameData.levelName !== level) {
            gameData.levelTimer = 0;
        }
        _logEvent("LevelEnd", {
            game: gameData.gameName,
            level: level,
            time: gameData.levelTimer,
            score: score,
        });
        gameData.levelTimer = 0;
    },

    js_logLevelUp: function (level) {
        _logEvent("LevelUp", {
            game: gameData.gameName,
            level: level
        });
    },

    js_logScore: function (score) {
        _logEvent("PostScore", {
            game: gameData.gameName,
            score: score
        });
    },

    js_logGameChoice: function (decision, choice) {
        _logEvent("GameChoice", {
            game: gameData.gameName,
            decision: decision,
            choice: choice,
        });
    },
}

autoAddDeps(LibWortalSdk, '$WortalSdk');
mergeInto(LibraryManager.library, LibWortalSdk);
