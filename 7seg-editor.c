#include <inttypes.h>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

#define ZOOM	8

#define A	0
#define B	1
#define C	2
#define D	3
#define E	4
#define F	5
#define G	6
#define DP	7

void put_seg(int seg, int clear);

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
// 				put_px(x+x_off, y+y_off, 0, 0, 0);
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
// 				put_px(x+x_off, y+y_off, 0, 0, 0);
			}			
		}
	}
}


void clear_segs() {
	put_seg(A, 1);
	put_seg(B, 1);
	put_seg(C, 1);
	put_seg(D, 1);
	put_seg(E, 1);
	put_seg(F, 1);
	put_seg(G, 1);
	
	return;
}	

void putn(int n) {
	clear_segs();
	
	switch(n) {
		case 0:
			put_seg(A, 0);
			put_seg(B, 0);
			put_seg(C, 0);
			put_seg(D, 0);
			put_seg(E, 0);
			put_seg(F, 0);
			break;
		case 1:
			put_seg(B, 0);
			put_seg(C, 0);
			break;
		case 2:
			put_seg(A, 0);
			put_seg(B, 0);
			put_seg(D, 0);
			put_seg(E, 0);
			put_seg(G, 0);
			break;
		case 3:
			put_seg(A, 0);
			put_seg(B, 0);
			put_seg(C, 0);
			put_seg(D, 0);
			put_seg(G, 0);
			break;
		case 4:
			put_seg(B, 0);
			put_seg(C, 0);
			put_seg(F, 0);
			put_seg(G, 0);
			break;
		case 5:
			put_seg(A, 0);
			put_seg(C, 0);
			put_seg(D, 0);
			put_seg(F, 0);
			put_seg(G, 0);
			break;
		case 6:
			put_seg(A, 0);
			put_seg(C, 0);
			put_seg(D, 0);
			put_seg(E, 0);
			put_seg(F, 0);
			put_seg(G, 0);
			break;
		case 7:
			put_seg(A, 0);
			put_seg(B, 0);
			put_seg(C, 0);
			break;
		case 8:
			put_seg(A, 0);
			put_seg(B, 0);
			put_seg(C, 0);
			put_seg(D, 0);
			put_seg(E, 0);
			put_seg(F, 0);
			put_seg(G, 0);
			break;
		case 9:
			put_seg(A, 0);
			put_seg(B, 0);
			put_seg(C, 0);
			put_seg(D, 0);
			put_seg(F, 0);
			put_seg(G, 0);
			break;
		case 0xA:
			put_seg(A, 0);
			put_seg(B, 0);
			put_seg(C, 0);
			put_seg(E, 0);
			put_seg(F, 0);
			put_seg(G, 0);
			break;
		case 0xB:
			put_seg(C, 0);
			put_seg(D, 0);
			put_seg(E, 0);
			put_seg(F, 0);
			put_seg(G, 0);
			break;
		case 0xC:
			put_seg(A, 0);
			put_seg(D, 0);
			put_seg(E, 0);
			put_seg(F, 0);
			break;
		case 0xD:
			put_seg(B, 0);
			put_seg(C, 0);
			put_seg(D, 0);
			put_seg(E, 0);
			put_seg(G, 0);
			break;
		case 0xE:
			put_seg(A, 0);
			put_seg(D, 0);
			put_seg(E, 0);
			put_seg(F, 0);
			put_seg(G, 0);
			break;
		case 0xF:
			put_seg(A, 0);
			put_seg(E, 0);
			put_seg(F, 0);
			put_seg(G, 0);
			break;
	}
}



void put_seg(int seg, int clear) {
	uint8_t r = 255;
	uint8_t g = 0;
	uint8_t b = 0;
	int x, y;
	
	if(clear) { g = b = 0; r = 75; }
	
	switch(seg) {
		case A:
			x = 4;
			y = 0;
			put_seg_h(x, y, r, g, b);
			break;
		case B:
			x = 26;
			y = 5;
			put_seg_v(x, y, r, g, b);
			break;
		case C:
			x = 26;
			y = 33;
			put_seg_v(x, y, r, g, b);
			break;
		case D:
			x = 4;
			y = 56;
			put_seg_h(x, y, r, g, b);
			break;
		case E:
			x = 0;
			y = 33;
			put_seg_v(x, y, r, g, b);
			break;
		case F:
			x = 0;
			y = 5;
			put_seg_v(x, y, r, g, b);
			break;
		case G:
			x = 4;
			y = 28;
			put_seg_h(x, y, r, g, b);
			break;
	}
}

int main() {

	SDL_Event event;
	
	int32_t quit = 0;

	if(SDL_Init (SDL_INIT_VIDEO) == -1) exit (1);
	atexit (SDL_Quit);
	screen = SDL_SetVideoMode(32*ZOOM, 64*ZOOM, 16, SDL_HWSURFACE);
	if(screen == NULL) exit (1);
	
	
	putn(0);
	
	SDL_UpdateRect (screen, 0, 0, 32*ZOOM, 64*ZOOM);
	
	int color[7] = { 1, 1, 1, 1, 1, 1, 1 };
	int num = 0;
	
	while (SDL_WaitEvent (&event) && !quit) {
		switch (event.type) {
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						quit = 1;
						break;
					case SDLK_a:
						if(color[A]) {
							color[A] = 0;
							put_seg(A, color[A]);
						} else {
							color[A] = 1;
							put_seg(A, color[A]);
						}
						break;
					case SDLK_b:
						if(color[B]) {
							color[B] = 0;
							put_seg(B, color[B]);
						} else {
							color[B] = 1;
							put_seg(B, color[B]);
						}
						break;
					case SDLK_c:
						if(color[C]) {
							color[C] = 0;
							put_seg(C, color[C]);
						} else {
							color[C] = 1;
							put_seg(C, color[C]);
						}
						break;
					case SDLK_d:
						if(color[D]) {
							color[D] = 0;
							put_seg(D, color[D]);
						} else {
							color[D] = 1;
							put_seg(D, color[D]);
						}
						break;
					case SDLK_e:
						if(color[E]) {
							color[E] = 0;
							put_seg(E, color[E]);
						} else {
							color[E] = 1;
							put_seg(E, color[E]);
						}
						break;
					case SDLK_f:
						if(color[F]) {
							color[F] = 0;
							put_seg(F, color[F]);
						} else {
							color[F] = 1;
							put_seg(F, color[F]);
						}
						break;
					case SDLK_g:
						if(color[G]) {
							color[G] = 0;
							put_seg(G, color[G]);
						} else {
							color[G] = 1;
							put_seg(G, color[G]);
						}
						break;
					case SDLK_UP:
						num++;
						if(num > 0x0F) num = 0x0F;
						putn(num);
						break;
					case SDLK_DOWN:
						num--;
						if(num < 0) num = 0;
						putn(num);
						break;
					default:
						break;
				}
				SDL_UpdateRect (screen, 0, 0, 32*ZOOM, 64*ZOOM);
				break;
		}
		
	}
	
	
	
	return 0;	
}
