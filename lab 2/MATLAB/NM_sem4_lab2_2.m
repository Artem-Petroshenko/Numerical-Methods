yy_spline = importdata('C:\Users\user\source\repos\NM-Lab2_sem4\NM-Lab2_sem4\yy.csv');
yy_lagrange = importdata('C:\Users\user\source\repos\NM-Lab1_sem4\NM-Lab1_sem4\yy.csv');
k = importdata('sem4\lab2\nodes.csv');
xx = importdata('sem4\lab2\xx.csv');
a = -6; b = 6;
f = @(x) 0.5.^x + 1 - (x - 2).^2;
for i = 1:k
subplot(2, 2, 1);
fplot(f, [a, b]);
hold on

n = 3 * i;
x_i = linspace (a, b, n+1);
y_i = f(x_i);
plot(x_i, y_i, '*g');
hold on
plot(xx, yy_spline(i, :), '--r');
grid on
legend('function', 'data', 'spline', 'location', 'bestoutside');
title(['number of nodes = ', num2str(n+1)]);
hold off

subplot(2, 2, 3);
error1 = abs(yy_spline(i, :) - f(xx));
error_max1 = max(error1);
semilogy(xx, error1);
hold on
error2 = abs(yy_lagrange(i, :) - f(xx));
error_max2 = max(error2);
semilogy(xx, error2);
hold off
title(['max spline error = ', num2str(error_max1)], ['max lagrange error = ', num2str(error_max2)]);
legend('spline', 'Lagrange');
grid on

subplot(2, 2, 2);
semilogy(n+1, error_max1, 'or');
hold on
semilogy(n+1, error_max2, 'og');
hold on
grid on
xlabel('number of nodes');
ylabel('max error');
legend('spline', 'Lagrange', 'location', 'southwest');

subplot(2, 2, 4);
h = (b-a) / n;
loglog(h, error_max1, 'or');
hold on
loglog(h, error_max2, 'og');
hold on
grid on
xlabel('length of interval');
ylabel('max error');
legend('spline', 'Lagrange', 'location', 'southwest');
pause((k-i) * 0.35)
end
figure
yy_error = importdata('C:\Users\user\source\repos\NM-Lab2_sem4\NM-Lab2_sem4\yy2.csv');
n = 30;
x_i = linspace(a, b, n+1);
y_i = f(x_i);
for j = 1 : 11
    subplot(2, 1, 1);
    fplot(f, [a, b]);
    hold on
    plot(x_i, y_i, '*g');
    hold on
    plot(xx, yy_error(j, :), '--r');
    hold off
    grid on
    title('относительная погрешность внесенной ошибки = ', num2str(10^(j - 6)));
    legend('function', 'data', 'spline', 'location', 'bestoutside')

    subplot(2, 1, 2);
    error3 = abs(yy_error(j, :) - f(xx));
    error_max3 = max(error3);
    semilogy(j - 6, error_max3, 'or');
    hold on
    grid on
    xlabel('Степень относительной погрешности ошибки');
    ylabel('Величина максимальной ошибки');
    %pause(j * 0.2);
end
