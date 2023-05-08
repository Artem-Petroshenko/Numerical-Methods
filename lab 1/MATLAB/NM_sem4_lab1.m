f = @(x) 0.5.^x + 1 - (x - 2).^2;
g = @(x) abs(0.5.^x + 1 - (x - 2).^2);
a = -6; b = 6;
File1 = fopen('sem4\lab1\datapoints.csv', 'w');
File2 = fopen('sem4\lab1\abs_func_datapoints.csv', 'w');
File3 = fopen('sem4\lab1\xx.csv', 'w');
xx = linspace(a, b, 1000);
fprintf(File3, '%0.20d ', xx);
File4 = fopen('sem4\lab1\nodes.csv', 'w');
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
    fprintf(File2, '%0.20d ', abs(y_i));
    fprintf(File2, '\n');
end
fprintf(File4, '%d', k);
fclose('all');