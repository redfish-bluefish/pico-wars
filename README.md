# Pico Wars
A clone of Advance Wars that runs entirely in the terminal with p2p networking for multiplayer. Made with C and ncurses.

## Roadmap
- ~~Board rendering and camera selection/movement~~
- ~~Support for resizing the terminal mid-game~~
- Unit rendering and selection/movement
- Unit attacking and capturing logic
- Game day turn logic and player state
- Win state logic
- Game state serialization 
- Networking module to allow p2p play given specific address and port
- Expand networking module to allow search on LAN
- Menus on game start and to serach for games
- Game event log
- Custom map support
- Custom graphical support (extended graphics module?)
- ???

## Third-Party Dependencies

- log.c by rxi (https://github.com/rxi/log.c)
- uthash/utlist by Troy D. Hanson (https://github.com/troydhanson/uthash)