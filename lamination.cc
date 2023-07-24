/* lamination.cc */

bool link(double A, double B, double C, double D){
	// do C and D link A and B in the circle?
	double d1,d2;
	d1=(cos(C)-cos(B))*(sin(A)-sin(B))-(sin(C)-sin(B))*(cos(A)-cos(B));
	d2=(cos(D)-cos(B))*(sin(A)-sin(B))-(sin(D)-sin(B))*(cos(A)-cos(B));	
	if(d1*d2<0.0){	//linked
		return(true);
	} else {	// not linked
		return(false);
	};
};

void draw_circular_arc(double C, double B){
	double A;
	double X,Y,Z,W,cc;
	double m,n,r;
	
	// assume C > B? 
	if(C > B){
		X=C;
		Y=B;
	} else {
		X=B;
		Y=C;
	};
	// X > Y at this stage
	
	if(X > Y+PI){
		Y=Y+TWOPI;
		Z=Y;
		Y=X;
		X=Z;
	};

	A=(X-Y);	// necessarily < PI
	cc=cos(A/2.0);
	if(abs(cc)<0.001){
		draw_edge(3.3+cos(C),sin(-C)-1.3,3.3+cos(B),sin(-B)-1.3);
	} else {
		m=(1.0/cc)*cos(Y+A/2.0);
		n=(-1.0/cc)*sin(Y+A/2.0);
		r=tan(A/2.0);
	//	draw_circle(3.3+m,n-1.3,r);
		W=A+Y+PI/2.0;
		if(W>TWOPI) {
			W=W-TWOPI;
		};
		draw_arc(3.3+m,n-1.3,r,W, PI-A); // A+Y+PI/2.0 Y+(1.5*PI));
	};

	
};


void draw_preimages(double A, double B, double C, double D, int depth, double h){
	double C1,C2,D1,D2;

	if(depth==0){
		draw_edge(3.3+h*cos(C),h*sin(-C)-1.3,3.3+cos(C),sin(-C)-1.3);
		draw_circular_arc(C,D);
//		draw_edge(3.3+cos(C),sin(-C)-1.3,3.3+cos(D),sin(-D)-1.3);
		draw_edge(3.3+cos(D),sin(-D)-1.3,3.3+h*cos(D),h*sin(-D)-1.3);

		
	} else {
		draw_edge(3.3+h*cos(C),h*sin(-C)-1.3,3.3+cos(C),sin(-C)-1.3);
		draw_circular_arc(C,D);
//		draw_edge(3.3+cos(C),sin(-C)-1.3,3.3+cos(D),sin(-D)-1.3);
		draw_edge(3.3+cos(D),sin(-D)-1.3,3.3+h*cos(D),h*sin(-D)-1.3);
		C1=C/2.0;
		C2=C1+PI;
		D1=D/2.0;
		D2=D1+PI;
		
		if(link(A,B,C1,D1)){
			draw_preimages(A,B,C1,D2,depth-1,sqrt(h));
			draw_preimages(A,B,C2,D1,depth-1,sqrt(h));
		} else {
			draw_preimages(A,B,C1,D1,depth-1,sqrt(h));
			draw_preimages(A,B,C2,D2,depth-1,sqrt(h));
		};
	};
};

void draw_lamination(cpx b){
	// draw quadratic lamination with bottcher coordinate b
	if(b==0.0){
		erase_rectangle(900,0,600,1000);
		draw_circle(3.3,-1.3,1.0);
		return;
	};
	int depth;
	double A,B,theta;
	theta=arg(b);
	if(theta<0){
		theta=theta+TWOPI;
	};
	A=theta/2.0;
	B=A+PI;
	
	depth = 5;
	erase_rectangle(900,0,600,1000);
	draw_circle(3.3,-1.3,1.0);
	draw_preimages(A,B,A,B,depth,sqrt(abs(b)));
};