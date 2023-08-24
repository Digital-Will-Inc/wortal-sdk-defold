var WortalTournament = {

    Wortal_tournament_getCurrentAsync: function (callback) {
        window.Wortal.tournament.getCurrentAsync()
            .then(tournament =>  {
                {{{ makeDynCall("vii", "callback") }}}(Utils.allocateString(JSON.stringify(tournament)), 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(JSON.stringify(error)));
            });
    },

    Wortal_tournament_getAllAsync: function (callback) {
        window.Wortal.tournament.getAllAsync()
            .then(tournaments =>  {
                {{{ makeDynCall("vii", "callback") }}}(Utils.allocateString(JSON.stringify(tournaments)), 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(JSON.stringify(error)));
            });
    },

    Wortal_tournament_postScoreAsync: function (score, callback) {
        window.Wortal.tournament.postScoreAsync(score)
            .then(() => {
                {{{ makeDynCall("vii", "callback") }}}(1, 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(JSON.stringify(error)));
            });
    },

    Wortal_tournament_createAsync: function (payload, callback) {
        window.Wortal.tournament.createAsync(Utils.toObjectFromJsonString(payload))
            .then(tournament => {
                {{{ makeDynCall("vii", "callback") }}}(Utils.allocateString(JSON.stringify(tournament)), 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(JSON.stringify(error)));
            });
    },

    Wortal_tournament_shareAsync: function (payload, callback) {
        window.Wortal.tournament.shareAsync(Utils.toObjectFromJsonString(payload))
            .then(() => {
                {{{ makeDynCall("vii", "callback") }}}(1, 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(JSON.stringify(error)));
            });
    },

    Wortal_tournament_joinAsync: function (tournamentID, callback) {
        window.Wortal.tournament.joinAsync(UTF8ToString(tournamentID))
            .then(() => {
                {{{ makeDynCall("vii", "callback") }}}(1, 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(JSON.stringify(error)));
            });
    }

}

mergeInto(LibraryManager.library, WortalTournament);
