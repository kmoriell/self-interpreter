lobby _AddSlots:(| punto =
	(|	
		x <- 3.
		y <- 4.
		print = (|| '(' print. x print. ';' print. y print. ')' print.).
		rty = (| temp.|
			temp: (self clone).
			temp x: 1.
			temp y: 0.
			temp.
			).
	|).
|).

punto print.
(punto rty) print.

'fin' print.
'\n' print.
