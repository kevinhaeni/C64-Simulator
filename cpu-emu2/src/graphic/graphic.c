/*

  bho1 - init 23.8.2015
  bho1 - change to SDL"

  Compile with  `sdl2-config --cflags --libs`
  


  --------> x
  |
  |
  |
  |
  |
  |
  \/
  
  y

  
*/


//#define MEMORY_SIZE 65536
//#define MEMORY_CELL_SIZE 8

#include <stdlib.h>
#include "SDL.h"

//#include "memory.h"
#include "cpu-util.h"
#include "graphic.h"

#include <time.h>



int sdl_init(struct _vic* vic, unsigned int x_resolution, unsigned int y_resolution);
void sdl_exit_display();
int colortable[16][3]= {
  // black
  { 0, 0, 0 },
  // White
  { 255, 255, 255 },
    // Red
  { 136, 0, 0 },
  // Cyan
  { 170, 255, 238 },
  // Violet
  { 204, 68, 204 },
   // Green
  { 0, 204, 85 },
  // Blue
	{ 0, 0, 170 },
  // Yellow
  { 238, 238, 119 },
  // Orange
	{ 221, 136, 85 },
  // Brown
	{ 102, 68, 0 },
  // Lightred
  { 255, 119, 119 },
  // Grey
	{ 51, 51, 51 },
  // Grey
	{ 119, 119, 119 },
  // Lightgreen
	{ 170, 255, 102 },
  // Lightblue
	{ 0, 136, 255 },
  // Grey
  { 187, 187, 187 }
};


void init_display(struct _vic* vic){
  srand(time(NULL));
  vic->virtual_x_resolution = 32;
  vic->virtual_y_resolution = 32;
  /* virtual_x_resolution = 200; */
  /* virtual_y_resolution = 100; */
  
  vic->x_stretch = 10;
  vic->y_stretch = 10;
  //colortable = colortablefix;
  vic->device_x_resolution = vic->x_stretch*vic->virtual_x_resolution;
  vic->device_y_resolution = vic->y_stretch*vic->virtual_y_resolution;

  vic->pixels =  malloc(sizeof(Uint32) * 640 * 480); 
  sdl_init(vic, 640, 480);
 
 SDL_RenderClear(vic->render);
 SDL_RenderCopy(vic->render, vic->texture, NULL, NULL);
 SDL_RenderPresent(vic->render);
 
 SDL_RenderDrawPoint(vic->render, 0,0);
 SDL_RenderPresent(vic->render);
}

/*
  sdl setup
*/

int sdl_init(struct _vic* vic, unsigned int x_resolution, unsigned int y_resolution){
    if (SDL_Init(SDL_INIT_VIDEO) == -1) {
	printf("Can't init SDL:  %s\n", SDL_GetError());
	exit(1);
  }
  
  atexit(SDL_Quit);

  SDL_Window *sdlWindow = SDL_CreateWindow("visuel c64 32x32 screen",
					   SDL_WINDOWPOS_UNDEFINED,
					   SDL_WINDOWPOS_UNDEFINED,
					   x_resolution, y_resolution,
					   SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
  vic->window = sdlWindow;
  SDL_Renderer *renderer = SDL_CreateRenderer(sdlWindow, -1, 0);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
  vic->render = renderer;
  SDL_Texture *sdlTexture = NULL;
  sdlTexture = SDL_CreateTexture(renderer,
				 SDL_PIXELFORMAT_ARGB8888,
				 SDL_TEXTUREACCESS_STREAMING,
				 32,32);
				 //x_resolution, y_resolution);
  vic->texture = sdlTexture;
  SDL_UpdateTexture(sdlTexture, NULL, vic->pixels, 32 * sizeof (Uint32));

}

void exit_display(){
  sdl_exit_display();
}



void draw_bitmap_memory(struct _6510_cpu* cpu, struct _vic* vic, char memory[][9]){

  int i, color, red, green, blue;
  int base = vic->videobase;
  Uint32* pixels = vic->pixels;
  for(i=base; i<base+32*32;i++){
    color = 0x0F & conv_bitstr2int(memory[i],0,7);

    red =  colortable[color][0];
    green = colortable[color][1];
    blue =  colortable[color][2];

    *pixels++ = red <<16 | green <<8 | blue | 0xff000000;
  }
  
  SDL_UpdateTexture(vic->texture, NULL, vic->pixels, 32 * sizeof (Uint32));
  //SDL_RenderClear(vic->render);

  SDL_Rect screen_rectangle;

  screen_rectangle.x = 0;
  screen_rectangle.y = 0;
  screen_rectangle.w = 400; //vic->window.w; //132;
  screen_rectangle.h = 400;
  
  //  SDL_RenderCopy(vic->render, vic->texture, NULL, NULL);
  SDL_RenderCopy(vic->render, vic->texture, NULL, &screen_rectangle);
  SDL_RenderPresent(vic->render);
  
  //  if(cpu->cycles %1000 <10){ 
  //    SDL_RenderPresent(vic->render);
  //  }

}  


void clr_screen(struct _vic* vic, char memory[][9]){
  SDL_RenderClear(vic->render);
  SDL_RenderPresent(vic->render);
}

  


void sdl_exit_display(){
  SDL_Quit();
}










