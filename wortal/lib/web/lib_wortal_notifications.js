var WortalNotifications = {

    Wortal_notifications_scheduleAsync: function (payload, callback) {
        window.Wortal.notifications.scheduleAsync(Utils.toObjectFromJsonString(payload))
            .then(result => {
                {{{ makeDynCall("vii", "callback") }}}(Utils.allocateString(JSON.stringify(result)), 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(JSON.stringify(error)));
            });
    },

    Wortal_notifications_getHistoryAsync: function (callback) {
        window.Wortal.notifications.getHistoryAsync()
            .then(result => {
                {{{ makeDynCall("vii", "callback") }}}(Utils.allocateString(JSON.stringify(result)), 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(JSON.stringify(error)));
            });
    },

    Wortal_notifications_cancelAsync: function (id, callback) {
        window.Wortal.notifications.cancelAsync(Utils.toObjectFromJsonString(id))
            .then(() => {
                {{{ makeDynCall("vii", "callback") }}}(1, 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(JSON.stringify(error)));
            });
    },

    Wortal_notifications_cancelAllAsync: function (label, callback) {
        window.Wortal.notifications.cancelAllAsync(Utils.toObjectFromJsonString(label))
            .then(() => {
                {{{ makeDynCall("vii", "callback") }}}(1, 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(JSON.stringify(error)));
            });
    }

}

addToLibrary(WortalNotifications);
