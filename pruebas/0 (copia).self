lobby printObj.

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

lobby printObj.
