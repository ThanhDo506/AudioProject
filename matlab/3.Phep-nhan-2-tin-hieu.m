 x=audioread( 'piano.wav');

 x1=x(10000:10100);
 
 
 y=audioread( 'guitar.wav');

  y1=y(10000:10120);

 
 
x1len=length(x1);
y1len=length(y1);
if(x1len<y1len)
x1=[x1 zeros(1,y1len-x1len)];
endif;

if(x1len>y1len)
y1=[y1; zeros(1,x1len-y1len)];
endif;

for i=1:length(y1) 
  z(i)= x1(i)*y1(i);
endfor;

z=z(1:101);
plot(z);

