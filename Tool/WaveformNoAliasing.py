from numpy import*
from matplotlib.pyplot import*

def PWM( Frequency, Duty, N, Sr, Duration ):
    Time = linspace( 0.0, Duration, int( Duration * Sr ) )
    Out = zeros( [ len( Time ) ] )
    
    for n in range( 1, N + 1 ):
        Out += ( 4 / ( pi * n ) ) * sin( n * pi * Duty ) * sin( ( 2 * pi * n * Frequency * Time ) + ( pi / 2 ) )
    return Out

def Triangle( Frequency, N, Sr, Duration ):
    Time = linspace( 0.0, Duration, int( Duration * Sr ) )
    Out = zeros( [ len( Time ) ] )
    
    for n in range( 1, N + 1, 2 ):
        Out += ( 8 / ( ( pi * n ) ** 2 ) ) * sin( ( 2 * pi * n * Frequency * Time ) + ( pi / 2 ) )
    return Out

def Sawtooth( Frequency, N, Sr, Duration ):
    Time = linspace( 0.0, Duration, int( Duration * Sr ) )
    Out = zeros( [ len( Time ) ] )
    
    for n in range( 1, N + 1 ):
        Out += ( 2 / ( pi * n ) ) * sin( ( 2 * pi * n * Frequency * Time ) )
    return Out
    

plot( PWM( 50, 0.9, 5, 44100, 0.06 ) )
plot( Triangle( 50, 5, 44100, 0.06 ) )
plot( Sawtooth( 50, 5, 44100, 0.06 ) )
show()
