'\n' print. 'INICIA TEST.' print. '\n' print.
'Se ejecuta un test que provee la cátedra (elaborado por Martin Di Paola) adaptado para los prints.' print. '\n' print.

'Debería dar 1.' print. '\n' print.
lobby _AddSlots: (| x <- 1. |) . 
(lobby x) print. '\n' print.
'\n' print.

'Debería dar 2.' print. '\n' print.
lobby x: 2.
(lobby x) print. '\n' print.
'\n' print.

'Debería dar 1.' print. '\n' print.
lobby x: 1.
(lobby x) print. '\n' print.
'\n' print.

'Debería dar 3.' print. '\n' print.
lobby _AddSlots: (| y <- (| a = 1. | a + 2. ). |) .
(lobby y) print. '\n' print.
'\n' print.

'Se ejecutan mensajes de los que no se indica que se espera obtener.' print. '\n' print.
lobby _AddSlots: (| b <- 'hola mundo' . |) .
lobby _AddSlots: (| d . |) .
lobby _RemoveSlots: (| y. |).
'\n' print.

'Debería dar 6.' print. '\n' print.
((((lobby x) + (lobby x)) + (lobby x)) * ((lobby x) + (lobby x))) print. '\n' print.
'\n' print.

'Debería dar 6.' print. '\n' print.
lobby _AddSlots: (| twice <- (| :a . | a * 2. ). |) .
(lobby twice: 3) print. '\n' print.
'\n' print.

'Debería dar 5.' print. '\n' print.
lobby _AddSlots: (| twiceplusone <- (| :a . tmp . | tmp: (a * 2). tmp + 1. ). |) .
(lobby twiceplusone: 2) print. '\n' print.
'\n' print.

'Debería dar 5.' print. '\n' print.
(lobby twiceplusone: 2) print. '\n' print.
'\n' print.

'Debería dar "hello".' print. '\n' print.
lobby _AddSlots: (| some <- (| sayhello = (| | 'hello'. ). |). |).
((lobby some) sayhello) print.  '\n' print.
'\n' print.

'Debería dar "hello".' print. '\n' print.
lobby _AddSlots: (| othersome <- (| parent* = (lobby some). |). |).
lobby othersome.
((lobby othersome) sayhello) print. '\n' print.
'\n' print.

'Probando clones.' print. '\n' print.
lobby _AddSlots: (| somecloned = (lobby some) clone. |).
(lobby somecloned) _AddSlots: (| q. |).
'no tiene el slot q <- nil.' print. '\n' print.
(lobby some) printObj.
'\n' print.
'si tiene el slot q <- nil probando que es un clone.' print. '\n' print.
(lobby somecloned) printObj.
'\n' print.

'Imprime 3.' print. '\n' print.
(1 + 2) print. '\n' print.
'\n' print.

'Deberia fallar por inmutable.' print. '\n' print.
lobby _AddSlots: (| mutable <- 1. inmutable = 2. |).
lobby mutable: 4.
lobby inmutable: 4.
