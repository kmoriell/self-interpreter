lobby _AddSlots:(| punto =
	(|	
		x <- 3.
		y <- 4.
		squarenorm = ( || ((x*x)+(y*y)). ).
		print = (|| '(' print. x print. ';' print. y print. ')' print.).
	|).
|).

lobby printObj.
punto print.
punto squarenorm.
(punto squarenorm) print.
punto print.
