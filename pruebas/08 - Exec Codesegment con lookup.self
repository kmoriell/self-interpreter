'\n' print. 'INICIA TEST.' print. '\n' print.
'Se prueba ejecucion de codigo con variables usando lookup con self un poco mas compleja.' print. '\n' print. '\n' print.

lobby _AddSlots:
(|
	punto =
	(|
		x <- 3.
		y <- 4.
		squarenorm = (|| ((x*x)+(y*y)). ).
		mostrar = (|| '(' print. x print. ';' print. y print. ')' print.).
	|).
	holaMundo = 
	(|
		hola = 'hola'.
		mundo = 'mundo'.
		mostrar = (|| hola print. ' ' print. mundo print.).
	|).
|).

'Se crearon varios slots en el lobby.' print. '\n' print.
'>>> punto mostrar.' print. '\n' print. 
'Salida esperada: (3;4)' print. '\n' print.
punto mostrar. '\n' print.

'\n' print.
'>>> (punto squarenorm) print.' print. '\n' print. 
'Salida esperada: 25' print. '\n' print.
(punto squarenorm) print. '\n' print.

'\n' print.
'>>> holaMundo mostrar.' print. '\n' print. 
'Salida esperada: hola mundo' print. '\n' print.
holaMundo mostrar. '\n' print.

'\n' print.
'FIN TEST.' print. '\n' print.
