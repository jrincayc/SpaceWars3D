SpaceWars3D was created by Joshua Cogliati and Michael Milvich.  

To run it the environmental variable SPACEWARS_RES needs to point to
the data directory.  That is something like:
export SPACEWARS_RES=$HOME/SpaceWars3D/src/data
needs to be run before running spacewars.

LICENSE:

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
   
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the
   distribution.

3. The name of the author may not be used to endorse or promote
   products derived from this software without specific prior written
   permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.


End License

NOTES

KEYS

<ESC> Exits the program
` toggles view
- decreases speed
= increases speed
g speedup
h slowdown
f up
d down
m right
b left
v roll 
z roll other direction
<up>,<down>,<left>,<right> pitch or yaw in that direction.
<space> launch bomb



COMMAND LINE

Screen size selection:

-1 
gives 640x480
-2 
gives 800x600
-3 
gives 1024x768

-m int
Chooses the map
-s int
chooses the ship
-f 
chooses fullscreen.

COMPILING

The program requires the xerces XML library, the GL, GLU and glut
libraries and the SDL library.  

Adjust the rules.make file if any compilation flags need to be changed. 

Run make in the src directory and if everything works it will create a
program app/spacewars3d

TODO

More than one players.

Configurable keyboard.

Network play. 

Computer players.

Better error detection in input files.

An attempt to separate this into servers and clients was done in the
client and server directories.  This was not finished.
