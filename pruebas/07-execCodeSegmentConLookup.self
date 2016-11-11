'\n' print. 'INICIA TEST.' print. '\n' print.
'Se prueba ejecucion de codigo con variables usando lookup con self.' print. '\n' print. '\n' print.

lobby _AddSlots:
(|
	x = 3.
	y = 4.
	suma = (||x+y.).
|).

'Agregamos un slot suma con codigo ejecutable.' print. '\n' print.
'Al llamar a lobby suma se deberia hacer un lookup del atributo x e y.' print. '\n' print.
'Ambos son encontrados a traves del parent implicito self que apunta al objeto (lobby) que llamo al metodo suma.' print. '\n' print.
'>>> lobby printObj.' print. '\n' print.
lobby printObj. '\n' print.

'>>> suma printObj.' print. '\n' print. 
suma printObj.
'>>> suma print.' print. '\n' print. 
'Salida esperada: 7' print. '\n' print.
suma print. '\n' print.
'\n' print.
'>>> (((suma*2)+1)/3) print.' print. '\n' print. 
'Salida esperada: 5' print. '\n' print.
(((suma*2)+1)/3) print. '\n' print.
'\n' print.
'FIN TEST.' print. '\n' print.
