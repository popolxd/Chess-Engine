# Chess Engine

Features:
- Classic minimax search algorithm
- All classical features of chess (except promoting to a piece different from queen)
- Primitive piece maps implemented
- Capture search can be used

Things to improve:
- Move generation is probably slow (could use bitboards for this in a future)
- Check checking is really slow (have to make a move, check if there is an check and undo a move, should store enemy attacking squares or smth)
- Proper undo function
- Proper mate and stalemate checking
- Try move ordering
- Avoid looping the whole board whenever I try to generate moves in minimax function (keep track where the pieces ares)
- Maybe try NegaMax algorithm for notational compactness
- General optimization