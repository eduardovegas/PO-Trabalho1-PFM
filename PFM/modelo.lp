\ENCODING=ISO-8859-1
\Problem name: IloCplex

Maximize
 obj: X(8) + X(9)
Subject To
 FLUX(1): X(0) - X(3)  = 0
 FLUX(2): X(1) - X(4) - X(5) - X(6)  = 0
 FLUX(3): X(2) + X(4) - X(7)  = 0
 FLUX(4): X(3) + X(5) - X(8)  = 0
 FLUX(5): X(6) + X(7) - X(9)  = 0
Bounds
 0 <= X(0) <= 6
 0 <= X(1) <= 4
 0 <= X(2) <= 1
 0 <= X(3) <= 4
 0 <= X(4) <= 3
 0 <= X(5) <= 1
 0 <= X(6) <= 3
 0 <= X(7) <= 4
 0 <= X(8) <= 4
 0 <= X(9) <= 9
End
