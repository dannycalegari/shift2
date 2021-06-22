/* interface.cc */
/*
   interactive mouse and keyboard driven environments
*/

void user_interface(){
	bool finished;
	bool rays;
	point p;
	cpx c;
	
	c=0.5;

	rays=false;
	draw_mandelbrot(rays);
	draw_julia(c,rays);	
	draw_lamination(bottcher(c));
	draw_mandelbrot(rays);
	
	finished=false;
	
	while(finished==false){			
		XNextEvent(display, &report);
		switch(report.type) {
			case ButtonPress:	
				p=mouse_location();
				c=p_to_cpx(p);
				draw_julia(c,rays);	
				draw_lamination(bottcher(c));

				break;
			case KeyPress:
			 //   erase_field();
			 	if(XLookupKeysym(&report.xkey, 0) == XK_q){ // quit           
                    finished=true;
                    XCloseDisplay(display);
                    cout << "Quitting program. \n";
                    exit(0);                
                    break;
                } else if(XLookupKeysym(&report.xkey, 0) == XK_r){ 
                	rays=1-rays;
					draw_mandelbrot(rays);
					draw_julia(c,rays);
					draw_lamination(bottcher(c));
                } else if(XLookupKeysym(&report.xkey, 0) == XK_Left){ 

                } else if(XLookupKeysym(&report.xkey, 0) == XK_Right){ 

                } else if(XLookupKeysym(&report.xkey, 0) == XK_Up){ 
   
                } else if(XLookupKeysym(&report.xkey, 0) == XK_Down){ 
  
                } 
            default:
            	break;
        };
    };
};
