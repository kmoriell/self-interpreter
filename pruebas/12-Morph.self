lobby _AddSlots:
(|
	punto =
	(|
		x <- 3.
		y <- 4.
		squarenorm = (|| ((x*x)+(y*y)). ).
		print = (|| '(' print. x print. ';' print. y print. ')' print.).
	|).
	holaMundo = 
	(|
		hola = 'hola'.
		mundo = 'mundo'.
		print = (|| hola print. ' ' print. mundo print.).
	|).
|).

lobby punto.
