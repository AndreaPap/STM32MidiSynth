from matplotlib.pyplot import*
from numpy import*

# circuito equivalente speaker R ( L || Cp )
# aggiunta di condensatore serie Cf e induttanza Lf
# rapporto tra corrente che circola nell'induttana ( circa proporzionale alla pressione sonora prodotta ) e la tensione in ingresso

Cf = 2200e-6
Lf = 0
R = 3.2
L = 0.5e-3
C = 0.5e-9

W = 2 * pi * geomspace( 0.1, 80000, 1000 )

Zcf = 1 / ( 1j * W * Cf )
Zlf = 1j * W * Lf
Zc = 1 / ( 1j * W * C )
Zl = 1j * W * L
Zc_Zl = Zc * Zl / ( Zc + Zl )

H = Zc / ( ( Zcf + R + Zc_Zl + Zlf ) * ( Zc + Zl ) ) 
ModH = abs( H )
ModH /= max( ModH )
ModH = 10 * log10( ModH )
plot( W / ( 2 * pi ), ModH )
xscale( 'log' )
show()
