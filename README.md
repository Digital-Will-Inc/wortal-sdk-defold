# Wortal SDK for Defold

## Installation

Add [Wortal SDK](https://github.com/Digital-Will-Inc/wortal-sdk-defold/archive/master.zip) as a [Defold library dependency](http://www.defold.com/manuals/libraries/)

## How to Use

### Ads

[API Reference](https://sdk.html5gameportal.com/api/ads/)

Interstitial ads can be shown at various points in the game such as a level end, restart or a timed
interval in games with longer levels.

```typescript
// Player reached the next level.
wortal.ads_show_interstitial("next", "NextLevel", pause_game, resume_game)

// Player paused the game.
wortal.ads_show_interstitial("pause", "PausedGame", pause_game, resume_game)

// Player opened the IAP shop.
wortal.ads_show_interstitial("browse", "BrowseShop", pause_audio, resume_audio)
```

Rewarded ads can be shown too. These are longer, optional ads that the player can earn a reward for watching. The player
must be notified of the ad and give permission to show before it can be shown.

```typescript
// This example shows the game flow independent of the outcome of the ad.
wortal.ads_show_rewarded("BonusCoins", pause_game, resume_game, skip_bonus, add_bonus_coins)

// This example shows the game flow depending on the outcome of the ad.
wortal.ads_show_rewarded("ReviveAndContinue", pause_audio, resume_audio, end_game, continue_game)
```

**NOTE**: Players should only be rewarded in the `adViewed` callback.

### Analytics

[API Reference](https://sdk.html5gameportal.com/api/analytics/)

The Analytics API can be used to track game events that can help better understand how players are interacting with
the game. This data will be available for viewing in the Wortal dashboard.

```typescript
// Logs the start of the level.
wortal.analytics_log_level_start("Level 3")

// Logs the end of the level. Will track the time spent playing the level if the name matches
// the name of the last logLevelStart() call.
wortal.analytics_log_level_end("Level 3", "100", 1)

// Logs a choice the player made in the game. This can be useful for balancing the game
// and seeing what content your players interact with the most.
wortal.analytics_log_game_choice("Character", "Blue")
```

### Context

[API Reference](https://sdk.html5gameportal.com/api/context/)

The Context API is used to connect players and allow them to interact in the game session, share their content
and send messages to each other.

```typescript
// Invite a friend to play the game.
local payload = {
    image = 'data:base64image',
    text = 'Invite text',
    caption = 'Play',
    data = { exampleData: 'yourData' },
}

wortal.context_choose(json.encode(payload), function(self, success, error)
    popup.success_check(success, "Success!", "Error")
end)

// Share your game activity with friends.
local payload = {
    image = 'data:base64image',
    text = 'Share text',
    caption = 'Play',
    data = { exampleData: 'yourData' },
}

wortal.context_share(json.encode(payload), function(self, shareResult, error)
    popup.success_check(shareResult, shareResult, "Error")
end)
```

### In-App Purchases

[API Reference](https://sdk.html5gameportal.com/api/iap/)

The In-App Purchases (IAP) API is used to provide an interface for in-game transactions on the platforms.
This process will differ based on what platform the game is being played on, but the API remains the same.

```typescript
// Get the catalog of products the player can purchase.
wortal.iap_get_catalog(function(self, catalog, error)
    popup.success_check(catalog, prettify(json.decode(catalog)), "Catalog failed")
end)

// Purchase a product.
local purchaseConfig = {
    productID = "my.product.id"
}

wortal.iap_make_purchase(json.encode(purchaseConfig), function(self, purchase, error)
    popup.success_check(purchase, prettify(json.decode(purchase)), "Purchase failed")
end)
```

### Leaderboards

[API Reference](https://sdk.html5gameportal.com/api/leaderboard/)

The Leaderboard API gives the game access to the platform's leaderboard functionality. This is where
you can track player's scores and compare them to other players.

```typescript
// Get the top 10 entries on the global leaderboard.
wortal.leaderboard_get_entries("global", 10, 0, function(self, entries, error)
    popup.success_check(entries, prettify(json.decode(entries)), "Leaderboard get entries failed")
end)

// Add the player's score to the leaderboard.
wortal.leaderboard_send_entry("global", 250, "details", function(self, entry, error)
    popup.success_check(entry, prettify(json.decode(entry)), "Leaderboard add failed")
end)
```

### Player

[API Reference](https://sdk.html5gameportal.com/api/player/)

You can find details about the current player via the Player API.

```typescript
// Get the player's name.
local name = wortal.player_get_name()

// Get a list of the player's friends who have also played this game.
local payload = {
    filter = "ALL",
    size = 20,
    hoursSinceInvitation = 4,
}

wortal.player_get_connected_players(json.encode(payload), function(self, players, error)
    popup.success_check(players, prettify(json.decode(players)), "Error")
end)
```

### Session

[API Reference](https://sdk.html5gameportal.com/api/session/)

Details about the current session can be accessed in the Session API.

```typescript
// Get the entry point of where the game started from.
wortal.session_get_entry_point(function(self, entryPoint, error)
    popup.success_check(entryPoint, entryPoint, "Error")
end)
```
