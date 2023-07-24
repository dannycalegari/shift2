/* green.cc */

double green(cpx z, cpx c){
	// g(z) where g is the Green's function for f_c:z -> z^2 + c
	int i, maxiter;
	cpx w;
	double T,maxsize;
	w=z;
	maxiter=50;
	maxsize=100.0;
	for(i=0;i<maxiter;i++){
		w=w*w+c;
		if(abs(w)>maxsize){
			T=log(abs(w));
			// green = T/(2^(i+1))
			return(T/pow(2.0,i+1));
		};
	};
	// exceeded maxiter; green(z) is close to 0:
	
	return(0.0);
};

void draw_green_graph(cpx c){
	int x,y,r,g;
	long col;
	double xx,yy;
	cpx z00,z10,z01,z11;
	double g00,g10,g01,g11;
	double X0,Y0,X1,Y1,X2,Y2,X3,Y3;
//	erase_field();
	
	for (x=0;x<500;x=x+1){
		xx=((double) x-250)/100.0;
		for(y=0;y<500;y=y+1){
			yy=((double) y-250)/100.0;
			z00=xx+I*yy;
			z10=z00+0.01;
			z01=z00+(0.01*I);
			z11=z01+0.01;
			g00=green(z00,c);
			g01=green(z01,c);
			g10=green(z10,c);
			g11=green(z11,c);
			
			r=255-(int) (abs(g01-g00)*6000.0);
			g=255-(int) (abs(g10-g00)*6000.0);
		//	cout << g01-g00 << " ";
			col=r+(256*g)+(256*256*255);
			
			X0=0.3+(0.866*xx)+(yy*0.866);
			Y0=(0.5*xx)-(0.5*yy)-g00*5.0;
		
			X1=0.3+(0.866*xx)+((yy+0.01)*0.866);
			Y1=(0.5*xx)-(0.5*(yy+0.01))-g01*5.0;
		
			X2=0.3+(0.866*(xx+0.01))+(yy*0.866);
			Y2=(0.5*(xx+0.01))-(0.5*yy)-g10*5.0;
			
			X3=0.3+(0.866*(xx+0.01))+((yy+0.01)*0.866);
			Y3=(0.5*(xx+0.01))-(0.5*(yy+0.01))-g11*5.0;			
			
			if(g11 < 0.25){
				if(g00==0.0){
					col=0x000000;
				};
				draw_triangle(X0,Y0,X1,Y1,X2,Y2,col);
				draw_triangle(X3,Y3,X1,Y1,X2,Y2,col);
			
				// cout << g11 << " ";
			};
			
			
		};
	};
};

void export_green_graph(cpx c){
	int x,y;
	double r,g;
	double xx,yy;
	cpx z00,z10,z01,z11;
	double g00,g10,g01,g11;
	double X0,Y0,X1,Y1,X2,Y2,X3,Y3;
	ofstream output_file;
	output_file.open("green_graph.eps");
	output_file << "%!PS-Adobe-3.0 EPSF-3.0  \n";
    output_file << "%%BoundingBox: 0 0 400 400 \n";
	output_file << "gsave 100 100 scale 1 100 div setlinewidth 1 setlinejoin 2 2 translate \n";

//	erase_field();
	
	for (x=0;x<500;x=x+1){
		xx=((double) x-250)/100.0;
		for(y=0;y<500;y=y+1){
			yy=((double) y-250)/100.0;
			z00=xx+I*yy;
			z10=z00+0.01;
			z01=z00+(0.01*I);
			z11=z01+0.01;
			g00=green(z00,c);
			g01=green(z01,c);
			g10=green(z10,c);
			g11=green(z11,c);
			
			r=1.0 - (abs(g01-g00)*23.4);
			g=1.0 - (abs(g10-g00)*23.4);
			
			X0=0.3+(0.866*xx)+(yy*0.866);
			Y0=(0.5*xx)-(0.5*yy)-g00*5.0;
		
			X1=0.3+(0.866*xx)+((yy+0.01)*0.866);
			Y1=(0.5*xx)-(0.5*(yy+0.01))-g01*5.0;
		
			X2=0.3+(0.866*(xx+0.01))+(yy*0.866);
			Y2=(0.5*(xx+0.01))-(0.5*yy)-g10*5.0;
			
			X3=0.3+(0.866*(xx+0.01))+((yy+0.01)*0.866);
			Y3=(0.5*(xx+0.01))-(0.5*(yy+0.01))-g11*5.0;			
			
			if(g11 < 0.25){
				if(g00==0.0){
					output_file << " 0 0 0 setrgbcolor \n";
				} else {
					output_file << r << " " << g << " 1 setrgbcolor \n";
				};
				output_file << "newpath \n";
				output_file << X0 << " " << Y0 << " moveto \n";
				output_file << X1 << " " << Y1 << " lineto \n";
				output_file << X3 << " " << Y3 << " lineto \n";
				output_file << X2 << " " << Y2 << " lineto closepath fill stroke \n";
//				draw_triangle(X0,Y0,X1,Y1,X2,Y2,col);
//				draw_triangle(X3,Y3,X1,Y1,X2,Y2,col);
			
				// cout << g11 << " ";
			};
			
			
		};
	};
	output_file << "grestore %eof \n";
	output_file.close();
};




