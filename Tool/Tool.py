from numpy import*

# i campioni vanno generati unipolari con ampiezza di picco 1

def SampleSine( Points ):
    X = linspace( 0, 2 * pi, Points + 1 )
    return ( sin( X[ 0 : -1 ] ) / 2 ) + 0.5

def SampleSaw( Points ):
    return concatenate( [ linspace( 0, 1, int( Points / 2 ) ), linspace( 1, 0, int( Points / 2 ) + 2 )[ 1 : -1 ] ] )

def SampleSawtooth( Points ):
    return linspace( 0, 1, Points )

def FormatArrayC( Data ):
    Str = '{ '
    for X in Data: Str += str( round( X, 7 ) ) + 'f, '
    Str = Str[ 0 : -2 ]
    Str += ' };'
    return Str

print( FormatArrayC( SampleSine( 128 ) ) )
print()
print( FormatArrayC( SampleSaw( 128 ) ) )    
print()
print( FormatArrayC( SampleSawtooth( 128 ) ) )  
