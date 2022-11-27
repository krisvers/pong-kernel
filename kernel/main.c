#include <video.h>
#include <keyboard.h>

struct Entity {
	int x, y;
	int width, height;
};

struct Entity ball = {
	159, 99, 3, 3
};
struct Entity pdl = {
	10, 100, 2, 20
};
struct Entity ai = {
	309, 100, 2, 20
};

//	Characters

char chars[150] = {
	1, 1, 1,
	1, 0, 1,
	1, 0, 1,		// 0
	1, 0, 1,
	1, 1, 1,
	
	1, 1, 0,
	0, 1, 0,
	0, 1, 0,		// 1
	0, 1, 0,
	1, 1, 1,

	1, 1, 0,
	0, 0, 1,
	0, 1, 0,		// 2
	1, 0, 0,
	1, 1, 1,

	1, 1, 1,
	0, 0, 1,
	0, 1, 1,		// 3
	0, 0, 1,
	1, 1, 1,

	1, 0, 0,
	1, 0, 1,
	1, 1, 1,		// 4
	0, 0, 1,
	0, 0, 1,

	1, 1, 1,
	1, 0, 0,
	1, 1, 0,		// 5
	0, 0, 1,
	1, 1, 0,

	1, 1, 1,
	1, 0, 0,
	1, 1, 1,		// 6
	1, 0, 1,
	1, 1, 1,

	1, 1, 1,
	0, 0, 1,
	0, 1, 0,		// 7
	0, 1, 0,
	0, 1, 0,

	0, 1, 0,
	1, 0, 1,
	0, 1, 0,		// 8
	1, 0, 1,
	0, 1, 0,

	1, 1, 1,
	1, 0, 1,
	1, 1, 1,		// 9
	0, 0, 1,
	0, 0, 1,
};

void number(int x, int y, unsigned char num) {
	for (int a = 0; a < 3; a++) {
		for (int b = 0; b < 5; b++) {
			pixel_vidmem(x + a, y + b, chars[num * 15 + (b * 3) + a] * 15);
		}
	}
}

void draw(struct Entity * ent) {
	for (int y = ent->y; y < ent->height + ent->y; y++) {
		for (int x = ent->x; x < ent->width + ent->x; x++) {
			pixel_vidmem(x, y, 15);
		}
	}
}

void borders() {
	for (int x = 0; x < 320; x += 5) {
		pixel_vidmem(x, 0, 15);
		pixel_vidmem(x + 1, 0, 15);
		pixel_vidmem(x + 2, 0, 15);
		pixel_vidmem(x + 3, 0, 15);
		pixel_vidmem(x + 4, 0, 15);
		pixel_vidmem(x, 199, 15);
		pixel_vidmem(x + 1, 199, 15);
		pixel_vidmem(x + 2, 199, 15);
		pixel_vidmem(x + 3, 199, 15);
		pixel_vidmem(x + 4, 199, 15);
	}
	for (int y = 0; y < 320; y += 5) {
		pixel_vidmem(0, y, 15);
		pixel_vidmem(0, y + 1, 15);
		pixel_vidmem(0, y + 2, 15);
		pixel_vidmem(0, y + 3, 15);
		pixel_vidmem(0, y + 4, 15);
		pixel_vidmem(319, y, 15);
		pixel_vidmem(319, y + 1, 15);
		pixel_vidmem(319, y + 2, 15);
		pixel_vidmem(319, y + 3, 15);
		pixel_vidmem(319, y + 4, 15);
		pixel_vidmem(159, y, 15);
	}
}

bool collision(struct Entity * enta, struct Entity * entb) {
	return (enta->y <= entb->y && enta->y + enta->height >= entb->y) && (enta->x <= entb->x && enta->x + enta->width >= entb->x);
}

int xVel = 1; int yVel = 1;
int aScore = 0; int bScore = 0;
bool win = false;

void update() {
	clear_vidmem();

	if (ball.x < 1) {
		ball.x = 159; ball.y = 99;
		bScore++;
		xVel *= -1;
	} else if (ball.x > 318 - ball.width) {
		ball.x = 159; ball.y = 99;
		aScore++;
		xVel *= -1;
	}
	if (ball.y < 1 || ball.y > 198 - ball.height) {
		yVel *= -1;
	}

	if (aScore > 9 || bScore > 9) {
		win = true;
	}
	
	ball.x += xVel;
	ball.y += yVel;

	number(79, 10, aScore);
	number(239, 10, bScore);

	borders();
	draw(&ball);
	draw(&pdl);
	draw(&ai);
	swap_buffers();

	if (read_key_char() == 'w') {
		pdl.y--;
	} else if (read_key_char() == 's') {
		pdl.y++;
	}

//	Uncomment for double AI

	/*if (pdl.x + 67 >= ball.x) {
		if (pdl.y + 1 > ball.y) {
			pdl.y--;
		} else if (pdl.y - 1 < ball.y) {
			pdl.y++;
		}
	}*/

	if (ai.x - 65 <= ball.x) {
		if (ai.y + 1 > ball.y) {
			ai.y--;
		} else if (ai.y - 1 < ball.y) {
			ai.y++;
		}
	}

	if (pdl.y < 1) {
		pdl.y = 1;
	} else if (pdl.y > 198 - pdl.height) {
		pdl.y = 198 - pdl.height;
	}

	if (collision(&pdl, &ball) || collision(&ai, &ball)) {
		xVel *= -1;
	}

	for (int i = 0; i < 0x26FFFF; i++) {
		asm("nop");
	}
}

void main() {
	clear_vidmem();

	while (!win) {
		update();
	}
}