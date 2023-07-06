# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [2.3.0] - 2023-07-06
### Added
- Core
    - Added Notifications API
    - New APIs: getSupportedAPIs, performHapticFeedbackAsync
- Analytics
    - New events: logSocialInvite, logSocialShare, logPurchase, logPurchaseSubscription
- Context
    - New APIs: inviteAsync, shareLinkAsync, isSizeBetween

### Fixed
- Core
  - Exception when passing empty string to js libs

### Changed
- Core
    - Organized api, classes and typedefs

## [2.2.0] - 2023-04-26
### Added
- Ads on Viber
- Group chat context for FB Instant Games
- Game ID parsing for FB Instant Games
- Converter util for FB leaderboards
- Ads API: noFill callback for ad calls
- Context APIs: getType, getPlayersAsync, shareLinkAsync, isSizeBetween
- Player API: flushDataAsync, getASIDAsync, getSignedASIDAsync, canSubscribeBotAsync, subscribeBotAsync
- Session API: getPlatform

### Changed
- Context and Player APIs now have optional null return values to match platform SDKs
- Improved docs
- Improved error handling

## [2.1.0] - 2023-02-21
### Added
- Support for FB Instant Games
- onPause callback

### Fixed
- Possible type mismatch for ad unit IDs

## [2.0.0] - 2022-12-14
### Breaking Change
- API access is now by module (wortal.ads, wortal.analytics, etc.)

### Added
- Context API
- In-App Purchase API
- Leaderboard API
- Player API
- Session API
- Support for Game Distribution platform
- API use example collections

### Changed
- Extension now uses Wortal SDK Core

## [1.0.1] - 2022-10-04
### Added
- Support for ad blockers

### Fixed
- Possible error on Viber init

## [1.0.0] - 2022-09-29
### Added
- Initial version of the SDK
