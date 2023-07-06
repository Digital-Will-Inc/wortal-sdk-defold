var WortalAnalytics = {

    Wortal_analytics_logLevelStart: function (level) {
        window.Wortal.analytics.logLevelStart(UTF8ToString(level));
    },

    Wortal_analytics_logLevelEnd: function (level, score, wasCompleted) {
        const completed = wasCompleted > 0;
        window.Wortal.analytics.logLevelEnd(UTF8ToString(level), UTF8ToString(score), completed);
    },

    Wortal_analytics_logLevelUp: function (level) {
        window.Wortal.analytics.logLevelUp(UTF8ToString(level));
    },

    Wortal_analytics_logScore: function (score) {
        window.Wortal.analytics.logScore(UTF8ToString(score));
    },

    Wortal_analytics_logTutorialStart: function (tutorial) {
        window.Wortal.analytics.logTutorialStart(UTF8ToString(tutorial));
    },

    Wortal_analytics_logTutorialEnd: function (tutorial, wasCompleted) {
        const completed = wasCompleted > 0;
        window.Wortal.analytics.logTutorialEnd(UTF8ToString(tutorial), completed);
    },

    Wortal_analytics_logGameChoice: function (decision, choice) {
        window.Wortal.analytics.logGameChoice(UTF8ToString(decision), UTF8ToString(choice))
    },

    Wortal_analytics_logSocialInvite: function (placement) {
        window.Wortal.analytics.logSocialInvite(UTF8ToString(placement));
    },

    Wortal_analytics_logSocialShare: function (placement) {
        window.Wortal.analytics.logSocialShare(UTF8ToString(placement));
    },

    Wortal_analytics_logPurchase: function (productID, details) {
        window.Wortal.analytics.logPurchase(UTF8ToString(productID), UTF8ToString(details));
    },

    Wortal_analytics_logPurchaseSubscription: function (productID, details) {
        window.Wortal.analytics.logPurchaseSubscription(UTF8ToString(productID), UTF8ToString(details));
    },

}

mergeInto(LibraryManager.library, WortalAnalytics);
