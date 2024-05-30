var WortalLeaderboard = {

    Wortal_leaderboard_getLeaderboardAsync: function (leaderboard, callback) {
        window.Wortal.leaderboard.getLeaderboardAsync(UTF8ToString(leaderboard))
            .then(leaderboard => {
                {{{ makeDynCall("vii", "callback") }}}(Utils.allocateString(JSON.stringify(leaderboard)), 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(JSON.stringify(error)));
            });
    },

    Wortal_leaderboard_sendEntryAsync: function (leaderboard, score, details, callback) {
        window.Wortal.leaderboard.sendEntryAsync(UTF8ToString(leaderboard), score, UTF8ToString(details))
            .then(entry => {
                {{{ makeDynCall("vii", "callback") }}}(Utils.allocateString(JSON.stringify(entry)), 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(JSON.stringify(error)));
            });
    },

    Wortal_leaderboard_getEntriesAsync: function (leaderboard, count, offset, callback) {
        window.Wortal.leaderboard.getEntriesAsync(UTF8ToString(leaderboard), count, offset)
            .then(entries =>  {
                {{{ makeDynCall("vii", "callback") }}}(Utils.allocateString(JSON.stringify(entries)), 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(JSON.stringify(error)));
            });
    },

    Wortal_leaderboard_getPlayerEntryAsync: function (leaderboard, callback) {
        window.Wortal.leaderboard.getPlayerEntryAsync(UTF8ToString(leaderboard))
            .then(entry => {
                {{{ makeDynCall("vii", "callback") }}}(Utils.allocateString(JSON.stringify(entry)), 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(JSON.stringify(error)));
            });
    },

    Wortal_leaderboard_getEntryCountAsync: function (leaderboard, callback) {
        window.Wortal.leaderboard.getEntryCountAsync(UTF8ToString(leaderboard))
            .then(count => {
                {{{ makeDynCall("vii", "callback") }}}(count, 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(JSON.stringify(error)));
            });
    },

    Wortal_leaderboard_getConnectedPlayersEntriesAsync: function (leaderboard, count, offset, callback) {
        window.Wortal.leaderboard.getConnectedPlayersEntriesAsync(UTF8ToString(leaderboard), count, offset)
            .then(entries =>  {
                {{{ makeDynCall("vii", "callback") }}}(Utils.allocateString(JSON.stringify(entries)), 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(JSON.stringify(error)));
            });
    }

}

addToLibrary(WortalLeaderboard);
