/* sausage.cc */

struct snode {
	int parent;
	vector<int> children;
	cpx Z;	// attaching point
};

#define sausage	vector<snode>	// [0] is root

struct mat {
	double E[3][3];
};

struct vec {
	double E[3];
};

mat scale(double T){
	mat M;
	int i,j;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if(i==j){
				M.E[i][j]=T;
			} else {
				M.E[i][j]=0.0;
			};
		};
	};
	return(M);
};

mat rotate(int A, double T){	// A is axis T is angle
	mat M;
	M=scale(1.0);	// identity matrix
	int B,C;
	B=(A+1)%3;
	C=(A+2)%3;
	M.E[B][B]=cos(T);
	M.E[B][C]=sin(T);
	M.E[C][B]=-sin(T);
	M.E[C][C]=cos(T);
	return(M);
};

vec mul(mat M, vec V){
	int i,j;
	vec W;
	for(i=0;i<3;i++){
		W.E[i]=0.0;
		for(j=0;j<3;j++){
			W.E[i]=W.E[i]+M.E[i][j]*V.E[j];
		};
	};
	return(W);
};

mat mul(mat M, mat N){
	mat O;
	int i,j,k;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			O.E[i][j]=0.0;
			for(k=0;k<3;k++){
				O.E[i][j]=O.E[i][j]+M.E[i][k]*N.E[k][j];
			};
		};
	};
	return(O);
};

vec add(vec U, vec V){
	vec W;
	int i;
	for(i=0;i<3;i++){
		W.E[i]=U.E[i]+V.E[i];
	};
	return(W);
};

void draw_sphere(double X, double Y, double Z, double R){
	draw_circle(X,Y,R);	// can jazz this up later
};

void draw_sausage(sausage S){
	int i;
	double X,Y,Z,R;
	for(i=0;i<S.size();i++){
		// compute X,Y,Z,R for S[i];
	
		draw_sphere(X,Y,Z,R);
	};
};