'\n' print. 'INICIA TEST.' print. '\n' print.
'Se prueba la ejecucion de metodos a traves de un parentSlot.' print. '\n' print. '\n' print.

lobby _AddSlots:
(|
	punto =
	(|
		x <- 3.
		y <- 4.
		squarenorm = (|| ((x*x)+(y*y)). ).
		mostrar = (|| '(' print. x print. ';' print. y print. ')' print.).
	|).
|).

lobby _AddSlots:
(|
	punto1 = (|	padre* = punto.	|).
|).


'Se creo el slot punto y el slot punto1 con un parentSlot que apunta a punto.' print. '\n' print.
'>>> lobby printObj.' print. '\n' print. 
lobby printObj.

'>>> punto1 mostrar.' print. '\n' print. 
'Salida esperada: (3;4)' print. '\n' print.
punto1 mostrar. '\n' print.

'\n' print.
'>>> (punto1 squarenorm) print.' print. '\n' print. 
'Salida esperada: 25' print. '\n' print.
(punto1 squarenorm) print. '\n' print.

'\n' print.
'FIN TEST.' print. '\n' print.
