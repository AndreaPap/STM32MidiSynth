from numpy import*
from matplotlib.pyplot import*

# simulazione C-R-R-C

def Par( Z1, Z2 ): return ( Z1 * Z2 ) / ( Z1 + Z2 )

W = 2 * pi * geomspace( 0.1, 80000, 1000 )
#C1 = 10e-6
#R1 = 1500
#C2 = 470e-9 # intersezione a 3000 ( circa max sensibilità )
#R2 = 2700
#C2 = 1e-6 # sembra più bilanciato( comunque privilegia i 3000 )
#R2 = 1500

C1 = 4.7e-6
R1 = 1500
C2 = 100e-9
R2 = 15000

ZC1 = 1 / ( 1j * W * C1 )
ZC2 = 1 / ( 1j * W * C2 )

H = Par( R1, R2 + ZC2 ) / ( ZC1 + Par( R1, R2 + ZC2 ) )
H *= ZC2 / ( R2 + ZC2 )

ModH = abs( H )
ModH /= max( ModH )
ModH = 20 * log10( ModH ) # uso 20 così è come se avessu calcolato il quadrato

ModH_Ideal = []
for Cur in range( 0, len( W ) ):
    # tilt parte da 50 Hz a -4.5 dB / oct, verificato con progetto rustle
    if( W[ Cur ] <= 50 * 2 * pi ): ModH_Ideal.append( 0 )
    else: ModH_Ideal.append( log2( W[ Cur ] / ( 2 * pi * 50 ) ) * ( -4.5 ) )

plot( W / ( 2 * pi ), ModH )
plot( W / ( 2 * pi ), ModH_Ideal )
xscale( 'log' )
show()
