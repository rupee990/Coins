# Coins
Coin Spawner for StitchHeads Studio

The Coins

///////////////////////////////////////////////////////////////////////////////

Coin Class:

Contains 3 variables the user can define:
- Rotation Rate, How fast the coin rotates (just for effect)
- arrow, User can rotate this to decide from what direction the coin can be picked up
- Accuracy, I use a dot product to see if the player is in front or back of the pickup direction, the default is 0.8, if my dot product is above 0.8 then I can pick up the coin, -1.0 would be every direction.

The coin has a Sphere Collider with a radius of 64.0f which is used to pick up the coin.

///////////////////////////////////////////////////////////////////////////////

Coin Spawner Class:

The Coin spawner contains The basic spawning variables such as:
- Number of Coins, how many coins to spawn.
- Spawn Rate, How Fast they spawn
- Spawn Area, in what area should they spawn in.

Additionally I added 2 spawn types:
- random, Will spawn coins randomly inside area, ignoreing collisions
- Grid, Will spawn in a grid fashion for the amount of coins.

Some properties are used to adjust the checks such as:
- Ground Check Distance, Distance used for the linetrace to find the ground or surface.
- Ground Offset, Offset to place the coin off the ground, by default this is 64 ( the coin's radius )

From the Spawner the User Can also change the direction of an arrow, which the coin will inherit as pickup direction. I added 3 bools aswell which when ticked will get a random direction on that axis.

Finally The user can adjust the Coin's Radius if they want the collider to be bigger or smaller.

///////////////////////////////////////////////////////////////////////////////
