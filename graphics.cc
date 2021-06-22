/*******************************************************
 * graphics.cc - sets up window stuff for main program *
 *                                                     *
 * uses standard Xlib stuff, because I'm too perverse  *
 * to use a GUI toolkit. the main reason is that       *
 * they keep upgrading to newer and newer libraries    *
 * which are not backward compatible, so that my       *
 * programs always start to break. boohoohoo.          *
 *                                                     *
 * Danny Calegari 12/17/2000                           *
 *******************************************************/

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>

Display *display;
int screen_num;
unsigned int display_width, display_height;
XEvent report;
GC gc;
Window win;
int border_width = 4;
unsigned int width, height;
XFontStruct * font;

void setup_font(void){
  //  const char * fontname = "-*-georgia-*-r-*-*-14-*-*-*-*-*-*-*";
    const char * fontname = "-*-times-*-r-*-*-16-*-*-*-*-*-*-*";

    font = XLoadQueryFont (display, fontname);
    /* If the font could not be loaded, revert to the "fixed" font. */
    if (! font) {
        font = XLoadQueryFont (display, "fixed");
        cout << "couldn't find font!\n";
    }
    XSetFont (display, gc, font->fid);
}

struct point{
	int x,y;
};

cpx p_to_cpx(point p){
	cpx z;
	z=(((double) p.x-250)/100.0) + (I*((double) 250-p.y)/100.0);
	return(z);
};

point v_to_p(double X, double Y){
	point p;
	p.x = (int) (X*200.0+500.0);
	p.y = (int) (Y*200.0+500.0);
	return(p);
};

int r_to_i(double R){
	int i;
	i = (int) (R*200.0);
	return(i);
};

void setup_graphics(void){
	display=XOpenDisplay(NULL);
	display_width = DisplayWidth(display, screen_num);
	display_height = DisplayHeight(display, screen_num);
	screen_num = DefaultScreen(display);  
	width = 1600;
	height = 500;
	win = XCreateSimpleWindow(display, RootWindow(display, screen_num), 0, 0, width, 
		height, border_width, BlackPixel(display, screen_num), WhitePixel(display, screen_num));
	XSelectInput(display, win, ExposureMask | KeyPressMask | ButtonPressMask );
	gc = DefaultGC(display, screen_num);
	XSetForeground(display, gc, BlackPixel(display, screen_num));
	XSetBackground(display, gc, WhitePixel(display, screen_num));
  	XMapWindow(display, win);
  	setup_font();
}

void erase_field(void){
	XClearWindow(display, win);
}

point mouse_location(){
//    Bool result;
    Window window_returned;
    int root_x, root_y;
    int win_x, win_y;
    unsigned int mask_return;
    point p;
    
	XQueryPointer(display, win, &window_returned,
                &window_returned, &root_x, &root_y, &win_x, &win_y,
                &mask_return);
    p.x=win_x;
    p.y=win_y;
    return(p);
};

void draw_point(int x, int y, long col){
    XSetForeground(display, gc, col);
	XDrawPoint(display, win, gc, x, y);
};

void draw_point(double X, double Y){
	point p;
	p=v_to_p(X,Y);
    XSetForeground(display, gc, 0x000000);
	XDrawPoint(display, win, gc, p.x, p.y);	
};

void draw_edge(double X1, double Y1, double X2, double Y2){
	point p1,p2;
	p1=v_to_p(X1,Y1);
	p2=v_to_p(X2,Y2);
    XSetForeground(display, gc, 0x000000);
    XSetLineAttributes(display, gc, 2, LineSolid, 1, 1);
    XDrawLine(display, win, gc, p1.x, p1.y, p2.x, p2.y);	
};


void draw_edge(double X1, double Y1, double X2, double Y2, long col){
	point p1,p2;
	p1=v_to_p(X1,Y1);
	p2=v_to_p(X2,Y2);
    XSetForeground(display, gc, col);
    XSetLineAttributes(display, gc, 2, LineSolid, 1, 1);
    XDrawLine(display, win, gc, p1.x, p1.y, p2.x, p2.y);	
};

void draw_circle(double X, double Y, double R){
	point p;
	int r;
	p=v_to_p(X,Y);
	r=r_to_i(R);
    XSetForeground(display, gc, 0x000000);
    XSetLineAttributes(display, gc, 1, LineSolid, 1, 1);
    XSetFillStyle(display, gc, FillSolid);
    XDrawArc(display, win, gc, p.x-r, p.y-r, 2*r, 2*r, 0, 23040);
};

void draw_arc(double X, double Y, double R, double alpha, double beta){
	point p;
	int r;
	int A,B;
	p=v_to_p(X,Y);
	r=r_to_i(R);
	A = (23040.0*alpha/TWOPI);
	B = (23040.0*beta/TWOPI);
    XSetForeground(display, gc, 0x000000);
    XSetLineAttributes(display, gc, 1, LineSolid, 1, 1);
    XSetFillStyle(display, gc, FillSolid);
    XDrawArc(display, win, gc, p.x-r, p.y-r, 2*r, 2*r, A, B);
};

void draw_vertex(double X, double Y){
	draw_circle(X,Y,0.05);
};

void draw_text(point p, string S, long col){
    XSetForeground(display, gc, col);
	XDrawString(display,win,gc,p.x,p.y,S.c_str(),strlen(S.c_str()));
};

void erase_rectangle(int x, int y, int width, int height){
	XSetForeground(display, gc, 0xFFFFFF);
	XFillRectangle(display, win, gc, x, y, width, height);
};