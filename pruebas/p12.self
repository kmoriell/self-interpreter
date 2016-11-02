lobby _AddSlots:(| y <- 1.
        x =
	(| temp <- 1.|
		self y: ((self y) + 1).
		self y.
	).
|).
lobby _AddSlots: (| val. |).

lobby x.
(lobby y) print.

lobby x.
(lobby y) print.
