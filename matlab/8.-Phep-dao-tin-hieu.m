 x=audioread('piano.wav');

 x1=x(10000:10100);
 
len=length(x1);
z ( len ,1);
for i=1:len
  z(len-i+1)=x1(i);
endfor;




