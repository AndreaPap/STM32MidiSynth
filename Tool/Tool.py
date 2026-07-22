from numpy import*
from matplotlib.pyplot import*

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

#print( FormatArrayC( SampleSine( 128 ) ) )
#print()
#print( FormatArrayC( SampleSaw( 128 ) ) )    
#print()
#print( FormatArrayC( SampleSawtooth( 128 ) ) )  

def RecursiveSine( Points ):
    Y = [0, 0]
    Cos0 = cos( pi / 10  )
    Sin0 = sin( pi / 10 )
    for Cur in range( 0, Points ):
        Out = ( 2 * Cos0 * Y[-1] ) - Y[-2] 
        if( Cur == 0 ): Out += Sin0
        Y.append( Out )
    plot(Y)
    show()

RecursiveSine( 100 )
        
