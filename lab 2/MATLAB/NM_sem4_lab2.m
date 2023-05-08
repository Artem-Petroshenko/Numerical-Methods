f = @(x) 0.5.^x + 1 - (x - 2).^2;
der2_f = @(x) log(0.5) * log(0.5) * 0.5^x - 2; 
a = -6; b = 6;
File1 = fopen('sem4\lab2\datapoints.csv', 'w');
File2 = fopen('sem4\lab2\xx.csv', 'w');
xx = linspace(a, b, 1000);
fprintf(File2, '%0.20d ', xx);
File3 = fopen('sem4\lab2\nodes.csv', 'w');
File4 = fopen('sem4\lab2\derivatives.csv', 'w');
a_der = der2_f(a);
b_der = der2_f(b);
fprintf(File4, '%0.20d %0.20d\n', a_der, b_der);
k = 0;
for n = 3:3:60 
    k = k+1;
    x_i = linspace (a, b, n+1);
    y_i = f(x_i);
    fprintf(File1, '%d', n+1);
    fprintf(File1, '\n');
    fprintf(File1, '%0.20d ', x_i);
    fprintf(File1, '\n');
    fprintf(File1, '%0.20d ', y_i);
    fprintf(File1, '\n');
end
fprintf(File3, '%d', k);
fclose('all');
%% Part 2: Putting an error in extra conditions
File5 = fopen('sem4\lab2\der_error.csv', 'w');
File6 = fopen('sem4\lab2\datapoints2.csv', 'w');
n = 30;
x_i = linspace (a, b, n+1);
y_i = f(x_i);
fprintf(File6, '%d', n+1);
fprintf(File6, '\n');
fprintf(File6, '%0.20d ', x_i);
fprintf(File6, '\n');
fprintf(File6, '%0.20d ', y_i);
fprintf(File6, '\n');
for j = -5 : 5
    a_der = der2_f(a) * (1 + rand() * 10^j);
    b_der = der2_f(b) * (1 + rand() * 10^j);
    fprintf(File5, '%0.20d %0.20d\n', a_der, b_der);
end
fclose('all');