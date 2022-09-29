# Wortal SDK for Defold

## Installation
1. Add `wortal-sdk-defold.zip` as a [Defold library dependency](http://www.defoldcom/manuals/libraries/)
2. Bundle your game for HTML5 platform
3. Create `.zip` archive of the game with `index.html` at the root
4. Upload build to the Wortal dashboard

## How to Use

### Interstitial Ads
Interstitial ads are convenient to show to players at certain milestones throughout your game. Ex: Player finishes a level, player levels up, etc.

```html
wortal_sdk.show_interstitial(placementType, description, on_before_ad, on_after_ad)

local function on_before_ad(self)
-- Pause game
end

local function on_after_ad(self)
-- Resume game
end
```

### Rewarded Ads
Rewarded ads can be used to offer the player bonuses or other incentives during the game. These ads are longer and require the player to watch the ad in its entirety to receive the reward, but are optional.

```html
wortal_sdk.show_rewarded(description, on_before_ad, on_after_ad, on_skip_ad, on_reward_ad)

-- Pause and resume in on_before_ad and on_after_ad

local function on_reward_ad(self)
-- Reward the player
end

local function on_skip_ad(self)
-- Don't reward - player skipped ad
end
```

### Analytics
The analytics API can be used to track in game events to get a better understanding of how players are interacting with the game.

```html
-- Starts the level timer
wortal_sdk.log_level_start(level)

-- If level is the same as the previous log_level_start call, will track the time played in the level
wortal_sdk.log_level_end(level, score)

wortal_sdk.log_level_up(level)
wortal_sdk.log_score(score)

-- Logs the player's choice when offered different options.
-- This can be useful for determining which characters are more popular, or paths are more commonly taken, etc.
-- This can be a powerful tool for balancing the game and giving the players more of what they enjoy.
wortal_sdk.log_game_choice(decision, choice)
```
