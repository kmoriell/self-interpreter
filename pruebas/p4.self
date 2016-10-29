lobby _AddSlots:(| punto =
	(|	
		x <- 3.
		y <- 4.
		squarenorm = ( || ((x*x)+(y*y)) print. ).
		print = (|| x print. y print.).
		qwe = (| temp <- 3. |
			temp print.			
			qwe temp: 1.
			temp print.
			).
	|).
|).

lobby printObj.

punto qwe.
