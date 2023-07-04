var WortalSession = {

    Wortal_session_getEntryPointData: function () {
        return Utils.allocateString(JSON.stringify(window.Wortal.session.getEntryPointData()));
    },

    Wortal_session_getLocale: function () {
        return Utils.allocateString(window.Wortal.session.getLocale());
    },

    Wortal_session_getTrafficSource: function () {
        return Utils.allocateString(JSON.stringify(window.Wortal.session.getTrafficSource()));
    },

    Wortal_session_setSessionData: function (data) {
        window.Wortal.session.setSessionData(Utils.toObjectFromJsonString(data));
    },

    Wortal_session_getEntryPointAsync: function (callback) {
        window.Wortal.session.getEntryPointAsync()
            .then(entryPoint =>  {
                {{{ makeDynCall("vii", "callback") }}}(Utils.allocateString(entryPoint), 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(error.code));
            });
    },

    Wortal_session_getPlatform: function () {
        return Utils.allocateString(window.Wortal.session.getPlatform());
    }

}

mergeInto(LibraryManager.library, WortalSession);
