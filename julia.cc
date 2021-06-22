/* julia.cc */


void draw_julia_rays(cpx c){
	// draw quadratic julia set
	int x,y,n;
	double xx,yy;
	cpx z;
	bool escaped;
	for (x=0;x<500;x++){
		xx=((double) x-250)/100.0;
		for (y=0;y<500;y++){
			yy=((double) y-250)/100.0;
			z=xx+I*yy;
			escaped = false;
			for(n=0;n<100;n++){
				z=z*z+c;
				if(abs(z)>100.0){
					if(arg(z)>0.0){
						draw_point(x+400,500-y,0x000000);
					};
					n=100;
					escaped = true;
				};
			};
			if(escaped == false){
				draw_point(x+400,500-y,0xFF0000);
			};
		};
	};
};

void draw_julia(cpx c, bool rays){
	// draw quadratic julia set
	int x,y,n,r,g,b;
	double xx,yy;
	cpx z;
	long col;
	bool escaped;
	
	erase_rectangle(400,0,500,500);
	if(rays){
		draw_julia_rays(c);
	} else {
	for (x=0;x<500;x++){
		xx=((double) x-250)/100.0;
		for (y=0;y<500;y++){
			yy=((double) y-250)/100.0;
			z=xx+I*yy;
			escaped = false;
			for(n=0;n<100;n++){
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
					draw_point(x+400,500-y,col);
					n=100;
					escaped = true;
				};
			};
			if(escaped == false){
				draw_point(x+400,500-y,0x000000);
			};
		};
	};
	};
};



