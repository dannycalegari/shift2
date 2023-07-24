/* interface.cc */
/*
   interactive mouse and keyboard driven environments
*/

void user_interface(){
	bool finished;
	bool rays;
	bool green_bool;
	point p;
	cpx c;
	double d;
	
	c=0.5;

	green_bool=false;
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
				cout << "c = " << c.real() << " + " << c.imag() << " i \n";
				draw_julia(c,rays);	
				draw_lamination(bottcher(c));

				break;
			case KeyPress:
			 //   erase_field();
			 	if(XLookupKeysym(&report.xkey, 0) == XK_q){ // quit           
                    finished=true;
                    XCloseDisplay(display);
                    cout << "Quitting program. \n";
                    if(green_bool==true){
                    	export_green_graph(c);
                    };
                    exit(0);                
                    break;
                } else if(XLookupKeysym(&report.xkey, 0) == XK_r){ 
                	rays=1-rays;
					draw_mandelbrot(rays);
					draw_julia(c,rays);
					draw_lamination(bottcher(c));
				} else if(XLookupKeysym(&report.xkey, 0) == XK_g){	// green graph
					green_bool=1-green_bool;
					if(green_bool==true){
						erase_field();
						draw_green_graph(c);
					} else {
						erase_field();
						draw_mandelbrot(rays);
						draw_julia(c,rays);
						draw_lamination(bottcher(c));				
					};
                } else if(XLookupKeysym(&report.xkey, 0) == XK_c){ // enter constant
                	cout << "enter value of c" << "\n";
                	cout << "real part: ";
                	cin >> d;
                	c.real(d);
                	cout << "imaginary part: ";
                	cin >> d;
                	c.imag(d);
 					draw_julia(c,rays);	
					draw_lamination(bottcher(c));

					break;               	            
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
