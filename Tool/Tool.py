from numpy import*

# i campioni vanno generati unipolari con ampiezza di picco 1

def SampleSine( Points ):
    X = linspace( 0, 2 * pi, Points + 1 )
    return ( sin( X[ 0 : -1 ] ) / 2 ) + 0.5

def FormatArrayC( Data ):
    Str = '{ '
    for X in Data: Str += str( round( X, 7 ) ) + 'f, '
    Str = Str[ 0 : -2 ]
    Str += ' };'
    return Str

print( FormatArrayC( SampleSine( 128 ) ) )
    
