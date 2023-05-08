yy = importdata('C:\Users\user\source\repos\NM-Lab1_sem4\NM-Lab1_sem4\yy.csv');
abs_yy = importdata('C:\Users\user\source\repos\NM-Lab1_sem4\NM-Lab1_sem4\abs_yy.csv');
yy_uniform = importdata('C:\Users\user\source\repos\NM-Lab1_sem4\NM-Lab1_sem4\yy_uniform.csv');
k = importdata('sem4\lab1\nodes.csv');
xx = importdata('sem4\lab1\xx.csv');
a = -6; b = 6;
f = @(x) 0.5.^x + 1 - (x - 2).^2;
g = @(x) abs(0.5.^x + 1 - (x - 2).^2);
for i = 1:k
subplot(2, 2, 1);
fplot(f, [a, b]);
hold on

n = i + 2;
x_i = linspace (a, b, n+1);
y_i = f(x_i);
plot(x_i, y_i, '*r');
hold on
plot(xx, yy(i, :), '--g', 'LineWidth', 2);
hold on
plot(xx, yy_uniform(i, :), '--r');
grid on
legend('function', 'data', 'general polynom', 'uniform polynom', 'location', 'bestoutside');
title(['number of nodes = ', num2str(n+1)]);
hold off

subplot(2, 2, 2);
fplot(g, [a, b]);
hold on
plot(x_i, abs(y_i), '*b');
hold on
plot(xx, abs_yy(i, :), '--r');
grid on
legend('absolute function', 'data', 'polynomial', 'location', 'bestoutside');
title(['number of nodes = ', num2str(n+1)]);
hold off

subplot(2, 2, 3);
error1 = abs(yy(i, :) - f(xx));
error_max1 = max(error1);
semilogy(xx, error1, 'LineWidth', 1.5);
hold on
error2 = abs(abs_yy(i, :) - g(xx));
error_max2 = max(error2);
semilogy(xx, error2);
hold on
error3 = abs(yy_uniform(i, :) - f(xx));
error_max3 = max(error3);
semilogy(xx, error3);
hold off
title(['max error of f = ', num2str(error_max1)], ['max error of uniform f = ', num2str(error_max3)]);
legend('original function', 'absolute function', 'uniform function');
grid on

subplot(2, 2, 4);
semilogy(n+1, error_max1, 'or', 'LineWidth', 1.5);
hold on
semilogy(n+1, error_max2, 'ob');
hold on
semilogy(n+1, error_max3, 'og');
grid on
xlabel('number of nodes');
ylabel('max error');
legend('original function', 'absolute function', 'uniform function', 'location', 'southwest');
pause((k - i) * 0.05);
end