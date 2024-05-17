var WortalStats = {

    Wortal_stats_getStatsAsync: function (level, payload, callback) {
        window.Wortal.stats.getStatsAsync(level, payload)
            .then(stats => {
                {{{ makeDynCall("vii", "callback") }}}(Utils.allocateString(JSON.stringify(stats)), 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(JSON.stringify(error)));
            });
    },

    Wortal_stats_postStatsAsync: function (level, value, payload, callback) {
        window.Wortal.stats.postStatsAsync(level, value, payload)
            .then(() => {
                {{{ makeDynCall("vii", "callback") }}}(1, 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(JSON.stringify(error)));
            });
    }

}

mergeInto(LibraryManager.library, WortalStats);
