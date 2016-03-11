# othello
Any useful information goes here

-rsonka, 3/6/2016: I successfully pulled from the project. 
Outline.cpp is only a cpp file so that my text editor will interpret it as a c file.
Point of outline: quick reference for functions/classes/object types.

IDEAS:, 3/6/2016:
-Could make a 64-long array of Move *'s for all the possible moves. Would it be faster 
to reference that than to make new Move *'s? I imagine it would definitely help us keep
track of our memory, which we've been told is important. 
-I'm not sure where exactly the inefficiency is in Board. I don't see any obvious way to 
improve any of its pre-existing functions, with one possible exception:
hasMove has to scan the entire board in order to check if the given 
side has a valid move. One thing we could do is add two more bitsets as class members
to Board (are bitsets actually the fastest thing here? They're definitely one of the
more memory-efficient objects I've ever seen...). These bit sets would represent the 
legal moves for BLACK and for WHITE. They would be updated every time the 
board's doMove function was called. That way, hasMove would be a simple count
of the bitset-and we wouldn't run the risk of having to scan the board multiple
times if we wanted to call haveMove more than once in our decisions.
-Board should really contain some additional information about the spaces. A weighting
is the obvious starting point. Tracking which spaces are 'frontier' is something
we should definitely do (if time).

================ What was ready by milestone 1. ============
-
