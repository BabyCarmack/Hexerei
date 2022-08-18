#Hexerei Engine

<p align="center">
  <img source="HexereiPrototype.png"
</p>

## 3D Linux-based Libre Game Engine

Hexerei is a work-in-progress traditional-style 3D game engine written in C.
It derives its name from the German word for "witchcraft", both a premonition of
its impending magic and a nod to the demoscene group that it is heavily inspired from,
the famous [Farbrausch](https://www.pouet.net/groups.php?which=322).
It retains a Free Software license; Richard Stallman would approve.
It currently supports 9 textures and 99 objects in any scene, but no physics (yet).
To modify a .scen file, ensure the number of characters in an object position and scale remains
exactly eight, or the parser will go bananas. I will write a more comprehensive documentation later.

## Building

### Linux

Building on Linux should be straightforward. Simply run "sh rerun.sh" in a terminal,
and the script will clean up any binaries, compile the engine, and run it.
If you simply want to build Hexerei, you can also just run "make".

### Windows

I do not have Windows so I cannot test its functionality, but theoretically you
should be able to use MinGW to compile with Make. You could also possibly compile
main.c and glad/glad.c manually, though you will need to link everything yourself.
I can't guarantee it will work with a non-GNU compiler, as I have only been using
gcc to compile code.

### OSX

There is no support for the OSX platform at this time. Building it is possible but
I do not know how.

## License

It is licensed under the permissive 3-clause [BSD License](https://opensource.org/licenses/BSD-3-Clause),
which grants total control of this program to you, as it should, so long as redistributions of unmodified Hexerei code,
in any form,
retain the license in addition to the engine itself. It also prohibits my name in use of promotion of other products
without my permission.
