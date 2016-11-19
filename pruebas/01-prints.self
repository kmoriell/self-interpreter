'\n' print. 'INICIA TEST.' print. '\n' print.
'Se prueba que se realicen prints de objetos primarios:' print. '\n' print. '\n' print.

'STRING' print. '\n' print.
'BUG: no soporta comillas simples anidadas.' print. '\n' print.
'>>> "Hola!, soy un string." print.' print. '\n' print. 
'Hola!, soy un string.' print. '\n' print.
'>>> "Hola!, soy un string." printObj.' print. '\n' print. 
'Hola!, soy un string.' printObj.
'\n' print.

'NUMBER' print. '\n' print.
'BUG: solo soporta naturales + 0' print. '\n' print.
'BUG: Hay dudas sobre si se toman bien los + y -' print. '\n' print.
'>>> 3 print.' print. '\n' print. 
3 print. '\n' print.
'>>> -1 print.' print. '\n' print. 
-1 print. '\n' print.
'>>> +10 print.' print. '\n' print. 
+10 print. '\n' print.
'\n' print.

'BOOL' print. '\n' print.
'- aun no implementados' print. '\n' print.
'\n' print.

'NIL' print. '\n' print.
'>>> nil print.' print. '\n' print. 
nil. '\n' print.
'>>> nil printObj.' print. '\n' print. 
nil printObj. '\n' print.

'OBJETO' print. '\n' print.
'>>> (||) printObj.' print. '\n' print. 
(||) printObj.
'>>> (||"soy un bloque de codigo".) printObj.' print. '\n' print. 
(||'soy un bloque de codigo'.) printObj.
'\n' print.

'FIN TEST.' print. '\n' print.
