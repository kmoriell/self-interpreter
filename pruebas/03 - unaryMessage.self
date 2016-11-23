'\n' print. 'INICIA TEST.' print. '\n' print.
'Se prueba mensajes unarios:' print. '\n' print. '\n' print.

'RECEIVER NAME: receiver explicito' print. '\n' print.
'>>> lobby printObj.' print. '\n' print. 
lobby printObj. '\n' print.

'RECEIVER NAME: receiver instanciado on the fly' print. '\n' print.
'>>> nil printObj.' print. '\n' print. 
nil printObj. '\n' print.

'RECEIVER NAME: receiver (lobby) implicito' print. '\n' print.
'>>> lobby _AddSlots: (|x<-5.|).' print. '\n' print. 
'>>> x printObj.' print. '\n' print. 
lobby _AddSlots: (|x<-5.|).
x printObj. '\n' print.

'FIN TEST.' print. '\n' print.
