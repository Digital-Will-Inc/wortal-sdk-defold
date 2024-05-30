var WortalAchievements = {

    Wortal_achievements_getAchievementsAsync: function (callback) {
        window.Wortal.achievements.getAchievementsAsync()
            .then(achievements => {
                {{{ makeDynCall("vii", "callback") }}}(Utils.allocateString(JSON.stringify(achievements)), 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(JSON.stringify(error)));
            });
    },

    Wortal_achievements_unlockAchievementAsync: function (achievementId, callback) {
        window.Wortal.achievements.unlockAchievementAsync(achievementId)
            .then(() => {
                {{{ makeDynCall("vii", "callback") }}}(1, 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(JSON.stringify(error)));
            });
    }

}

addToLibrary(WortalAchievements);
