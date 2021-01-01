# Solver_for_Peg_Solitaire
Solver for Peg Solitaire: Graph Search

In this programming assignment, an algorithm to solve Peg Solitaire (known as Brainvita in India)has been built. The game was invented in the XVII century in Madagascar. The ﬁrst reference to the rules appeared in 1687 in a french cultural magazine. It is one of the classic board game puzzles, and several boards that diﬀer in shape and size appeared through time. We can play the game in terminal using the keyboard.

The Peg Solitaire game enginge code in this assignment was adapted from the open-source terminal version made available by Maurits van der Schee 1 .

Algorithm：

1: procedure PegSolver(start, budget) 
2: n ← initNode(start) 
3: stackPush(n) 
4: remainingPegs ← numPegs(n) 
5: while stack = empty do ̸ 
6: n ← stack.pop() 
7: exploredNodes ← exploredNodes + 1 
8: if numPegs(n) < remainingPegs then 
9: saveSolution(n) 
10: remainingPegs ← numPegs(n) 
11: end if 
12: for each jump action a ∈ [0, m) × [0, m) × { Left, Right, Up, Down } do 
13: if a is a legal action for node n then 
14: newNode ← applyAction(n, a) . Create Child node 
15: generatedNodes ← generatedNodes + 1 
16: if won(newNode) then . Peg Solitaire Solved 
17: saveSolution(newNode) 
18: remainingPegs ← numPegs(newNode) 
19: return 
20: end if 
21: if newNode.state.board seen for the ﬁrst time then . Avoid duplicates 
22: stackPush(newNode) . DFS strategy 
23: end if 
24: end if 
25: end for 
26: if explored nodes ≥ budget then 
27: return . Budget exhausted 
28: end if 
29: end while 
30: end procedure
