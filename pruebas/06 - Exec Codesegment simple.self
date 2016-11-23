'\n' print. 'INICIA TEST.' print. '\n' print.
'Se prueba ejecucion de codigo simple.' print. '\n' print. '\n' print.

lobby _AddSlots:
(|
	lobbyPrint = (||3+4.).
|).

'Agregamos un slot lobbyPrint con codigo ejecutable.' print. '\n' print.
'Al llamar a lobby lobbyPrint se nos deberia retornar un objeto numerico 7' print. '\n' print.
'resultado de la ejecucion de código 3+4.' print. '\n' print.'\n' print.
'>>> lobby printObj.' print. '\n' print.
lobby printObj. '\n' print.

'>>> lobbyPrint printObj.' print. '\n' print. 
lobbyPrint printObj.
'>>> lobbyPrint print.' print. '\n' print. 
'Salida esperada: 7' print. '\n' print.
lobbyPrint print. '\n' print.
'\n' print.
'>>> (((lobbyPrint*2)+1)/3) print.' print. '\n' print. 
'Salida esperada: 5' print. '\n' print.
(((lobbyPrint*2)+1)/3) print. '\n' print.
'\n' print.
'FIN TEST.' print. '\n' print.
