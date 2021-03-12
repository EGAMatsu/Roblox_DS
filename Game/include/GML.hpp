
#include <stdio.h>
#include <math.h>

float lengthdir_x( float Length, float Direction ) {
	return ( cos( -Direction*( 3.14159265/180 ) ) * Length );
}

float lengthdir_y( float Length, float Direction ) {
	return ( sin( -Direction*( 3.14159265/180 ) ) * Length );
}