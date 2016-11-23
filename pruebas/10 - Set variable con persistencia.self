'\n' print. 'INICIA TEST.' print. '\n' print.
'Se prueba la ejecucion de un codeSegment que logre persistir cambios en otro objeto.' print. '\n' print. '\n' print.

lobby _AddSlots:(| punto =
	(|	
		x <- 3.
		y <- 4.
		squarenorm = ( || ((x*x)+(y*y)). ).
		setX = (| :value.|
			self x: value.
			).
		setY = (| :value.|
			self y: value.
			).
	|).
|).

'Observamos el lobby.' print. '\n' print. 
'>>> lobby printObj.' print. '\n' print. 
lobby printObj. '\n' print.

'Mostramos la norma al cuadrado.' print. '\n' print. 
'>>> (punto squarenorm) print.' print. '\n' print. 
'Salida esperada: 25' print. '\n' print. 
(punto squarenorm) print. '\n' print.
'\n' print.

'Seteamos X e Y con persistencia.' print. '\n' print.
'>>> punto setX: 10.' print. '\n' print.
punto setX: 10.
'>>> punto setY: 20.' print. '\n' print.
punto setY: 20.
'\n' print.

'Mostramos la nueva norma al cuadrado.' print. '\n' print. 
'>>> (punto squarenorm) print.' print. '\n' print. 
'Salida esperada: 500' print. '\n' print. 
(punto squarenorm) print. '\n' print.

'\n' print.
'FIN TEST.' print. '\n' print.
