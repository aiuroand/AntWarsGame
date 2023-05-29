# Ant Wars Game

There are several kinds of anthills in this game.
- `Green` - are yours
- `White` - are neutral
- `Others` - are your enemies
  - `Red`  
  - `Magenta`
  - `Blue` 

You can control the game using keybord and mouse.

- Use `KEY_UP, KEY_DOWN and KEY_ENTER` to interact with menu

- In game you can use `Left Mouse Button`. Firstly choose your
  `Green` anthill and secondly choose any enemy or neutral anhthill.

- When you have to choose a talent you can click `Left Mouse Button` on 
  `Select` button under the talent you want.

During the game you can always leave using 
- `q` if you dont want to save the game
- `s` if you want to save the game and continue it in future

You can always try to create your own map using this instruction.
- On first two position write an integer that represents height of an anhtill in `00` format.
- Then write a space.
- On second two position write an integer that represents width of an anhtill in `00` format.
- Then write a space.
- On third two positions write an integer that represents difference between a round you
  want to set and first round in `00` format ( ex. If you want to start from tound 5 write there `04`). 
- Then write a space.
- Now you can create a map where 
  - Borders are `'#'`.
  - Free spaces are filled with  `Space`.
  - Anthils are a 3x5 box where.
    - In posiition (1.1) you should write an `owner's color`.
    - In posiitions (1.2) and (1.3) you should integer in `00` format, that represents starting amount
      of ants in this anthill.
    - In the middle of the left wall you should write `unique id` for an anthill. 
    - In the middle of the bottom wall you should write an integer in  `000` format
      Talent tree in my game may be unequivocally represented using a single number from 0 to 63,
      where talents are
      - `1` - More ants per attack.
      - `2` - More armor per anthill.
      - `4` - More ants per move.
      - `8` - More ant allowed in anthills.
      - `16` - Owner randomly conquers neutral ( white ) anthill by some chance.
      - `32` - Amount of ants in random owner's anthill increases to MAX number by some chance .
    - And their sum represetns my talent tree.

Gool Luck and Have fun!
