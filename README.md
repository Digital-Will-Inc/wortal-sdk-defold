# Wortal SDK for Defold

## Installation

Add [Wortal SDK](https://github.com/Digital-Will-Inc/wortal-sdk-defold/archive/master.zip) as a [Defold library dependency](http://www.defold.com/manuals/libraries/)

## How to Use

### Ads

[API Reference](https://docs.games-api.ai/api/ads/)

Interstitial ads can be shown at various points in the game such as a level end, restart or a timed
interval in games with longer levels.

```lua
-- Player reached the next level.
wortal.ads_show_interstitial("next", "NextLevel", pause_game, resume_game)

-- Player paused the game.
wortal.ads_show_interstitial("pause", "PausedGame", pause_game, resume_game)

-- Player opened the IAP shop.
wortal.ads_show_interstitial("browse", "BrowseShop", pause_audio, resume_audio)
```

Rewarded ads can be shown too. These are longer, optional ads that the player can earn a reward for watching. The player
must be notified of the ad and give permission to show before it can be shown.

```lua
-- This example shows the game flow independent of the outcome of the ad.
-- Ex: Player gets bonus coins for watching the ad, but the game continues regardless of the outcome.
wortal.ads_show_rewarded("BonusCoins", pause_game, resume_game, skip_bonus, add_bonus_coins)

-- This example shows the game flow depending on the outcome of the ad.
-- Ex: Player dies and can revive by watching an ad, but if they skip the ad they lose the level.
wortal.ads_show_rewarded("ReviveAndContinue", pause_audio, resume_audio, end_game, continue_game)
```

**NOTE**: Players should only be rewarded in the `adViewed` callback.

### Analytics

[API Reference](https://docs.games-api.ai/api/analytics/)

The Analytics API can be used to track game events that can help better understand how players are interacting with
the game. This data will be available for viewing in the Wortal dashboard.

```lua
-- Logs the start of the level.
wortal.analytics_log_level_start("Level 3")

-- Logs the end of the level. Will track the time spent playing the level if the name matches
-- the name of the last logLevelStart() call.
wortal.analytics_log_level_end("Level 3", "100", 1)

-- Logs a choice the player made in the game. This can be useful for balancing the game
-- and seeing what content your players interact with the most.
wortal.analytics_log_game_choice("Character", "Blue")
```

### Achievements

[API Reference](https://docs.games-api.ai/api/achievements/)

The Achievements API is used to track the player's progress in the game. Achievements can be unlocked by completing
specific tasks or reaching certain milestones.

```lua
-- Unlock an achievement.
wortal.achievements_unlock_achievement("achievement-123", function(self, success, error)
    popup.success_check(success, "Success!", "Error")
end)

-- Get a list of the player's achievements.
wortal.achievements_get_achievements(function(self, achievements, error)
    popup.success_check(achievements, prettify(json.decode(achievements)), "Error")
end)
```

### Context

[API Reference](https://docs.games-api.ai/api/context/)

The Context API is used to connect players and allow them to interact in the game session, share their content
and send messages to each other.

```lua
-- Invite a friend to play the game.
local payload = {
    image = 'data:base64image',
    text = 'Invite text',
    cta = 'Play',
    data = { exampleData: 'yourData' },
}

wortal.context_invite(json.encode(payload), function(self, success, error)
    popup.success_check(success, "Success!", "Error")
end)

-- Share your game activity with friends.
local payload = {
    image = 'data:base64image',
    text = 'Share text',
    cta = 'Play',
    data = { exampleData: 'yourData' },
}

wortal.context_share(json.encode(payload), function(self, shareResult, error)
    popup.success_check(shareResult, shareResult, "Error")
end)
```

### In-App Purchases

[API Reference](https://docs.games-api.ai/api/iap/)

The In-App Purchases (IAP) API is used to provide an interface for in-game transactions on the platforms.
This process will differ based on what platform the game is being played on, but the API remains the same.

```lua
-- Get the catalog of products the player can purchase.
wortal.iap_get_catalog(function(self, catalog, error)
    popup.success_check(catalog, prettify(json.decode(catalog)), "Catalog failed")
end)

-- Purchase a product.
local purchaseConfig = {
    productID = "my.product.id"
}

wortal.iap_make_purchase(json.encode(purchaseConfig), function(self, purchase, error)
    popup.success_check(purchase, prettify(json.decode(purchase)), "Purchase failed")
end)
```

### Leaderboards

[API Reference](https://docs.games-api.ai/api/leaderboard/)

The Leaderboard API gives the game access to the platform's leaderboard functionality. This is where
you can track player's scores and compare them to other players.

```lua
-- Get the top 10 entries on the global leaderboard.
wortal.leaderboard_get_entries("global", 10, 0, function(self, entries, error)
    popup.success_check(entries, prettify(json.decode(entries)), "Leaderboard get entries failed")
end)

-- Add the player's score to the leaderboard.
wortal.leaderboard_send_entry("global", 250, "details", function(self, entry, error)
    popup.success_check(entry, prettify(json.decode(entry)), "Leaderboard add failed")
end)
```

### Notifications

[API Reference](https://docs.games-api.ai/api/notifications/)

The Notifications API is used to send notifications to the player. These can be used to notify the player
of an event in the game or to remind them to come back and play.

```lua
-- Schedule a notification to send to the player.
local payload = {
    title = "Your energy is full!",
    body = "Come back and play again.",
    mediaURL: "https://example.com/image.png",
    label: "resources-full",
    scheduleInterval: 300
}

wortal.notifications_schedule(json.encode(payload), function(self, result, error)
    popup.success_check(result, prettify(json.decode(result)), "Notification schedule failed")
end)

-- Cancel a scheduled notification.
wortal.notifications_cancel("notification-123", function(self, success, error)
    print(success)
end)
```

### Player

[API Reference](https://docs.games-api.ai/api/player/)

You can find details about the current player via the Player API.

```lua
-- Get the player's name.
local name = wortal.player_get_name()

-- Get a list of the player's friends who have also played this game.
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

[API Reference](https://docs.games-api.ai/api/session/)

Details about the current session can be accessed in the Session API.

```lua
-- Get the entry point of where the game started from.
wortal.session_get_entry_point(function(self, entryPoint, error)
    popup.success_check(entryPoint, entryPoint, "Error")
end)
```

### Stats

[API Reference](https://docs.games-api.ai/api/stats/)

The Stats API is used to track player statistics in the game.

```lua
-- Track the player's progress in the game.
wortal.stats_post_stats("level 1", 3, function(self, success, error)
    popup.success_check(success, "Success!", "Error")
end)

-- Get the player's stats.
wortal.stats_get_stats("level 1", function(self, stats, error)
    popup.success_check(stats, prettify(json.decode(stats)), "Error")
end)
```

### Tournament

[API Reference](https://docs.games-api.ai/api/tournament/)

The Tournament API is used to create and manage tournaments for your game.

```lua
// Create a tournament.
local payload = {
    initialScore: 100,
    config: {
        title: "Level 1 Tournament",
    },
    data: {
        level: 1,
    },
};

wortal.tournament_create(json.encode(payload)), function(self, tournament, error)
    popup.success_check(tournament, prettify(json.decode(tournament)), "Error")
end)

// Post a score to a tournament.
wortal.tournament_post_score(200), function(self, success, error)
    popup.success_check(success, "Success!", "Error")
end)
```
