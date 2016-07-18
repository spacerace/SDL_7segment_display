#include <inttypes.h>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

#define ZOOM	4

#define SIZE_X  1024
#define SIZE_Y  ((64*ZOOM*2)+58)

#define A	0
#define B	1
#define C	2
#define D	3
#define E	4
#define F	5
#define G	6
#define DP	7

void put_seg(int seg, int x_off, int y_off);

uint8_t _r = 255;
uint8_t _g = 0;
uint8_t _b = 0;

SDL_Surface *screen;

uint32_t segment_h[6] = { 0x003ffffc, 0x007ffffe, 0x00ffffff, 0x00ffffff, 0x007ffffe, 0x003ffffc };
uint8_t segment_v[24] = { 0x0c, 0x1e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
			  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1e, 0x0c };

void put_px(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
	int x1 = x * ZOOM;
	int y1 = y * ZOOM;
	int x2 = x1 + ZOOM;
	int y2 = y1 + ZOOM;
	
	boxRGBA (screen, x1, y1, x2, y2, r, g, b, 0xff);
	
	return;	
}

void put_seg_h(int x_off, int y_off, uint8_t r, uint8_t g, uint8_t b) {
	int x = 0;
	int y = 0;
	
	for(y = 0; y < 6; y++) {
		for(x = 0; x <= 23; x++) {
			if((segment_h[y] >> x)&0x01) {
				put_px(x+x_off, y+y_off, r, g, b);
			} else {
//  				put_px(x+x_off, y+y_off, 38, 0, 0);
			}
		}
	}	
}

void put_seg_v(int x_off, int y_off, uint8_t r, uint8_t g, uint8_t b) {
	int x = 0;
	int y = 0;
	
	for(y = 0; y <= 23; y++) {
		for(x = 0; x < 6; x++) {
			if((segment_v[y] >> x)&0x01) {
				put_px(x+x_off, y+y_off, r, g, b);
			} else {
//  				put_px(x+x_off, y+y_off, 38, 0, 0);
			}			
		}
	}
}
void clear_all() {
	boxRGBA (screen, 0, 0, SIZE_X, SIZE_Y, 0, 0, 0, 255);
	SDL_UpdateRect (screen, 0, 0, SIZE_X, SIZE_Y);
	
	return;
}

void clear_segs() {
	uint8_t r_save = _r;
	_r = 38;
	
	
	putn(8, 0, 0);
	putn(8, 1, 0);
	putn(8, 2, 0);
	putn(8, 3, 0);
	putn(8, 4, 0);
	putn(8, 5, 0);
	putn(8, 6, 0);

	putn(8, 0, 1);
	putn(8, 1, 1);
	putn(8, 2, 1);
	putn(8, 3, 1);
	putn(8, 4, 1);
	putn(8, 5, 1);
	putn(8, 6, 1);
	
	_r = r_save;
	
	return;
}
	

void putn(int n, int pos, int line) {	
	const int seg_pos[7] = { 0, 36, 72, 108, 152, 188, 224 };
	const int line_start[2] = { 0, 80 };
	
	int x_off = seg_pos[pos];
	int y_off = line_start[line];
	
	switch(n) {
		case 0:
			put_seg(A, x_off, y_off);
			put_seg(B, x_off, y_off);
			put_seg(C, x_off, y_off);
			put_seg(D, x_off, y_off);
			put_seg(E, x_off, y_off);
			put_seg(F, x_off, y_off);
			break;
		case 1:
			put_seg(B, x_off, y_off);
			put_seg(C, x_off, y_off);
			break;
		case 2:
			put_seg(A, x_off, y_off);
			put_seg(B, x_off, y_off);
			put_seg(D, x_off, y_off);
			put_seg(E, x_off, y_off);
			put_seg(G, x_off, y_off);
			break;
		case 3:
			put_seg(A, x_off, y_off);
			put_seg(B, x_off, y_off);
			put_seg(C, x_off, y_off);
			put_seg(D, x_off, y_off);
			put_seg(G, x_off, y_off);
			break;
		case 4:
			put_seg(B, x_off, y_off);
			put_seg(C, x_off, y_off);
			put_seg(F, x_off, y_off);
			put_seg(G, x_off, y_off);
			break;
		case 5:
			put_seg(A, x_off, y_off);
			put_seg(C, x_off, y_off);
			put_seg(D, x_off, y_off);
			put_seg(F, x_off, y_off);
			put_seg(G, x_off, y_off);
			break;
		case 6:
			put_seg(A, x_off, y_off);
			put_seg(C, x_off, y_off);
			put_seg(D, x_off, y_off);
			put_seg(E, x_off, y_off);
			put_seg(F, x_off, y_off);
			put_seg(G, x_off, y_off);
			break;
		case 7:
			put_seg(A, x_off, y_off);
			put_seg(B, x_off, y_off);
			put_seg(C, x_off, y_off);
			break;
		case 8:
			put_seg(A, x_off, y_off);
			put_seg(B, x_off, y_off);
			put_seg(C, x_off, y_off);
			put_seg(D, x_off, y_off);
			put_seg(E, x_off, y_off);
			put_seg(F, x_off, y_off);
			put_seg(G, x_off, y_off);
			break;
		case 9:
			put_seg(A, x_off, y_off);
			put_seg(B, x_off, y_off);
			put_seg(C, x_off, y_off);
			put_seg(D, x_off, y_off);
			put_seg(F, x_off, y_off);
			put_seg(G, x_off, y_off);
			break;
		case 0xA:
			put_seg(A, x_off, y_off);
			put_seg(B, x_off, y_off);
			put_seg(C, x_off, y_off);
			put_seg(E, x_off, y_off);
			put_seg(F, x_off, y_off);
			put_seg(G, x_off, y_off);
			break;
		case 0xB:
			put_seg(C, x_off, y_off);
			put_seg(D, x_off, y_off);
			put_seg(E, x_off, y_off);
			put_seg(F, x_off, y_off);
			put_seg(G, x_off, y_off);
			break;
		case 0xC:
			put_seg(A, x_off, y_off);
			put_seg(D, x_off, y_off);
			put_seg(E, x_off, y_off);
			put_seg(F, x_off, y_off);
			break;
		case 0xD:
			put_seg(B, x_off, y_off);
			put_seg(C, x_off, y_off);
			put_seg(D, x_off, y_off);
			put_seg(E, x_off, y_off);
			put_seg(G, x_off, y_off);
			break;
		case 0xE:
			put_seg(A, x_off, y_off);
			put_seg(D, x_off, y_off);
			put_seg(E, x_off, y_off);
			put_seg(F, x_off, y_off);
			put_seg(G, x_off, y_off);
			break;
		case 0xF:
			put_seg(A, x_off, y_off);
			put_seg(E, x_off, y_off);
			put_seg(F, x_off, y_off);
			put_seg(G, x_off, y_off);
			break;
	}
}



void put_seg(int seg, int x_off, int y_off) {
	int x, y;
	
	switch(seg) {
		case A:
			x = x_off + 4;
			y = y_off + 0;
			put_seg_h(x, y, _r, _g, _b);
			break;
		case B:
			x = x_off + 26;
			y = y_off + 5;
			put_seg_v(x, y, _r, _g, _b);
			break;
		case C:
			x = x_off + 26;
			y = y_off + 33;
			put_seg_v(x, y, _r, _g, _b);
			break;
		case D:
			x = x_off + 4;
			y = y_off + 56;
			put_seg_h(x, y, _r, _g, _b);
			break;
		case E:
			x = x_off + 0;
			y = y_off + 33;
			put_seg_v(x, y, _r, _g, _b);
			break;
		case F:
			x = x_off + 0;
			y = y_off + 5;
			put_seg_v(x, y, _r, _g, _b);
			break;
		case G:
			x = x_off + 4;
			y = y_off + 28;
			put_seg_h(x, y, _r, _g, _b);
			break;
	}
}

int main() {

	SDL_Event event;
	
	int32_t quit = 0;

	if(SDL_Init (SDL_INIT_VIDEO) == -1) exit (1);
	atexit (SDL_Quit);
	screen = SDL_SetVideoMode(SIZE_X, SIZE_Y, 16, SDL_HWSURFACE);
	if(screen == NULL) exit (1);
	
	clear_all();
	clear_segs();
	
	putn(1, 0, 0);
	putn(2, 1, 0);
	putn(7, 2, 0);
	putn(3, 3, 0);
	putn(0, 4, 0);
	putn(3, 5, 0);
	putn(5, 6, 0);

	putn(2, 0, 1);
	putn(4, 1, 1);
	putn(8, 2, 1);
	putn(0, 3, 1);
	putn(5, 4, 1);
	putn(3, 5, 1);
	putn(9, 6, 1);
	
	
	SDL_UpdateRect (screen, 0, 0, SIZE_X, SIZE_Y);
	
	while (SDL_WaitEvent (&event) && !quit) {
		switch (event.type) {
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						quit = 1;
						break;
					case SDLK_UP:
						break;
					case SDLK_DOWN:
						break;
					default:
						break;
				}
				SDL_UpdateRect (screen, 0, 0, 1024, 64*ZOOM*3);
				break;
		}
		
	}
	
	
	
	return 0;	
}
