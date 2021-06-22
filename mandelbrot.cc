/* mandelbrot.cc */


void draw_mandelbrot_rays(){
	// draw quadratic julia set
	int x,y,n;
	double xx,yy;
	cpx z,c;
	bool escaped;
	for (x=0;x<400;x++){
		xx=((double) x-250)/100.0;
		for (y=0;y<500;y++){
			yy=((double) y-250)/100.0;
			z=xx+I*yy;
			c=z;
			z=0.0;
			escaped = false;
			for(n=-1;n<100;n++){
				z=z*z+c;
				if(abs(z)>100.0){
					if(arg(z)>0.0){
						draw_point(x,500-y,0x000000);
					};
					n=100;
					escaped = true;
				};
			};
			if(escaped == false){
				draw_point(x,500-y,0xFF0000);
			};
		};
	};
};

void draw_mandelbrot(bool rays){
	// draw mandelbrot set
	int x,y,n,r,g,b;
	double xx,yy;
	cpx z,c;
	long col;
	bool escaped;
	
	erase_rectangle(0,0,400,500);

	if(rays){
		draw_mandelbrot_rays();
	} else {
	for (x=0;x<400;x++){
		xx=((double) x-250)/100.0;
		for (y=0;y<500;y++){
			yy=((double) y-250)/100.0;
			z=xx+I*yy;
			c=z;
			z=0.0;
			escaped=false;
			for(n=-1;n<100;n++){
				z=z*z+c;
				if(abs(z)>4.0){
					r = 3*n;
					g = 20*n;
					b = 11*n;
					if(r>255) {
						r=255;
					};
					if(g>255) {
						g=255;
					};
					if(b>255) {
						b=255;
					};
					col=0xFFFFFF - (r*256*256 + g*256 + b);
					draw_point(x,500-y,col);
					n=100;
					escaped = true;
				};
			};
			if(escaped == false){
				draw_point(x,500-y,0x000000);
			};
		};
	};
	};
};


bool is_in_mandelbrot(cpx c){
	int n;
	cpx z;
	z=0.0;
	for(n=0;n<100;n++){
		z=z*z+c;
		if(abs(z)>4.0){
			return(false);
		};
	};
	return(true);
};


cpx iterate_poly(cpx z, cpx c, int n){
	// apply z -> z^2 + c to z a total of n times
	int i;
	cpx w;
	w=z;
	for(i=0;i<n;i++){
		w=w*w+c;
	};	
	return(w);
};


cpx bottcher(cpx c){
	// computes bottcher coordinate of c for poly z -> z^2 + c
	int i,n;
	bool escapes;
	cpx z,w,wa,wb;
	double ta,tb;
	
	escapes=false;
	z=c;
	
	for(n=1;n<10;n++){
		z=z*z+c;
		if(abs(z)>100.0){
			i=n;
			escapes=true;
			w=z;	// botcher coord of f^n(z)
			n=10;
		};
	};
	
	if(escapes==false){
		return(0.0);
	} else {
		for(n=i-1;n>=0;n--){
			wa=sqrt(w);
			wb=-wa;
			z=iterate_poly(c,c,n);
			ta=abs(wa-z);
			tb=abs(wb-z);
			if(ta < tb){
				w=wa;
			} else {
				w=wb;
			};
		};
	};
	
	return(w);
	
};

