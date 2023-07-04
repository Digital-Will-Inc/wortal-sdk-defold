var WortalPlayer = {

    Wortal_player_getID: function () {
        return Utils.allocateString(window.Wortal.player.getID());
    },

    Wortal_player_getName: function () {
        return Utils.allocateString(window.Wortal.player.getName());
    },

    Wortal_player_getPhoto: function () {
        return Utils.allocateString(window.Wortal.player.getPhoto());
    },

    Wortal_player_isFirstPlay: function () {
        return window.Wortal.player.isFirstPlay() ? 1 : 0;
    },

    Wortal_player_getDataAsync: function (keys, callback) {
        window.Wortal.player.getDataAsync(Utils.toObjectFromJsonString(keys))
            .then(data =>  {
                {{{ makeDynCall("vii", "callback") }}}(Utils.allocateString(JSON.stringify(data)), 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(error.code));
            });
    },

    Wortal_player_setDataAsync: function (data, callback) {
        window.Wortal.player.setDataAsync(Utils.toObjectFromJsonString(data))
            .then(() =>  {
                {{{ makeDynCall("vii", "callback") }}}(1, 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(error.code));
            });
    },

    Wortal_player_flushDataAsync: function (callback) {
        window.Wortal.player.flushDataAsync()
            .then(() =>  {
                {{{ makeDynCall("vii", "callback") }}}(1, 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(error.code));
            });
    },

    Wortal_player_getConnectedPlayersAsync: function (payload, callback) {
        window.Wortal.player.getConnectedPlayersAsync(Utils.toObjectFromJsonString(payload))
            .then(players =>  {
                {{{ makeDynCall("vii", "callback") }}}(Utils.allocateString(JSON.stringify(players)), 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(error.code));
            });
    },

    Wortal_player_getSignedPlayerInfoAsync: function (callback) {
        window.Wortal.player.getSignedPlayerInfoAsync()
            .then(info =>  {
                {{{ makeDynCall("vii", "callback") }}}(Utils.allocateString(JSON.stringify(info)), 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(error.code));
            });
    },

    Wortal_player_getASIDAsync: function (callback) {
        window.Wortal.player.getASIDAsync()
            .then(asid =>  {
                {{{ makeDynCall("vii", "callback") }}}(Utils.allocateString(asid), 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(error.code));
            });
    },

    Wortal_player_getSignedASIDAsync: function (callback) {
        window.Wortal.player.getSignedASIDAsync()
            .then(asid =>  {
                {{{ makeDynCall("vii", "callback") }}}(Utils.allocateString(asid), 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(error.code));
            });
    },

    Wortal_player_canSubscribeBotAsync: function (callback) {
        window.Wortal.player.canSubscribeBotAsync()
            .then(canSubscribe =>  {
                {{{ makeDynCall("vii", "callback") }}}(canSubscribe ? 1 : 0, 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(error.code));
            });
    },

    Wortal_player_subscribeBotAsync: function (callback) {
        window.Wortal.player.subscribeBotAsync()
            .then(() =>  {
                {{{ makeDynCall("vii", "callback") }}}(1, 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(error.code));
            });
    }

}

mergeInto(LibraryManager.library, WortalPlayer);
