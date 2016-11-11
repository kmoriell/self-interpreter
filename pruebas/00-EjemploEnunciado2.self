'\n' print. 'INICIA TEST.' print. '\n' print.
'Se ejecuta un test similar al del enunciado.' print. '\n' print.
'Notas a tener en cuenta:' print. '\n' print.
'Todavia no se soportan keyword message con multiples argumentos.' print. '\n' print.
'Todavia no se soporta la re-implementacion de operadores (tecnicamente por enunciado no era posible ya que los operadores no cumple con la sintaxis de un name).' print. '\n' print. '\n' print.

lobby _AddSlots:
(|
	punto =
	(|
		squarenorm = (|| ((x*x)+(y*y)). ).
		print = (|| '(' print. x print. ';' print. y print. ')' print.).
		* = (| :scalar. temp. |
						temp: (self clone).
						temp x: ((temp x) * scalar).
						temp y: ((temp y) * scalar).
						temp.	
						).
	|).
|).

lobby _AddSlots:
(|
	punto1 = (| x<-0. y<-1. proto*=punto. |).
	punto2 = (| x<-1. y<-0. proto*=punto. |).
|).

'Observamos el lobby.' print. '\n' print.
lobby printObj. '\n' print.

'Imprimimos punto1 * 2 con el metodo multiplicar' print. '\n' print.
'>>> (punto1 * 2) print.' print. '\n' print.
'Salida esperada: (0;2)' print. '\n' print.
'\n' print.

'Imprimimos punto1 y verificamos que no se haya persistido la modificacion de los valores x e y producto de la ejecucion anterior.' print. '\n' print.
'>>> punto1 print.' print. '\n' print.
'Salida esperada: (0;1)' print. '\n' print.
'\n' print.

'FIN TEST.' print. '\n' print.
