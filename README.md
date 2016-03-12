# othello
Any useful information goes here

================ What was ready by milestone 1. ============
-A 1-play deep search (my move, opponents move). (Michael)
-A basic heuristic (corners good, next to corners bad), with option to do
simple stone-count instead for testing minimax; some structural help (i.e. finding
a vector of possible moves) (Rita) 
+ A whole bunch of streamlining and debugging (both)
+Tuning (both)

================ Improvements to make tournament worthy: ===
-Recursive Alpha-beta pruning to arbitrarily set depth that recognizes game-end
states (and weights them appropriately). (Rita)
-Heuristic improvement to consider mobility, frontier spaces, and some 
dynamic adjustment of weights (next to corner spaces are no longer negative
if the corner is yours. ).