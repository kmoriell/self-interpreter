lobby _AddSlots:(| punto =
	(|	
		inc = (| :valor. contador <- 0.|
				contador:(contador+valor).
				contador.
			).
	|).
|).

'El contador de inicializa en 0, y se deberia incrementar en 1.' print.
'>>> (punto inc: 1) print' print. '\n' print.
'Salida esperada: 1.' print. '\n' print.
(punto inc: 1) print. '\n' print.

'En la proxima ejecucion, como contador se define dentro del metodo deberia volver a arrancar en 0.' print. '\n' print.
'>>> (punto inc: 1) print' print. '\n' print.
'Salida esperada: 1.' print. '\n' print.
(punto inc: 1) print. '\n' print.
