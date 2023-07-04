var WortalIAP = {

    Wortal_iap_isEnabled: function () {
        return window.Wortal.iap.isEnabled() ? 1 : 0;
    },

    Wortal_iap_getCatalogAsync: function (callback) {
        window.Wortal.iap.getCatalogAsync()
            .then(catalog => {
                {{{ makeDynCall("vii", "callback") }}}(Utils.allocateString(JSON.stringify(catalog)), 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(error.code));
            });
    },

    Wortal_iap_getPurchasesAsync: function (callback) {
        window.Wortal.iap.getPurchasesAsync()
            .then(purchases => {
                {{{ makeDynCall("vii", "callback") }}}(Utils.allocateString(JSON.stringify(purchases)), 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(error.code));
            });
    },

    Wortal_iap_makePurchaseAsync: function (purchaseConfig, callback) {
        window.Wortal.iap.makePurchaseAsync(Utils.toObjectFromJsonString(purchaseConfig))
            .then(purchase => {
                {{{ makeDynCall("vii", "callback") }}}(Utils.allocateString(JSON.stringify(purchase)), 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(error.code));
            });
    },

    Wortal_iap_consumePurchaseAsync: function (token, callback) {
        window.Wortal.iap.consumePurchaseAsync(UTF8ToString(token))
            .then(() => {
                {{{ makeDynCall("vii", "callback") }}}(1, 0);
            })
            .catch(error => {
                {{{ makeDynCall("vii", "callback") }}}(0, Utils.allocateString(error.code));
            });
    }

}

mergeInto(LibraryManager.library, WortalIAP);
