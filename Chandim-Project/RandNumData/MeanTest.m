M = csvread('MeanTest.csv');
[m,n] = size(M);
figure;

loglog(M(:,1),M(:,3),'b^-','LineWidth',1.2);

title('Mean test for random number genrator');
%legend('CPU (sequential)','GPU (Dongryeol)','My GPU');
xlabel('Number of samples');
ylabel('Error in mean'); 
grid on
