lobby _AddSlots:
(|
	punto =
	(|
		squarenorm = (|| ((x*x)+(y*y)). ).
		print = (|| '(' print. x print. ';' print. y print. ')' print.).
		* = (| :scalar. temp. |
						temp: (self clone).
						temp x: ((temp x) * scalar).
						temp y: ((temp y) * scalar).
						temp.	
						).
	|).
|).

lobby _AddSlots:
(|
	punto1 = (| x<-0. y<-1. proto*=punto. |).
	punto2 = (| x<-1. y<-0. proto*=punto. |).
|).

punto1 print.
