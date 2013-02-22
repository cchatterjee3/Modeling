
Mn = csvread('north.csv');
[f,x]=hist(Mn,20);
figure(2)
bar(x,f/100);

Ms = csvread('south.csv');
[f,x]=hist(Ms,20);
figure(3)
bar(x,f/100);

%bar(x,118*f/trapz(x,f));
%plot(x,g,'r');hold of


MRs = csvread('NorthGoing.csv');
figure(3)
hist(Ms,20);

bar(x,f/100);

Mn = csvread('all.csv');
[f,x]=hist(Mn,20);
figure(2)
bar(x,f/100);