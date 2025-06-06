--- Requirements -----------------------------------------------

Minimum Requirements (1080p 30FPS):
CPU: i7 3770 or equivalent
GPU: GTX 960 2GB or equivalent
RAM: 8GB DDR3
Storage: 3GB hard drive

Recommended Requirements (1080p 60FPS):
CPU: i5 10400f or equivalent
GPU: RTX 3060 6GB or equivalent (8GB VRAM for ultra settings)
RAM: 12GB DDR4
Storage: 3GB hard drive

--- Controls ---------------------------------------------------

Movement: W, A, S, D
Jump: Space Bar
Dash: Shift
Use Item in slot: Left Mouse Button
Change Item in inventory: C for left, V for right
Pick up Item: E
Drop Item in selected inventor slot: G
Pause Game: P

--- Spell Tier -------------------------------------------------

- Basic Spell = 1 secound cooldown
BasicAttack
LightBall
StoneCannon

- Medium Spell = 2.5 secound cooldown
FireBall

- Powerfull Spell = 10 secound cooldown
Dispel
Barrier

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

--- V0.24 ---
- Switched Anti aliasing to TSR mode for better image quality
- Improved lighting effects
- Reworked spawn area
- Added dynamic mesh mapping
- Added closable door
- Fixed BP_EnemyChase corruption caused by unreal crash
- Added RoomEventHanlder
- Added area detection for rooms

--- V0.24.1 ---
- Added functional Triggers to rooms
- Added conditional door opening and closing
- Added Enemy death in room detection

Known issues:
AI character mesh extends outside the capsule hitbox preventing successful hits during animation under certain angles

--- V0.25 ---
- Added main menu panorama scene
- Impoved door fetching and interactions system
- Added Gate (another door)
- Improved navmesh connection between AI when spawning from elevation

--- V0.25.1 ---
- Rotation on objects based on event tick is tied to FPS (Timers will be more effective than event tick)
- Added Key locked door
- Added Key item
- Added support for multiple Key items
- Added Key item indicator in hud
- Added Indicator for items in range
- Fixed Indicator not being accurate when many items are in range
- Improved performance for lighting effects with multiple sources of light in one place

--- V0.25.5 ---
- Added LightBall spell
- Added dimming effect to LightBall
- Added LightBall spell pickup
- Added LightBall spell icon to HUD
- Fixed Projectiles ignoring static meshes in certain scenarios
- Reworked the way assets are rendered and grouped
- Decreased amount of detail in some meshes for optimization
- Added Sound settings
- Added Master, BGM, SFX, UI Volumes and their respective sldiers
- Added custom variable Saving
- Added creation of default settings if no user settings are found
- Added Background music to MainMenu

Notes:
SFX and UI sounds are not in use due to lack of sounds (Still being applied and saved)

--- V0.25.6 ---
- Fixed an issue where background music would freeze during detection of optimal settings
- Added new model for enemies
- Added Sound attenuation
- Added Stepping sounds
- Added Sword hit and swoosh sounds
- Added Sound Cue
- Added random footstep noise on movement animations
- Added Dynamic footsteps and footstep mapping
- Fixed a bug where torches would ignore SFX setting
- Fixed corruption problems with Game mode being overriden by C++ class

Known Bugs:
Overriding game mode with a c++ class will corrput it and will brick the project

--- V0.25.7 ---
- Fixed a bug where sword hit sound would play when character overlapped with the sword even if the AI character was dead
- Fix Torch sounds ignoring master volume
- Explosion can now trigger fake floor
- Casting sound effect no longer plays when the spell isnt cast due to lack of mana
- Adjusted room alignment
- Reworked BasicAttackSpell visuals and hitboxes
- Added projectile flying sound to BasicAttackSpell
- Adjusted sound attenuation for all spells and their after effects
- Added Delay timer indicator in HUD
- Added 3 types of spell tags (refer to README in section Spell tier)
- Fixed collision bug with IronDoorKey item
- Fixed collision with FireBalls and turret casting it

Notes:
- Timers are mismatched by milisecounds (not noticable without debug)
- HUD time effect is slight off the items

--- V0.25.8 RETRACTED---
THIS PATCH HAS BEEN RETRACTED DUE TO POOR CODE QUALITY AND BUGS RESULTING FROM OMITTED CODE
RETRACTION HAPPENED BEFORE COMMIT WAS PUSHED TO GITHUB

--- V0.25.9 ---
- BGM now pauses when muted instead of dissapearing in main menu
- Reworked the way default values are saved in FirstPersonCharacter
- Added saving for all game objects
- Fixed RoomEvents dont keep cleared status after secound save
- Fixed 13 saving inconsistency issues

Notes:
The patch V0.25.8 is missing as it has been retracted due to poor code quality

UNIT TEST RESULTS | Patch V0.25.9
Saving test:
- Ground items consistency during reloads PASSED
- Ground items consistency when overwriting save files PASSED
- Iron door key consistency during reloads FAILED (Spawning problem when game loaded from save)
- Iron door key consistency when overwriting save files OMITTED (Previous test failed)
- Threat detection during saving PASSED
- Room status consistency during reloads PASSED
- Room status consistency when overwriting save files PASSED
- Stand alone door consistency during reloads PASSED
- Stand alone door consistency when overwriting save files FAILED (Door doesnt keep status over multiple saves)
- Player Statistics consistency during reloads PASSED
- Player Statistics consistency when overwriting save files PASSED
- Player States consistency during reloads PASSED
- Player States consistency when overwriting save files PASSED

Data test:
- Data loading during different states PASSED
- Data loading after restart of the game PASSED
- Lossless position saving PASSED
- Consistency when loading PASSED
- Overwriting and loading the same file to check for read/write errors PASSED

--- V0.25.9 ---
- Fixed spell collision on 2 spells colliding
- Fixed slot five timer not showing up
- Fixed pickup indicator displaying incorrectly when player loads a save spawning next to a pickup
- Added validation methods to prevent crashes upon loading saves that corrupt/dont contain any data
- Removed mist effect from staff particles
- Fixed EnemyChase attack hitbox having incorrect tags causing them to not take damage from certain spells
- Chaged Sword weapon collider into a trigger rather than overlapp all dynamic for optimization
- Added eye glowing effect to enemies
- Fixed EnemyChase not attacking if the player stays in attack hitbox (now attacks will loop as long as the player is in range)
- Added Confirmations to saving in PauseSaveGameMenu

--- V0.26.0 ---
- Added UI Assets
- Updated visuals for mana bar and health bar
- Fixed spell timer allignment
- Updated visuals for Inventory slots and Invenotry indicator
- Redesigned invenotry layout order
- Updated allignment to support 16:9 aspect ratio in HUD
- Added more settings to settings menu
- Set minimum MouseSensitivity value to 0.1 so that the player cannot soft lock themselves
- Moved preloading of PauseSettingsMenu to when the player pauses the game for reduction of microlags during loading of levels
- Fixed BGM Destruction when 0 volume is set
- Added update for all static torch sounds in the game
- Added settings menu in pause
- Fixed volumes losing references on frequent reloading of the game
- Added Save file deletion
- Added confirmation for overwriting save files, deleting save files and trying to load none existent save files
- Fixed enemy caster AI losing their eyes
- Added death condition to the game
- Added Spectator mode after death
- Added menus for death and spectator mode
- Fixed enemy AI attacking player that doesn't exist after death

--- V0.26.1 ---
- Added realisitc character camera
- Added Camera shake toggle in settings menus
- Reworked Destructable walls into Fake walls
- Reworked spikes to kill instead of dealing damage (they will be placed with that in mind)
- Added Debug Specific Game Mode
- Changed the ability to save the game in Debug room to false
- Removed Benchmark map from the game and menus
- Rearanged Debug room to showcase features

--- V0.26.2 ---
- Replaced BGMs with non commercial ones
- Added death BGM sequence
- Reworked the shape of Turrets
- Changed ragdoll and decal funtionality of fake floor
- Removed mist from pickups
- Added loading (primitive, its time based)
- Fixed a bug where directional light would not dispawn when loading from a save file that starts after starting sequence
- Added more items to pick up
- Added new section to the map
- Added secret room in the new location
- Fixed an issue where key wouldn't spawn after reloading a save
- Fixed an issue where overriding the save file would reset iron door open status
- EnemyCaster Staff no longer shines when EnemyCaster is dead
- Fixed an issue where the player could interact with the game while the game was loading
- Fixed an issue where when first loading into the game the incorrect resolution and window mode was selected/applied
- Fixed an issue where when first loading into the game the buttons for window mode and resolution where not correctly highlighted
- Added Borderless window option in settings menu
- Changed the name of BGM Volume to Background Musci Volume in settings
- Updated Pause settings menu accordingly

--- V0.27.0 ---
- Added sprites for UI buttons
- Adjusted Basic attack magic balancing
- Adjusted Explosion radius and duration from Fireball spell
- Fixed fireball turret immunity to dispell magic
- Adjusted the location of disable particles on turrets
- Added UI sounds
- Removed some fake floors for optimization
- Fixed a bug where unbreakable wall had no collision for player
- Added new area and secrets to the map
- Added another room event in the new area
- Added Game finish sequence

--- V0.27.1 ---
- Fixed Big room cliping with starting split
- Added HUD off option for cinematic screenshots
- Added Keybind menu

--- V0.27.2 ---
- Fixed explosion radius staying too long
- Renamed Keybing settings to keybinds
- Added crosshair to HUD
- Added crosshair toggle
- Fixed RoomEvents not spawning under certain circumstances when loading

#######################################################################################################################

--- Currently known bugs in UE5.3.2 ---
- When expolsion light is spawned next to some (minority) cascade light sources, it causes these sources to produce artefacts briefly
- Variable transform is bugged in UE5.3.2
- Enhanced input IA_PauseGame doesnt work when game is paused even though it has Trigger when paused flag enabled
- Tags do not get properly applied in C++ and have to be manually applied in Blueprints (No fix sofar)
- Casting certain values directly to C++ class of game mode base can cause unreal to not package and never load upon reloading the project.
There is no obvious error as the project is stuck loading whitout freezing or showing signs of malfuntioning.
- Overriding game mode with a c++ class will corrput it and will brick the project

--- Engine notes ---
UE5.3.2 had some features missing/not enabled and it had to be edited manually in source code. 
The project might have trouble running outside of patched engine.
This has no effect on packaged projects.
