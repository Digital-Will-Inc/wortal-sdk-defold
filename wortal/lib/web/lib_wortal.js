var WortalLib = {

    $Utils: {
        _onPauseCallbackPtr: null,

        onPauseCallback: function () {
            {{{ makeDynCall("vi", "Utils._onPauseCallbackPtr") }}}(1);
        },

        allocateString: function(str) {
            return stringToUTF8OnStack(str);
        },

        toObjectFromJsonString: function(str) {
            return JSON.parse(UTF8ToString(str) || "{}");
        }
    },

    Wortal_isInitialized: function () {
        return window.Wortal.isInitialized();
    },

    Wortal_initializeAsync: function (callback) {
        window.Wortal.initializeAsync()
            .then(() =>  {
                {{{ makeDynCall("vii", "callback") }}}(1, 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(JSON.stringify(error)));
            });
    },

    Wortal_startGameAsync: function (callback) {
        window.Wortal.startGameAsync()
            .then(() =>  {
                {{{ makeDynCall("vii", "callback") }}}(1, 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(JSON.stringify(error)));
            });
    },

    Wortal_setLoadingProgress: function (progress) {
        window.Wortal.setLoadingProgress(progress);
    },

    Wortal_onPause: function (callback) {
        Utils._onPauseCallbackPtr = callback;

        window.Wortal.onPause(() => Utils.onPauseCallback);
    },

    Wortal_performHapticFeedback: function (callback) {
        window.Wortal.performHapticFeedbackAsync()
            .then(() =>  {
                {{{ makeDynCall("vii", "callback") }}}(1, 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(JSON.stringify(error)));
            });
    },

    Wortal_getSupportedAPIs: function () {
        return Utils.allocateString(JSON.stringify(window.Wortal.getSupportedAPIs()));
    }

}

autoAddDeps(WortalLib, '$Ads');
autoAddDeps(WortalLib, '$Utils');
addToLibrary(WortalLib);
