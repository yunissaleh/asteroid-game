# asteroid-game
Asteroids Game is a simple game where the player controls a ship and must shoot asteroids to avoid collision while trying to pass to the next level.
Created using OpenGl & C++. 

How to Play
The player controls the ship using the W A S D keys and can shoot a bullet using the mouse left-click. The asteroids rotate continuously, have different sizes, and an irregular hexagon shape. To pass to the next level, the player must either wait for the asteroid wave to pass the lower screen border or move the ship through the upper screen border.

The game has a total of six levels, and the difficulty increases by increasing the asteroids' speed after each level and increasing their damage after passing level 5. The player's health is signaled by the three hearts in the upper left corner, and each collision causes the player to lose one heart until level 6. From level 6 and on, the color of the asteroids changes to yellow, and each collision depletes two hearts from the player's health.

Once all of the hearts are consumed, the player loses, and the game resets its speed and level number. To reset and randomize the positions of the asteroids after each level, the game has a reset() method, which gives each asteroid a random float between 0 and 2 for y axes, so some asteroids will come from outside the screen too.

The collisions are detected by rounding the (ship & asteroid\bullet & asteroid) positions and checking if they are equal. If it's true, the collision is achieved, and the player takes damage (ship and asteroid collision) or asteroids get destroyed (bullet collision). Once a bullet collision happens, the asteroid is removed by moving it out of the screen bounds till the next level is reached, and asteroid positions are reset.


Sound Effects
The game includes a shooting sound effect using playSound(). If the program fails to run, you can either comment line 230 or make sure to add Winmm.lib dependency by going to project settings -> linker -> input -> additional dependencies -> add Winmm.lib.
