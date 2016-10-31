lobby _AddSlots:(| punto =
	(|	
		x <- 3.
		y <- 4.
		squarenorm = ( || ((x*x)+(y*y)). ).
		print = (|| '(' print. x print. ';' print. y print. ')' print.).
		qwe = (| temp <- 1. |
			qwe temp:2.
			qwe temp:3.
			qwe temp:4.
			).
		rty = (| :scalar. |
			'scalar = ' print.
			scalar print.
			'\n' print.
			).
	|).
|).

lobby _AddSlots:(| val <- 3.|).

(punto qwe) print.
lobby val: (punto qwe).
'\n' print.
'Val = ' print.
val print.
'\n' print.
'squarenorm de: ' print.
punto print.
' es: ' print.
(punto squarenorm) print.
'\n' print.
punto rty: 1.
