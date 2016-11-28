'\n' print. 'INICIA TEST.' print. '\n' print.
'Se prueba el metodo _RemoveSlots' print. '\n' print. '\n' print.

lobby _AddSlots:
(|
	n1 =
	(|
		n2 =
		(|
			n3 = 100.
		|).
	|).
|).

'Agregamos varios slots anidados...' print. '\n' print.
'>>> lobby _AddSlots: ... ' print. '\n' print. 
'>>> lobby printObj.' print. '\n' print. 
lobby printObj. '\n' print.

'Removemos el slot n3 (el mas anidado) desde el contexto lobby.' print. '\n' print.
'>>> ((lobby n1) n2) _RemoveSlots: (|n3.|).' print. '\n' print. 
'>>> lobby printObj. ' print. '\n' print. 
((lobby n1) n2) _RemoveSlots: (|n3.|).
lobby printObj. '\n' print.

'Removemos el slot n1 utilizando el lobby de forma implicita (ya que es el contexto de esta consola).' print. '\n' print.
'>>> _RemoveSlots: (|n1.|).' print. '\n' print. 
'>>> lobby printObj. ' print. '\n' print. 
_RemoveSlots: (|n1.|).
_RemoveSlots: (|_AddSlots.|).
lobby printObj. '\n' print.


'FIN TEST.' print. '\n' print.
