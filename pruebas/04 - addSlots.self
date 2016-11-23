'\n' print. 'INICIA TEST.' print. '\n' print.
'Se prueba el metodo _AddSlots' print. '\n' print. '\n' print.

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

'>>> lobby _AddSlots: ... ' print. '\n' print. 
'>>> lobby printObj.' print. '\n' print. 
lobby printObj. '\n' print.

'Agregamos un slot z a punto utilizando lobby de forma implicita.' print. '\n' print.
'>>> punto _AddSlots: (|z=2.|). ' print. '\n' print. 
'>>> lobby printObj.' print. '\n' print. 
punto _AddSlots: (|z=2.|).
lobby printObj. '\n' print.

'FIN TEST.' print. '\n' print.
