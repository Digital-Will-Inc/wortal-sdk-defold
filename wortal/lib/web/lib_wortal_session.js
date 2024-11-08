var WortalSession = {

    Wortal_session_gameplayStart: function ()
    {
        window.Wortal.session.gameplayStart();
    },

    Wortal_session_gameplayStop: function ()
    {
        window.Wortal.session.gameplayStop();
    },

    Wortal_session_happyTime: function ()
    {
        window.Wortal.session.happyTime();
    },

    Wortal_session_getEntryPointData: function ()
    {
        return Utils.allocateString(JSON.stringify(window.Wortal.session.getEntryPointData()));
    },

    Wortal_session_getLocale: function ()
    {
        return Utils.allocateString(window.Wortal.session.getLocale());
    },

    Wortal_session_getTrafficSource: function ()
    {
        return Utils.allocateString(JSON.stringify(window.Wortal.session.getTrafficSource()));
    },

    Wortal_session_setSessionData: function (data)
    {
        window.Wortal.session.setSessionData(Utils.toObjectFromJsonString(data));
    },

    Wortal_session_getEntryPointAsync: function (callback)
    {
        window.Wortal.session.getEntryPointAsync()
            .then(entryPoint =>
            {
                { { { makeDynCall("vii", "callback") } } } (Utils.allocateString(entryPoint), 0);
            })
            .catch(error =>
            {
                { { { makeDynCall("vii", "callback") } } } (0, Utils.allocateString(JSON.stringify(error)));
            });
    },

    Wortal_session_getPlatform: function ()
    {
        return Utils.allocateString(window.Wortal.session.getPlatform());
    },

    Wortal_session_getDevice: function ()
    {
        return Utils.allocateString(window.Wortal.session.getDevice());
    },

    Wortal_session_getOrientation: function ()
    {
        return Utils.allocateString(window.Wortal.session.getOrientation());
    },

    Wortal_session_onOrientationChange: function (callback)
    {
        window.Wortal.session.onOrientationChange(orientation =>
        {
            { { { makeDynCall("vi", "callback") } } } (Utils.allocateString(orientation));
        });
    },

    Wortal_session_switchGameAsync: function (gameId, callback)
    {
        window.Wortal.session.switchGameAsync(gameId)
            .then(() =>
            {
                { { { makeDynCall("vii", "callback") } } } (0, 0);
            })
            .catch(error =>
            {
                { { { makeDynCall("vii", "callback") } } } (Utils.allocateString(JSON.stringify(error)), 0);
            });
    },

    Wortal_session_isAudioEnabled: function ()
    {
        return window.Wortal.session.isAudioEnabled() ? 1 : 0;
    },

    Wortal_session_onAudioStatusChange: function (callback)
    {
        window.Wortal.session.onAudioStatusChange(isAudioEnabled =>
        {
            { { { makeDynCall("vi", "callback") } } } (isAudioEnabled);
        })
    }

}

addToLibrary(WortalSession);
