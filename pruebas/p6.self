lobby _AddSlots:(| punto =
	(|	
		x <- 3.
		y <- 4.
		squarenorm = ( || ((x*x)+(y*y)). ).
		print = (|| '(' print. x print. ';' print. y print. ')' print.).
		qwe = (| temp <- 2. |
			temp: 1.
			).
	|).
|).

lobby printObj.
punto qwe
