M = csvread('CQperf.csv');
[m,n] = size(M);
figure;


    semilogx(M(:,1),M(:,2),'rd--','LineWidth',1.2);
    hold on;

    semilogx(M(:,1),M(:,3),'bd-','LineWidth',1.2);
title('Performance of Calender Queue');

xlabel('N');
ylabel('Time in \mu Seconds'); 
grid on
