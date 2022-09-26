var gameData = {
    platform: window.getWortalPlatform(),
    browser: navigator.userAgent,
    gameName: document.title,
    country: "",
    linkInterstitialId: "",
    linkRewardedId: "",
    gameTimer: 0,
    levelName: "",
    levelTimer: 0,
    levelTimerHandle: 0,
};

console.log('[Wortal] Platform: ' + gameData.platform);
window.addEventListener("load", () => {
    window.initWortal(function () {
        console.log("[Wortal] Initializing..");
        if (gameData.platform === 'link' || gameData.platform === 'viber') {
            document.getElementById("loading-cover").style.display = "none";
            if (window.wortalGame) {
                window.wortalGame.initializeAsync().then(() => {
                    Progress.addListener(val => wortalGame.setLoadingProgress(val));
                    window.wortalGame.startGameAsync();
                    _getLinkAdUnitIds();
                });
            }
        } else {
            window.triggerWortalAd("preroll", "", "Preroll", {
                adBreakDone: function () {
                    console.log("[Wortal] AdBreakDone");
                    document.getElementById("loading-cover").style.display = "none";
                },
                noShow: function () {
                    console.log("[Wortal] NoShow");
                    document.getElementById("loading-cover").style.display = "none";
                }
            });
        }
    });

    window.addEventListener('visibilitychange', () => {
        if (document.visibilityState === "hidden") {
            _logGameEnd();
        }
    });

    _getIntlData()
        .then(data => gameData.country = data)
        .catch(() => gameData.country = "Nulltherlands");

    _logGameStart();
    console.log("[Wortal] Initialized");
});

function _getIntlData() {
    return fetch('./intl-data.json')
        .then(response => response.json())
        .then(data => _getPlayerCountry(data))
        .catch(error => console.log(error));
}

// This uses the time zone setting of the player to determine their country.
// We do this to avoid collecting any personal data on the player for GDPR compliance.
// The location is very coarse and easily spoofed so nothing here can identify the player.
function _getPlayerCountry(data) {
    if (data == null) {
        return "Nulltherlands";
    }
    const zone = Intl.DateTimeFormat().resolvedOptions().timeZone;
    const arr = zone.split("/");
    const city = arr[arr.length - 1];
    return data[city];
}

function _getLinkAdUnitIds() {
    wortalGame.getAdUnitsAsync().then((adUnits) => {
        console.log('[Wortal] Link AdUnit IDs returned: \n' + adUnits);
        gameData.linkInterstitialId = adUnits[0].id;
        gameData.linkRewardedId = adUnits[1].id;
    });
}

function _logGameStart() {
    _logEvent("GameStart", {
        game: gameData.gameName,
        platform: gameData.platform,
        browser: gameData.browser,
        country: gameData.country,
    });
    setInterval(function () {
        if (document.visibilityState !== "hidden") {
            gameData.gameTimer += 1;
        }
    }, 1000);
}

function _logGameEnd() {
    _logEvent("GameEnd", {
        game: gameData.gameName,
        timePlayed: gameData.gameTimer,
    });
}

function _logEvent(name, features) {
    let request = new XMLHttpRequest();
    request.open("POST", "https://wombat.digitalwill.co.jp/wortal/events");
    request.setRequestHeader("Content-Type", "application/json");
    request.send(JSON.stringify({ name, features }));
}
