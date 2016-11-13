lobby _AddSlots:(| punto =
	(|	
		inc = (| :valor. contador <- 0.|
				contador:(contador+valor).
				contador.
			).
	|).
|).

'El contador de inicializa en 0, y se deberia incrementar en 1.' print.
'Como para los urinarios esta la triple ejecucion por backtracking, el deberia dar 3 en vez de 1.' print. '\n' print.
'>>> (punto inc: 1) print' print. '\n' print.
'Por lo dicho antes, salida esperada 3.' print. '\n' print.
(punto inc: 1) print. '\n' print.

'En la proxima ejecucion, como contador se define dentro del metodo deberia volver a arrancar en 0.' print. '\n' print.
'Es decir que el resultado de la ejecucion deberia dar nuevamente 3 (en realidad 1 pero triplica).' print. '\n' print.
'Actualmente como no se aplica la clonacion el method object se modifican nuevamente sus valores y ahora vale 6.' print. '\n' print.
'>>> (punto inc: 1) print' print. '\n' print.
'Por lo dicho antes, salida esperada 3.' print. '\n' print.
(punto inc: 1) print. '\n' print.
