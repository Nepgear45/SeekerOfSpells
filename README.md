
--- Controls ---------------------------------------------------



--- Patch notes ------------------------------------------------
--- V0.09 ---

- Added HUD
- Added Health and Mana bars
	Both bars adjust to the max amount they have dynamically and can be changed in game
- Added item slots prototype
	Needs to be applied to all slots, so far works flawlessly with first (might need to check for reference compatibility)

--- V0.10 ---

- Added primitve AI for testing
- Added AI animations

--- V0.11 ---

- Added AI Behavioral tree
- Added AI that chances the player and can lose sight of the player
- Fixed an issue with AI Forever following the player
- Fixed an issue where AI would snap into postion if the angle of turning would be too great

--- V0.12 ---

- Added EnemyDamage
- Added EnemyAttack Animations
- Fixed a lot of bugs with enemy animations (dont ask)
- Added Immunity frames to Player

--- V0.13 ---

- Reworked Animation handling
- Fixed all bugs with animation looping
- Fixed error upon quitting the game where weapon would not be found by Blueprints
- Moved CanDamage variable to parent class of BP_Sword for more optimal fetching through different Blueprints

Known issues:
- Enemy AI still moves while attacking but the animation indicates they are standing still, this is not an animation bug it is simply a fault in AI Programming (so me my fault)

--- V0.14 ---

- Fixed a bug where AI player detection would collide with projectiles
- Fixed a bug where AI would lose the player if the player looped around the AI before it fully turned around
- Fixed a bug where AI would regain SeePlayer status immidiately after losing sight of player making it infinitely follow the player
- Fixed a bug where AI would move during standing animations
- All projectiles now use native collision projectile object type

--- V0.15 ---

- Fixed a bug where sword would only hit player arms not their hitbox
- Fixed sliding bug during attack animation
- Reworked Enemy to inherit from a c++ class for easier damage casting
- Fixed some animation glitches
- Added death animation to EnemyChaseAI
- Added death condition to EnemyChaseAI
- Added GameModeBase and inheritance of gamemode for main gameplay
- Added EnemyList in game mode for future saving

Known bugs:
- The sword from EnemyChaseAI does not have physics after detaching from it

--- V0.16 ---

- Added bases for EnemyCaster and their AI

--- V0.17 ---

- Fixed AI not stoppint when needed
- Changed some hardcoded values to be more accessible in blueprint
- Fixed EnemyCaster collisions
- Fixed EnemyCaster Rotating uncontrolabely when chasing player
- Fixed EnemyCaster not finding player
- Fixed EnemyCasterAI Chasing Player forever instead of stopping for distance
- Fixed EnemyChase and EnemyCaster softlocking themselves when colliding
- Fixed EnemyCaster Staff animation and effect
- Fixed EnemyCaster casting in sync with animation
- Fixed BlendSpace animation inconsistencies

Known occurances (not issues this time)
- EnemyCasterAI will stop casting spells if player is not in direct line of sight, they will however not move until player outside of attack radius. This for now is intentional behaviour as simpling navigating around the obsticale will make it too predictable for the player
- EnemyCaster can hit other enemy actors, this is intended

Known issues
- Projectile taging is not ideal and is hard sometimes to distinguish between hitable and non hitable hitboxes, the handler for that should get reworked however it does not cause any issues (for now)
- Tags do not get properly applied in C++ and have to be manually applied in Blueprints (No fix sofar)

--- V0.18 ---

- Added Pause menu
- Added Breakable walls (Explosion)
- Added Spikes

Known issues
- Enhanced input IA_PauseGame doesnt work when game is paused even though it has Trigger when paused flag enabled

--- V0.19 ---
- Updated gitignore to ignore asset folders
- Added UI inventory indicator for item slot selected
- Added transparent background to item images
- Added Dungeon assets
- Fixed an issue where Fireball spell wouldn't spawn explosion upon colliding with unreakable walls
- Added light and asset showcase in Debug room

--- V0.20 ---
- Added lighting to Fireball
- Added lighting to Fireball expolsion
- Added lighting to BasicAttackSpell
- Added lighting to DispellMagic
- Fixed all hitboxes problems todo with spells and their after effects
- Reworked Explosion zone overlap detection

Knonw bugs
- When expolsion light is spawned next to some (minority) cascade light sources, it causes these sources to produce artefacts briefly
- Variable transform is bugged in UE5.3.2

--- V0.20.1 ---
- Changed core funtionality of unreal engine 5.3.2 to support gravity componenet for fractured objects
- Added physics component to fractured objects
- Added fake floor

Knonw bugs
- Physics for fractured components doesnt work properly in UE5.3.2

--- V0.21 ---
- Fixed collision on trigger of FakeFloor trap
- Added corridor mapping
- Added Starting room sequence
- Added Random Room generation basics

--- V0.22 ---
- Added corridor mapping and cleanup
- Added ability to start new game from menu(temporary, needs touchup)
- Added FPS counter
- Added Torch base for character (needs model of the actual torch and something to toggle it)
- Added benchmark for lighting and assets
- Added ability to launch benchamrk level

Known bugs
- Casting certain values directly to C++ class of game mode base can cause unreal to not package and never load upon reloading the project.
There is no obvious error as the project is stuck loading whitout freezing or showing signs of malfuntioning.

--- V0.23 ---
- Fixed projectiles ignoring component tags
- Added a fully working settings menu
- Added Settings saving
- Added hardware settings optimization
- Added default settings
- Added display options: Window mode, Display Resolution, Framerate
- Added graphical options: View Distance, Post Processing, Anti Aliasing, Texture Quality, Shadow Quality

#######################################################################################################################

--- Currently known bugs in UE5.3.2 ---
- When expolsion light is spawned next to some (minority) cascade light sources, it causes these sources to produce artefacts briefly
- Variable transform is bugged in UE5.3.2
- Enhanced input IA_PauseGame doesnt work when game is paused even though it has Trigger when paused flag enabled
- Tags do not get properly applied in C++ and have to be manually applied in Blueprints (No fix sofar)
- Casting certain values directly to C++ class of game mode base can cause unreal to not package and never load upon reloading the project.
There is no obvious error as the project is stuck loading whitout freezing or showing signs of malfuntioning.

--- Engine notes ---
UE5.3.2 had some features missing/not enabled and it had to be edited manually in source code. 
The project might have trouble running outside of patched engine.
This has no effect on packaged projects.
