x=audioread( 'resources/wav/piano.wav');

 x1=x(10000:10100);

y=audioread( 'resources/wav/guitar.wav');
  y1=y(10000:10120);
  
  x1len=length(x1);
y1len=length(y1);

for i=1:x1len
  c(x1len-i+1)=x1(i);
endfor;
x1=c;

for i=1:x1len 
  for j= 1:y1len
    z(i,j) = x1(i)*y1(j); 
  endfor;
 endfor;
 
 a= zeros(1,x1len+y1len-1);
 
 for k= 1: x1len+y1len-1
   for i=1:x1len
      for j= 1:y1len
          if(i+j-1==k)
              a(k)= a(k)+z(i,j);
          endif;
       endfor;
   endfor;
 endfor;
 
 plot(a);