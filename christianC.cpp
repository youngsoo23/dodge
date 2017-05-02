//Created by: Christian Chavez
//Dodge project
//Individual coode
//Last Update: 4/30/2017

/*
This code is responsible for the menu functionality for the start and end of
the game. It allows the players to turn the audio on/off. 
*/

#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <ctime>
#include <fstream>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <sstream>
#include <cstring>
#include <time.h>
#include <vector>
#include "src/ppm.h"
#include "src/christianC.h"
using namespace std;

extern "C" {
#include "src/fonts.h"
}

struct Vec {
    float x, y, z;
};

struct Shape {
    float width, height;
    Vec center;
};

struct MenuBox {
    Shape box[2];
};

void player1Name(const int, const int, Input);
void getName_player1(int, Input);
void assign_namep1(char[], Input);
extern bool display_playername;
void player2Name(const int, const int, Input);
void getName_player2(int, Input);
void assign_namep2(char[], Input);
void start_menu(const int, const int);
void mode_menu(const int, const int);
void audio_menu(const int, const int);
void end_menu(const int, const int);
extern bool display_playername2;
extern bool display_modemenu;
bool entering_one = true;
bool entering_two = false;
void introMessage(const int, const int);
void gameOverScores(const int, const int, char [], char []);
extern int p1_score;
extern int p2_score;
extern bool two_player;
extern bool display_startmenu;
extern bool display_modemenu;
extern bool display_audiomenu;
extern bool display_endmenu;
extern bool display_tutorial;
extern bool show_logo;
extern bool game_over;
extern bool audio_on;
extern int menu_position;
extern GLuint silhouetteSpike;
extern int keys[];
int menu_count = 0;

unsigned int black_ = 0x000000;

void player1Name (const int xres, const int yres, Input &input)
{
    float w, h;

    MenuBox m1;
    Shape *s;

    m1.box[0].width = 100;
    m1.box[0].height = 15;
    m1.box[0].center.x = xres/2;
    m1.box[0].center.y = yres/2 + 75;
    glColor3ub(252, 246, 179);
    s = &m1.box[0];
    glPushMatrix();
    glTranslatef(s->center.x, s->center.y, 0);
    w = s->width;
    h = s->height;
    glBegin(GL_QUADS);
    glVertex2i(-w,-h);
    glVertex2i(-w, h);
    glVertex2i( w, h);
    glVertex2i( w,-h);
    glEnd();
    glPopMatrix();
    
    Rect p;
    
    p.bot = s->center.y + 30;
    p.left = s->center.x;
    p.center = s->center.y;
    ggprint13(&p, 20, black_, "Enter player1 name");

    p.bot = s->center.y - 8;
    p.left = s->center.x;
    p.center = s->center.y;
    ggprint13(&p, 20, black_, "%s", input.player1);

    
    p.bot = s->center.y - 45;
    p.left = s->center.x;
    p.center = s->center.y;
    if (!two_player) {
        ggprint13(&p, 20, black_, "Press Enter to Play!");
    } else {
        ggprint13(&p, 20, black_, "Press Enter to Continue");
    }

    if (keys[XK_Left] && menu_count != 2) {
        display_playername = false;
        display_modemenu = true;
        //menu_count = 1;
    } 
}

void getName_player1 (int key, Input &input)
{
    if (entering_one) {
        if (key >= XK_a && key <= XK_z) {
            char k[2];
            k[0] = key;
            k[1] = '\0';
            strcat(input.player1, k);
            return;
        }
        if (key == XK_BackSpace) {
            int slen = strlen(input.player1);
            if (slen > 0)
                input.player1[slen - 1] = '\0';
            return;
        }
    }
}

void assign_namep1 (char p1_name[], Input &input)
{
    for (int i = 0; i < 100; i++)
        p1_name[i] = input.player1[i];
}

void player2Name (const int xres, const int yres, Input &input)
{
    float w, h;

    MenuBox m2;
    Shape *s;

    m2.box[1].width = 100;
    m2.box[1].height = 15;
    m2.box[1].center.x = xres/2;
    m2.box[1].center.y = yres/2 + 75;
    glColor3ub(252, 246, 179);
    s = &m2.box[1];
    glPushMatrix();
    glTranslatef(s->center.x, s->center.y, 0);
    w = s->width;
    h = s->height;
    glBegin(GL_QUADS);
    glVertex2i(-w,-h);
    glVertex2i(-w, h);
    glVertex2i( w, h);
    glVertex2i( w,-h);
    glEnd();
    glPopMatrix();
    
    Rect p;
    
    p.bot = s->center.y + 30;
    p.left = s->center.x;
    p.center = s->center.y;
    ggprint13(&p, 20, black_, "Enter player2 name");

    p.bot = s->center.y - 8;
    p.left = s->center.x;
    p.center = s->center.y;
    ggprint13(&p, 20, black_, "%s", input.player2);

    p.bot = s->center.y - 45;
    p.left = s->center.x;
    p.center = s->center.y;
    ggprint13(&p, 20, black_, "Press Enter to Play!");

	if (keys[XK_Left]) {
        display_playername2 = false;
        display_playername = true;
        menu_count = 2;
	}

}

void getName_player2 (int key, Input &input)
{
    if (entering_two) {
        if (key >= XK_a && key <= XK_z) {
            char k[2];
            k[0] = key;
            k[1] = '\0';
            strcat(input.player2, k);
            return;
        }
        if (key == XK_BackSpace) {
            int slen = strlen(input.player2);
            if (slen > 0)
                input.player2[slen - 1] = '\0';
            return;
        }
    }
}

void assign_namep2 (char p2_name[], Input &input)
{
    for (int i = 0; i < 100; i++)
        p2_name[i] = input.player2[i];
}

void introMessage(const int xres, const int yres)
{
    unsigned int yellow = 0x00dddd00;
    Rect i;
    
    i.bot = yres/2 + 80;
    i.left = xres/2;
    i.center = yres/2;
    ggprint13(&i, 20, yellow, "PRESS 'm' TO START!");
}

void gameOverScores (const int xres, const int yres, char p1_name[], char p2_name[])
{
    unsigned int yellow = 0x00dddd00;
    Rect s;

    if (!two_player) {
        s.bot = yres/2 + 100;
        s.left = xres/2 - 40;
        s.center = yres/2;
        ggprint13(&s, 20, yellow, "%s's score: ", p1_name);

        s.bot = yres/2 + 100;
        s.left = xres/2 + 100;
        s.center = yres/2;
        ggprint13(&s, 20, yellow, "%i", p1_score);
    
        s.bot = yres/2 + 75;
        s.left = xres/2;
        s.center = yres/2;
        ggprint13(&s, 20, yellow, "Press c to continue");

    }

    if (two_player) {
        s.bot = yres/2 + 100;
        s.left = xres/2 - 40;
        s.center = yres/2;
        ggprint13(&s, 20, yellow, "%s's score: ", p1_name);

        s.bot = yres/2 + 100;
        s.left = xres/2 + 100;
        s.center = yres/2;
        ggprint13(&s, 20, yellow, "%i", p1_score);

        s.bot = yres/2 + 80;
        s.left = xres/2 - 40;
        s.center = yres/2;
        ggprint13(&s, 20, yellow, "%s's score: ", p2_name);

        s.bot = yres/2 + 80;
        s.left = xres/2 + 100;
        s.center = yres/2;
        ggprint13(&s, 20, yellow, "%i", p2_score);

        if (p1_score > p2_score) {
            s.bot = yres/2 + 60;
            s.left = xres/2;
            s.center = yres/2;
            ggprint13(&s, 20, yellow, "%s Wins!", p1_name);
        } else {
            s.bot = yres/2 + 60;
            s.left = xres/2;
            s.center = yres/2;
            ggprint13(&s, 20, yellow, "%s Wins!", p2_name);
        }
        
        s.bot = yres/2 + 40;
        s.left = xres/2;
        s.center = yres/2;
        ggprint13(&s, 20, yellow, "Press c to continue");
    }
}

void start_menu(const int xres, const int yres)
{
	unsigned int yellow = 0x00dddd00;
	
	Rect m;
	m.bot = yres - 200;
	m.left = xres/2 - 55;
	m.center = 0;
	ggprint13(&m, 16, yellow, "Play Game");
	ggprint13(&m, 16, yellow, "Audio Settings");
	ggprint13(&m, 16, yellow, "How to Play");

	int spike_x;
	int spike_y;

	if (menu_position == 1) {
		spike_x = xres/2 - 73;
		spike_y = yres - 190;
	} else if (menu_position == 2) {
		spike_x = xres/2 - 73;
		spike_y = yres - 207;
	} else if (menu_position == 3) {
		spike_x = xres/2 - 73;
		spike_y = yres - 224;
	}

	float w = 10.0;
	// Display spike
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glTranslatef(spike_x,spike_y,0);
	glBindTexture(GL_TEXTURE_2D, silhouetteSpike);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glColor4ub(255,255,255,255);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i( w, w);
	glTexCoord2f(1.0f, 1.0f); glVertex2i( w,-w);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(-w,-w);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(-w, w);
	glEnd();
	glPopMatrix();

	if (keys[XK_Return]) {
		if (menu_position == 1) {
			display_startmenu = false;
			display_modemenu = true;
		} else if (menu_position == 2) {
			display_startmenu = false;
			display_audiomenu = true;
			menu_position = 1;
		} else if (menu_position == 3) {
			display_startmenu = false;
			display_tutorial = true;
			show_logo = false;
		}
	}
}

void mode_menu(const int xres, const int yres)
{
	unsigned int yellow = 0x00dddd00;
	
	Rect m;
	m.bot = yres - 200;
	m.left = xres/2 - 55;
	m.center = 0;
	ggprint13(&m, 16, yellow, "1-Player");
	ggprint13(&m, 16, yellow, "2-Player");
	ggprint13(&m, 16, yellow, " ");
	
	int spike_x = xres/2 - 73;
	int spike_y = yres - 190;
	if (menu_position == 1) {
		spike_x = xres/2 - 73;
		spike_y = yres - 190;
	} else if (menu_position == 2) {
		spike_x = xres/2 - 73;
		spike_y = yres - 207;
	}
	
	float w = 10.0;
	// Display spike
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glTranslatef(spike_x,spike_y,0);
	glBindTexture(GL_TEXTURE_2D, silhouetteSpike);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glColor4ub(255,255,255,255);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i( w, w);
	glTexCoord2f(1.0f, 1.0f); glVertex2i( w,-w);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(-w,-w);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(-w, w);
	glEnd();
	glPopMatrix();

	if (keys[XK_Left] && menu_count != 1) {
		if (!game_over) {
			display_modemenu = false;
			display_startmenu = true;
			menu_position = 1;
		} else {
			display_modemenu = false;
			display_endmenu = true;
		}
    }
}

void audio_menu(const int xres, const int yres)
{
	unsigned int yellow = 0x00dddd00;
	
	Rect m;
	m.bot = yres - 200;
	m.left = xres/2 - 55;
	m.center = 0;
	ggprint13(&m, 16, yellow, "Enable Audio");
	ggprint13(&m, 16, yellow, "Disable Audio");
	ggprint13(&m, 16, yellow, " ");

	if (audio_on) {
		ggprint13(&m, 16, yellow, "Audio is currently ON!");
	} else {
		ggprint13(&m, 16, yellow, "Audio is currently OFF!");
	}
	
	int spike_x = xres/2 - 73;
	int spike_y = yres - 190;
	if (menu_position == 1) {
		spike_x = xres/2 - 73;
		spike_y = yres - 190;
	} else if (menu_position == 2) {
		spike_x = xres/2 - 73;
		spike_y = yres - 207;
	}
	
	float w = 10.0;
	// Display spike
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glTranslatef(spike_x,spike_y,0);
	glBindTexture(GL_TEXTURE_2D, silhouetteSpike);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glColor4ub(255,255,255,255);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i( w, w);
	glTexCoord2f(1.0f, 1.0f); glVertex2i( w,-w);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(-w,-w);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(-w, w);
	glEnd();
	glPopMatrix();

	if (keys[XK_Left]) {
		if (!game_over) {
			display_audiomenu = false;
			display_startmenu = true;
			menu_position = 2;
		}
		if (game_over) {
			display_audiomenu = false;
			//display_endmenu = true;
		}
	}
}

void end_menu(const int xres, const int yres)
{
	unsigned int yellow = 0x00dddd00;
	
	Rect m;
	m.bot = yres - 200;
	m.left = xres/2 - 55;
	m.center = 0;
	ggprint13(&m, 16, yellow, "Play Again");
	ggprint13(&m, 16, yellow, "Change Game Mode");
	ggprint13(&m, 16, yellow, "Audio Settings");
	ggprint13(&m, 16, yellow, "View Scores");

	int spike_x;
	int spike_y;

	if (menu_position == 1) {
		spike_x = xres/2 - 73;
		spike_y = yres - 190;
	} else if (menu_position == 2) {
		spike_x = xres/2 - 73;
		spike_y = yres - 207;
	} else if (menu_position == 3) {
		spike_x = xres/2 - 73;
		spike_y = yres - 224;
	} else if (menu_position == 4) {
		spike_x = xres/2 - 73;
		spike_y = yres - 241;
	}

	float w = 10.0;
	// Display spike
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glTranslatef(spike_x,spike_y,0);
	glBindTexture(GL_TEXTURE_2D, silhouetteSpike);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glColor4ub(255,255,255,255);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i( w, w);
	glTexCoord2f(1.0f, 1.0f); glVertex2i( w,-w);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(-w,-w);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(-w, w);
	glEnd();
	glPopMatrix();
}
