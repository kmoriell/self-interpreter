lobby _AddSlots:(| punto =
	(|	
		x <- 3.
		y <- 4.
		squarenorm = ( || ((x*x)+(y*y)). ).
		printPunto = (|| '(' print. x. ';' print. y print. ')' print. '\n' print.).
		setX = (| :value.|
			self x: value.
			).
		setY = (| :value.|
			self y: value.
			).
	|).
|).

lobby printObj.
punto printPunto.
punto setX: 10.
punto setY: 20.
punto printPunto.
