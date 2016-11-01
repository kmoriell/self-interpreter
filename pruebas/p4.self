lobby _AddSlots:(| punto =
	(|	
		x <- 3.
		y <- 4.
		squarenorm = ( || ((x*x)+(y*y)) print. ).
		print = (|| x print. y print.).
		qwe = (| temp <- 3. |
			'temp: ' print.			
			temp print.
			'\n' print.
			temp: (x*y).
			'temp: ' print.	
			temp print.
			'\n' print.
			).
	|).
|).

lobby printObj.
punto qwe.
