function posicion=eval_net_letras(X)%,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19)

disp('evaluando letras');
	load('todaslasredes');
%X=[X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19];


	%X=[2.9713e+04,  -4.7374e+02,   2.0051e+03,  -2.6149e+03,   3.2272e+03,  -8.1204e+03,   3.1763e+03,   3.0177e+03,   2.4687e+03,  -1.4006e+03,   2.4377e+03,   6.8578e+02,  -8.0483e+02,  -1.2209e+03,  -9.5363e+02,  -5.8240e+02,  -8.5046e+02,   2.5811e+02,   1.0936e+03,   1.3279e+02];
	[mTestInput] = trastd(X',cMeanInput,cStdInput);
    
       [simOut] = sim(netLetras,mTestInput);  	  
	[patata, posicion]=max(simOut);

end
