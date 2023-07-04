var WortalContext = {

    Wortal_context_getID: function () {
        const id = window.Wortal.context.getId();
        if (id) {
            return Utils.allocateString(id);
        } else {
            return null;
        }
    },

    Wortal_context_getType: function () {
        const cType = window.Wortal.context.getType();
        if (cType) {
            return Utils.allocateString(cType);
        } else {
            return null;
        }
    },

    Wortal_context_getPlayersAsync: function (callback) {
        window.Wortal.context.getPlayersAsync()
            .then(players =>  {
                {{{ makeDynCall("vii", "callback") }}}(Utils.allocateString(JSON.stringify(players)), 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(error.code));
            });
    },

    Wortal_context_chooseAsync: function (payload, callback) {
        window.Wortal.context.chooseAsync(Utils.toObjectFromJsonString(payload))
            .then(() => {
                {{{ makeDynCall("vii", "callback") }}}(1, 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(error.code));
            });
    },

    Wortal_context_shareAsync: function (payload, callback) {
        window.Wortal.context.shareAsync(Utils.toObjectFromJsonString(payload))
            .then(shareResult => {
                {{{ makeDynCall("vii", "callback") }}}(shareResult, 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(error.code));
            });
    },

    Wortal_context_shareLinkAsync: function (payload, callback) {
        window.Wortal.context.shareLinkAsync(Utils.toObjectFromJsonString(payload))
            .then(() => {
                {{{ makeDynCall("vii", "callback") }}}(1, 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(error.code));
            });
    },

    Wortal_context_updateAsync: function (payload, callback) {
        window.Wortal.context.updateAsync(Utils.toObjectFromJsonString(payload))
            .then(() => {
                {{{ makeDynCall("vii", "callback") }}}(1, 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(error.code));
            });
    },

    Wortal_context_switchAsync: function (contextId, callback) {
        window.Wortal.context.switchAsync(UTF8ToString(contextId))
            .then(() => {
                {{{ makeDynCall("vii", "callback") }}}(1, 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(error.code));
            });
    },

    Wortal_context_createAsync: function (playerId, callback) {
        window.Wortal.context.createAsync(UTF8ToString(playerId))
            .then(() => {
                {{{ makeDynCall("vii", "callback") }}}(1, 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(error.code));
            });
    },

    Wortal_context_isSizeBetween: function (minSize, maxSize) {
        const result = window.Wortal.context.isSizeBetween(minSize, maxSize);
        if (result) {
            return Utils.allocateString(result);
        } else {
            return null;
        }
    }

}

mergeInto(LibraryManager.library, WortalContext);
