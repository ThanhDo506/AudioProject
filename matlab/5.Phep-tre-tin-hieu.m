x=audioread( 'piano.wav');
x1=x(10000:10100);
x1= [ zeros(1,20) x1   ];
plot(x1);
