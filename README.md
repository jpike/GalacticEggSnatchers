# GALACTIC EGG SNATCHERS

This in-development game is an Easter-themed game similar to Space Invaders.  Target release date is April 30, 2014, with possibly some additional updates done through May 3, 2014.  It is being developed as a collaborative project in the http://www.reddit.com/r/hobbygamedev sub-reddit.

The game will be a native Windows game, running at least on Windows 7.

## Story

This story isn't included in the game, but it may be add a little fun to the experience:

Easter is approaching, and eggs are on short supply throughout the galaxy. The only remaining supply of Easter eggs is on planet Earth, and aliens have come to abduct these last few eggs! As an Easter-loving bunny, it is your responsibility to use your supply of carrot missiles to protect the Earth's supply of Easter eggs! Otherwise, children will wake up sad on Easter morning because they won't have any colorful eggs to find.

## Gameplay

The enemies will be aliens, and they will fire at the player.  The player will be a bunny that fires carrots for missiles.  The "bunkers" that protect the player will be replaced with Easter eggs.  Instead of the aliens destroying the eggs, they will be trying to abduct them.  An unused idea is that eggs could be placed in Easter baskets.

## Building the Code

The game is programmed using C++ within a Visual Studio 2012 Express environment.

The main dependency is [SFML 2.1](http://sfml-dev.org/) ([zlib/libpng license](http://sfml-dev.org/license.php)).

SFML is not included with this project and must be downloaded externally.  To build the solution, you'll need to have an environment variable set to the following directory:

* SFML_DIR - Set to the root directory for SFML 2.1 (with include and lib directories).

