from numpy import*

def Table( Points ):
    Phase = linspace( 0, 2 * pi, Points, endpoint = False )
    Sine = sin( Phase )
    MaxErr = Sine[ 1 ] - Sine[ 0 ]
    print( f'Size: {Points * 4} [bytes]\nMax error: {round( MaxErr, 3 )} = {round( 20 * log10( MaxErr ), 3 )} dB' )
    
    File = open( './SineTable/SineTable.c', 'w' )
    File.write( f'''#include "SineTable.h"

const float NORM_2PI = 0.1591549f;
const uint32_t TableMask = {Points - 1};

const float Table[ {Points} ] =
{{''' )    
    Step = 0
    for Cur in range( 0, len( Sine ) ):
        if( Step == 0 ): File.write( '\n\t' )
        File.write( f'{Sine[ Cur ]:+.7f}f, ' )
        Step = ( Step + 1 ) & ( 8 - 1 )
    if( Step == 0 ): File.write( '\n' )
    File.write( '};\n\n' )
    File.write( 'float Sine( float Phase )\n{\n\treturn Table[ ( uint32_t )( Phase * NORM_2PI * TableMask ) & TableMask ];\n}' ) 
    File.close()
    
    File = open( './SineTable/SineTable.h', 'w' )
    File.write( f'''#ifndef SINE_TABLE
#define SINE_TABLE

#include "stdint.h"

extern const float PI2;
extern const uint32_t TableMask;
extern const float Table[ {Points} ];
extern float Sine( float Phase );

#endif
''' )
    File.close()

Table( 2 ** 14 )
