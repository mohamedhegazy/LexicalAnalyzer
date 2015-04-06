		int N=700;
		double x[][]=new double[N][N];
		double y[][]=new double[N][N];
		double z[][]=new double[N][N];
		z=fill(z);
		y=fill(y);
		int B=9;
	    long startTimeNano = System.nanoTime( );	    
	    for (int jj = 0; jj < N; jj = jj+B)
	    	for (int kk = 0; kk < N; kk = kk+B)
	    	for (int i = 0; i < N; i = i+1)
	    	for (int j = jj; j < Math.min(jj+B,N); j = j+1)
	    	{ double r = 0;
	    	for (int k = kk; k < Math.min(kk+B,N); k = k + 1)
	    	r = r + y[i][k]*z[k][j];
	    	x[i][j] = x[i][j] + r;
	    	};
	    long taskTimeNano  = System.nanoTime( ) - startTimeNano;