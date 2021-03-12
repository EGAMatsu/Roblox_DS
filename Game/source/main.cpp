/*---------------------------------------------------------------------------------
	
	Box test to demonstrate 3D bounding box es.  also shows the effect of culling and
	clipping on vertex usage
*--------------------------------------------------------------------------------*/

#include <fat.h>

#include <nds.h>
#include <maxmod9.h>
#include "nitrofs.h"

#include "soundbank.h"
#include "soundbank_bin.h"

#include <stdio.h>

#include "GML.hpp"

#include <time.h>

#include <nf_lib.h>

//some code for profiling
//---------------------------------------------------------------------------------
u16 startTimer(int timer) {
//---------------------------------------------------------------------------------

	TIMER_CR(timer) = 0;
	TIMER_DATA(0) = 0;
	TIMER_CR(timer) = TIMER_DIV_1 | TIMER_ENABLE;
	return TIMER_DATA(0);
}

#define getTimer(timer) (TIMER_DATA(timer))

//---------------------------------------------------------------------------------
//draws a box...same signature as boxTest
//---------------------------------------------------------------------------------
void DrawSkyBox(float x, float y, float z, float width, float height, float depth, float r, float g, float b) {
//---------------------------------------------------------------------------------
	glBegin(GL_QUADS);
	
	float scale=1;

	width=(width) / scale;
	height=(height) / scale;
	depth=(depth) / scale;
	
	x=x / scale;
	y=y / scale;
	z=z / scale;
	
	//z  face
	glColor3f(r,g,b);
	glVertex3f(x , y , z );
	glVertex3f(x + width, y , z );
	glVertex3f(x + width, y + height, z );
	glVertex3f(x , y + height, z );

	//z + depth face
	glColor3f(r,g,b);
	glVertex3f(x , y , z + depth);
	glVertex3f(x , y + height, z + depth);
	glVertex3f(x + width, y + height, z + depth);
	glVertex3f(x + width, y , z + depth);


	//x  face
	glColor3f(r,g,b);
	glVertex3f(x , y , z );
	glVertex3f(x , y + height, z );
	glVertex3f(x , y + height, z + depth);
	glVertex3f(x , y , z + depth);

	//x + width face
	glColor3f(r,g,b);
	glVertex3f(x + width, y , z );
	glVertex3f(x + width, y , z + depth);
	glVertex3f(x + width, y + height, z + depth);
	glVertex3f(x + width, y + height, z );

	//y  face
	glColor3f(r,g,b);
	glVertex3f(x , y , z );
	glVertex3f(x , y , z + depth);
	glVertex3f(x + width, y , z + depth);
	glVertex3f(x + width, y , z );

	//y  + height face
	glColor3f(r,g,b);
	glVertex3f(x , y + height, z );
	glVertex3f(x + width, y + height, z );
	glVertex3f(x + width, y + height, z + depth);
	glVertex3f(x , y + height, z + depth);

	glEnd();

}

//---------------------------------------------------------------------------------
//draws a box...same signature as boxTest
//---------------------------------------------------------------------------------
void DrawBox(float x, float y, float z, float width, float height, float depth, float r, float g, float b) {
//---------------------------------------------------------------------------------
	glBegin(GL_QUADS);
	
	float scale=12;

	width=(width) / scale;
	height=(height) / scale;
	depth=(depth) / scale;
	
	x=x / scale;
	y=y / scale;
	z=z / scale;
	
	//z  face
	glColor3f(r/1.15/256,g/1.15/256,b/1.15/256);
	glVertex3f(x , y , z );
	glVertex3f(x + width, y , z );
	glVertex3f(x + width, y + height, z );
	glVertex3f(x , y + height, z );

	//z + depth face
	glColor3f(r/2/256,g/2/256,b/2/256);
	glVertex3f(x , y , z + depth);
	glVertex3f(x , y + height, z + depth);
	glVertex3f(x + width, y + height, z + depth);
	glVertex3f(x + width, y , z + depth);


	//x  face
	glColor3f(r/1.25/256,g/1.25/256,b/1.25/256);
	glVertex3f(x , y , z );
	glVertex3f(x , y + height, z );
	glVertex3f(x , y + height, z + depth);
	glVertex3f(x , y , z + depth);

	//x + width face
	glColor3f(r/1.25/256,g/1.25/256,b/1.25/256);
	glVertex3f(x + width, y , z );
	glVertex3f(x + width, y , z + depth);
	glVertex3f(x + width, y + height, z + depth);
	glVertex3f(x + width, y + height, z );

	//y  face
	glColor3f(r/2.25/256,g/2.25/256,b/2.25/256);
	glVertex3f(x , y , z );
	glVertex3f(x , y , z + depth);
	glVertex3f(x + width, y , z + depth);
	glVertex3f(x + width, y , z );

	//y  + height face
	glColor3f(r/256,g/256,b/256);
	glVertex3f(x , y + height, z );
	glVertex3f(x + width, y + height, z );
	glVertex3f(x + width, y + height, z + depth);
	glVertex3f(x , y + height, z + depth);

	glEnd();

}

		float speed = 0.1;
		float total_speed_x = 0;
		float total_speed_y = 0; //a
		float total_speed_z = 0;
		
		u8 secs=0;
		float fps=0;
		
		int screenTouch=0;
		
		float language=0;

//---------------------------------------------------------------------------------
int main(int argc, char **argv) {	
//---------------------------------------------------------------------------------

	bool fatInited = fatInitDefault();
	bool nitroFSInited = nitroFSInit(argv[0]);
	
	bool dlp_demo = true;

if (!dlp_demo) {
	
if (!fatInited && !nitroFSInited) {
		consoleDemoInit();
		
		iprintf("ERR.CODE = 0002\nI hate to break this to ya,\nbut you cant use whatever you are using\nto emulate this game or run it.\nplease use a valid r4 or no$gba ver.\n\n\nfor no$gba, use the debug ver.");
		
		while (1) { swiWaitForVBlank(); }
	}

if (!fatInited) {
		consoleDemoInit();
		
		iprintf("ERR.CODE = 0000\nI hate to break this to ya,\nbut you cant use whatever you are using\nto emulate this game or run it.\nplease use a valid r4 or no$gba ver.\n\n\nfor no$gba, use the debug ver.");
		
		while (1) { swiWaitForVBlank(); }
	}

	if (!nitroFSInited) {
		consoleDemoInit();
		
		iprintf("ERR.CODE = 0001\nI hate to break this to ya,\nbut you cant use whatever you are using\nto emulate this game or run it.\nplease use a valid r4 or no$gba ver.\n\n\nfor no$gba, use the debug ver.");
		
		while (1) { 
		swiWaitForVBlank();}
	}
	
}
	

	//mmInitDefault( (char*)soundbank_bin );
	mmInitDefaultMem((mm_addr)soundbank_bin);
	//mmInitDefault( "soundbank.bin" );
	
	//mmLoad( MOD_BZPIF );
	//mmStart( MOD_BZPIF, MM_PLAY_LOOP );

mmLoadEffect(SFX_BUTTON);
mmLoadEffect(SFX_SWITCH3);

mm_sound_effect sound;
sound.id      = SFX_BUTTON; // sample ID (make sure it is loaded)
sound.rate    = 1024;     // playback rate, 1024 = original sound
sound.handle  = 0;           // 0 = allocate new handle
sound.volume  = 255;         // 200/255 volume level
sound.panning = 128;         // centered panning

mm_sound_effect oof;
oof.id      = SFX_UUHHH; // sample ID (make sure it is loaded)
oof.rate    = 1024;     // playback rate, 1024 = original sound
oof.handle  = 0;           // 0 = allocate new handle
oof.volume  = 255;         // 200/255 volume level
oof.panning = 128;         // centered panning

mm_sound_effect levitate;
levitate.id      = SFX_SWITCH3; // sample ID (make sure it is loaded)
levitate.rate    = 1024;     // playback rate, 1024 = original sound
levitate.handle  = 0;           // 0 = allocate new handle
levitate.volume  = 255;         // 200/255 volume level
levitate.panning = 128;         // centered panning



	switch (NF_GetLanguage()) {
		case 0 : // Japanese
			language=0;
			break;
		case 1 : // English
			language=1;
			break;
		case 2 : // French
			language=2;
			break;
		case 3 : // German
			language=3;
			break;
		case 4 : // Italian
			language=4;
			break;
		case 5 : // Spanish
			language=5;
			break;
		case 6 : // Chinese
			language=6;
			break;
		default:
			language=0;
			break;
	}

	touchPosition touchXY;

//put 3D on top
	
	lcdMainOnTop();

	//setup the sub screen for basic printing
	consoleDemoInit();

	// Setup the Main screen for 3D 
	videoSetMode(MODE_0_3D);

	// initialize gl
	glInit();
	
	// enable antialiasing
	//glEnable(GL_ANTIALIAS);
	
	// setup the rear plane
	glClearColor(0,0,0,31); // BG must be opaque for AA to work
	glClearPolyID(63); // BG must have a unique polygon ID for AA to work
	glClearDepth(0x7FFF);
	
	// Set our view port to be the same size as the screen
	glViewport(0,0,255,191);
	
	//camera
	float rotX = 0, rotY = 0;
	float translate = -5;

	//some profiling code
	u16 time;

	//keep track of vertex ram usage.
	int polygon_count;
	int vertex_count;

	//object 
	int rx = 50, ry = 15;
	int oldx = 0, oldy = 0;

	//main loop
	while (1) {

		//process input
		scanKeys();

		touchRead(&touchXY);

		
		int held = keysHeld();
		int pressed = keysDown();
		
		if( held & KEY_UP){
			total_speed_x += lengthdir_x(speed, (-rx)-90);
			total_speed_y += lengthdir_y(speed, (-rx)-90);
		}
		
		if( held & KEY_DOWN){
			total_speed_x -= lengthdir_x(speed, (-rx)-90);
			total_speed_y -= lengthdir_y(speed, (-rx)-90);
		}
		
		if( held & KEY_LEFT){
			total_speed_x += lengthdir_x(speed, (-rx));
			total_speed_y += lengthdir_y(speed, (-rx));
		}
		
		if( held & KEY_RIGHT){
			total_speed_x -= lengthdir_x(speed, (-rx));
			total_speed_y -= lengthdir_y(speed, (-rx));
		}
		
		if( pressed & KEY_LID) {
		mmEffectEx( &oof );
		}
		
		if( pressed & KEY_L) {
		total_speed_z += .1;
		mmEffectEx( &levitate );
		}
		if( pressed & KEY_R) {
		total_speed_z -= .1;
		mmEffectEx( &levitate );
		}

		//reset x and y when user touches screen.
		if( pressed & KEY_TOUCH)  {
			oldx = touchXY.px;
			oldy = touchXY.py;
		}
		
		if( pressed & KEY_SELECT)  {
 
		/*
		if (screenTouch==-1) {
			screenTouch=1;
		}
		if (screenTouch==1) {
			screenTouch=-1;
		}
		*/
		
		screenTouch=!screenTouch;

mmEffectEx( &sound );

		}

		//if user drags then grab the delta
		if( held & KEY_TOUCH) {
			rx += touchXY.px - oldx; 
			ry += touchXY.py - oldy;
			oldx = touchXY.px;
			oldy = touchXY.py;
		}
			// setup the rear plane
	glClearColor(0,0,0,31); // BG must be opaque for AA to work
	glClearPolyID(63); // BG must have a unique polygon ID for AA to work
	glClearDepth(0x7FFF);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		
		
		gluPerspective(70, 256.0 / 192.0, 0.01, 128);
		
		//change cull mode

		// Set the current matrix to be the model matrix.
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		glCutoffDepth(0xFFFF);
		
	glLight(0, RGB15(31,31,31) , 0,				  floattov10(-1.0),		 0);
	glLight(1, RGB15(31,0,31),   0,				  floattov10(1) - 1,			 0);
	glLight(1, RGB15(31,0,31),   0,				  floattov10(1) - 1,			 0);
	glLight(2, RGB15(0,31,0) ,   floattov10(-1.0), 0,					 0);
	glLight(3, RGB15(0,0,31) ,   floattov10(1.0) - 1,  0,					 0);
	
		//handle camera
			  
		glRotateX(ry);
		glRotateY(rx);
		
		glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE);
			  	  
		//Skybox Code Here soon....
		
		glPolyFmt(POLY_ALPHA(31) | POLY_CULL_FRONT | POLY_FORMAT_LIGHT0 | POLY_FORMAT_LIGHT1 | 
			  POLY_FORMAT_LIGHT2 | POLY_FORMAT_LIGHT3| GL_ANTIALIAS);
		
		if (ry>89) {
			ry=89;
		}
		if (ry<-89) {
			ry=-89;
		}
		
		glTranslatef(total_speed_x,total_speed_z,total_speed_y);

		//move the cube
		glRotateX(0);
		glRotateY(0);

		DrawBox(-2,-1,-1,1,2,1,245.0,205.0,47.0);
		
		DrawBox(1,-1,-1,1,2,1,245.0,205.0,47.0);
		
		DrawBox(-1,-1,-1,2,2,1,13.0,105.0,171.0);
		
		DrawBox(-1,1,-1,2,1,1,245.0,205.0,47.0);
		
		DrawBox(-1,-3,-1,1,2,1,164.0,189.0,70.0);
		
		DrawBox(0,-3,-1,1,2,1,164.0,189.0,70.0);
		
		DrawBox(-32,-4,-32,64,1,64,40,127,70.0);
		
		

		swiWaitForVBlank();
		
		if (screenTouch==0) {
			lcdMainOnTop();
		}
		if (screenTouch==1) {
			lcdMainOnBottom();
		}
		
		//if (language=0) {
		if (dlp_demo) {
		printf("\x1b[0;0H       |DSBLOX: Tech Demo|\n  (DnP/Emulation Demo Version)");
		}
		if (!dlp_demo) {
		printf( "\nHow does one get map importing?" );
		}
		printf("\n\nUse the bottom screen to aim\nUse the D-PAD to move\nUse L and R to move up/down\n\nscreenTouch = %i", screenTouch);
		
		printf( "\nHow does one get map importing?" );
		
		
			
			
		//}
		//if (language=1) {
		//printf("\x1b[0;0H   |DosubuRokkusu: Tech Demo|");
		//printf("\n\nUse the bottom screen to aim\nUse the D-PAD to move\nUse L and R to move up/down");
		//}
		
		time = startTimer(0);
		int hit = BoxTestf(-1,-1,-1,2,2,2);
		//printf("\nSingle test (float): %i", 2*(getTimer(0) - time));

		time = startTimer(0);
		BoxTest(inttov16(-1),inttov16(-1),inttov16(-1),inttov16(2),inttov16(2),inttov16(2));
		//printf("\nSingle test (fixed): %i", 2*(getTimer(0) - time));

		time = startTimer(0);
		for(int i = 0; i < 64; i++)
			BoxTest(inttov16(-1),inttov16(-1),inttov16(-1),inttov16(2),inttov16(2),inttov16(2));

		while (GFX_STATUS & (1<<27)); // wait until the geometry engine is not busy

		// flush to the screen
		glFlush(0);

	}

	return 0;
}
