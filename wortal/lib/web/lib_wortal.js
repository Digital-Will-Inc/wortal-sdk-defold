var WortalLib = {

    $Utils: {
        _onPauseCallbackPtr: null,

        onPauseCallback: function () {
            {{{ makeDynCall("vi", "Utils._onPauseCallbackPtr") }}}(1);
        },

        allocateString: function(str) {
            return allocate(intArrayFromString(str), ALLOC_STACK);
        },

        toObjectFromJsonString: function(str) {
            return JSON.parse(UTF8ToString(str));
        }
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
    }

}

autoAddDeps(WortalLib, '$Ads');
autoAddDeps(WortalLib, '$Utils');
mergeInto(LibraryManager.library, WortalLib);
