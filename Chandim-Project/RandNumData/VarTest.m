M = csvread('VarTest.csv');
[m,n] = size(M);
figure;

loglog(M(:,1),M(:,3),'gd-','LineWidth',1.2);

title('Varience test for random number genrator');
%legend('CPU (sequential)','GPU (Dongryeol)','My GPU');
xlabel('Number of samples');
ylabel('Error in Varience'); 
grid on
