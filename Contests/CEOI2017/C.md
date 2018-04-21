# C Mousetrap
Time Limit: 5 s Memory Limit: 512 MB

Dumbo the elephant has a huge labyrinth with n rooms numbered 1 . . . n and n−1 passages in such way that it is possible to reach any room from any other room. Unfortunately, a mouse sneaked into the labyrinth. Dumbo is terribly afraid of mice, so he sets a mousetrap in room t. Obviously, the mouse avoids the room with the trap, so Dumbo has to think of a better strategy to bait the mouse into the trap. The mouse constantly runs around and never stops, unless it has nowhere to move. He also knows that the mouse leaves a dirty trail of droppings and footprints in every passage it uses. The mouse then refuses to use a dirty passage again. Dumbo can clean a dirty passage, or block a passage with stones.By blocking passages or cleaning them, he wants to force the mouse to run into the trap.

He would like to do this in a minimal number of moves, as he feels highly uncomfortable in the presence of a mouse.

We can describe this as a game for two players. The mouse tries to maximize the number of Dumbo’s moves. The Dumbo tries to win in minimal number of moves. The first player is Dumbo. On his turn, he may clean one dirty passage of the labyrinth or block one passage. It doesn’t matter if the blocked passage is clean or not. He cannot unblock a passage. He may, however, choose to do nothing. Turns in which Dumbo decides to do nothing do not count as moves. When it is the mouse’s turn, the mouse will choose a clean unblocked passage and run to the adjacent room down that passage.If there is no such passage leading from mouse’s current room, the mouse won’t move.Initially, all the passages are clean, the mouse is in room m, the trap is in room t,and it is Dumbo’s turn. What is the minimum number of moves (passages cleaned and blocked) Dumbo needs if both players play optimally (mouse’s goal is to maximize the number of Dumbo’s moves)?
## Input
Integers n, t and m will be given in the first line, separated by spaces. n − 1 lines follow.
In each line, ai and bi are given, separated by a space, which indicates a passage between
rooms ai and bi.
Note that the input size is large.
## Constraints
```
• 1 ≤ n, t, m ≤ 106
Subtask 1 (20 points)
• n ≤ 10
Subtask 2 (25 points)
• It is guaranteed that a passage between rooms m and t exists.
Subtask 3 (20 points)
• n ≤ 1000
Subtask 4 (35 points)
• no additional constraints
```
## Output
Your program should print the number of Dumbo’s moves.
## Example
### Input
```
10 1 4
1 2
2 3
2 4
3 9
3 5
4 7
4 6
6 8
7 10
```
## Output
```
4
```
## Comment
One possible scenario:

* Dumbo blocks passage between rooms 4 and 7.
* Mouse moves to room 6. The passage between rooms 4 and 6 is now dirty.
* Dumbo blocks the passage between rooms 6 and 8.
* Mouse cannot move.
* Dumbo cleans the passage between rooms 4 and 6.
* Mouse moves to room 4. The passage between rooms 4 and 6 is dirty.
* Dumbo blocks the passage between rooms 2 and 3.
* Mouse moves to room 2. The passage between rooms 2 and 4 is dirty.
* Dumbo doesn’t do anything.
• Mouse can only move to room 1 and gets caught into a trap.
Dumbo made 4 moves.
## Solve
待填坑