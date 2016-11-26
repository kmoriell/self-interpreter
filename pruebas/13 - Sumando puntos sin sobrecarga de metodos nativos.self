'\n' print. 'INICIA TEST.' print. '\n' print.
'Un ejemplo complejo en el que se setea puntos, se los multiplica por escalares y se los suma entre si.' print. '\n' print. '\n' print.

lobby _AddSlots:
(|
	punto =
	(|
		mostrar = ( || '(x = ' print. x print. '; y = ' print. y print. ')' print.).
		mulEscalar = (| :ptr. temp. | temp: (self clone). temp x: (x * ptr). temp y: (y * ptr). temp.).
		setX = (| :valor. | self x: valor.).
		setY = (| :valor. | self y: valor.).
		suma = (| :otroPunto. temp. | temp: (self clone). temp x: (x + (otroPunto x)). temp y: (y + (otroPunto y)). temp.).
	|).
|).

lobby _AddSlots:
(|
	p1 <- (| x<-0. y<-0. proto*=punto. |).
	p2 <- (| x<-0. y<-0. proto*=punto. |).
|).

'Ambos puntos se inicializan en (0;0).' print. '\n' print.
'p1: ' print. p1 mostrar. '\n' print.
'p2: ' print. p2 mostrar. '\n' print.
'\n' print.

'Seteamos con persistencia los puntos y los mostramos.' print. '\n' print.
p1 setX: 1. p1 setY: 2.
p2 setX: 3. p2 setY: 4.
'p1: ' print. p1 mostrar. '\n' print.
'p2: ' print. p2 mostrar. '\n' print.
'\n' print.

'Multiplicamos el punto p2 por el escalar 2 sin persistencia y lo mostramos.' print. '\n' print.
'p2*2 : ' print. (p2 mulEscalar: 2) mostrar. '\n' print.
'\n' print.

'Mostramos nuevamente p2 para verificar la no persistencia.' print. '\n' print.
'p2: ' print. p2 mostrar. '\n' print.
'\n' print.

'Aplicamos con persistencia al p2 su valor*2.' print. '\n' print.
p2 : (p2 mulEscalar: 2).

'Mostramos el nuevo valor del punto p2.' print. '\n' print.
'p2: ' print. p2 mostrar. '\n' print.
'\n' print.

'Sumamos ambos puntos. Recordemos que p1=(1;2) y p2=(6;8)' print. '\n' print.
'El resultado debería ser (7;10)' print. '\n' print.
'p1+p2 : ' print. (p1 suma: p2) mostrar. '\n' print.

'\n' print.
'FIN TEST.' print. '\n' print.
