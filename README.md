# TIQ-RPC

Recently, I've really enjoyed programming for The Impossible Quiz. So, I wanted to challenge myself, so I decided to implement Discord Rich Presence!

This program supports Flash Player 32, 32 SA, and 11 SA. It says what question you're on, elapsed time, and supports some customization, like how often it refreshes your status and whether or not it times out if it can't detect Flash Player.

## Setup

1. Download the ZIP file and extract it.
2. Open `config.toml`, and edit settings according to your needs.
3. Open Flash Player, then open the program.
4. Keep the program open, or your rich presence won't work.

## Other Stuff

Discord SDK version sourced from [here](https://github.com/a-day-old-bagel/discordCppSdk/tree/master), by [a-day-old-bagel](https://github.com/a-day-old-bagel), huge fucking thanks to them for making a version that actually works, unlike the normal SDK.

The Impossible Quiz headers sourced from [meee :3](https://github.com/saturnaliam/TIQ-Headers).

Used [toml++](https://marzer.github.io/tomlplusplus/) for the handling and parsing of `.toml` files.
