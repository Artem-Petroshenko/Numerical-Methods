koshi = importdata('C:\Users\user\source\repos\NM-Lab5_sem4\NM-Lab5_sem4\Koshi.csv');
y = @(x) x.^2 .* exp(-x);
a = 1; b = 5;
h = koshi(1, 1);
num = koshi(2:2^5+1, 1);
x = a + h : h : b;
eps = [10^(-1), 10^(-2), 10^(-3), 10^(-4), 10^(-5), 10^(-6), 10^(-7), 10^(-8), 10^(-9), 10^(-10), 10^(-11), 10^(-12), 10^(-13), 10^(-14), 10^(-15)];
plot(x', num, LineWidth=1);
hold on
plot(x, y(x));
grid on
xlabel('x')
ylabel('function value')
title('численное и точное решение');
legend('Численное', 'Точное', 'Location', 'southwest');

figure
err = abs(y(x) - num');
plot(x, err);
grid on
xlabel('x')
ylabel('err')
title('График ошибки');

errors = importdata('C:\Users\user\source\repos\NM-Lab5_sem4\NM-Lab5_sem4\Error.csv');
local2 = errors(:, 1);
global2 = errors(:, 2);
h = errors(:, 3);
figure
loglog(h, local2);
hold on
loglog(h, global2);
hold on
loglog(h, h.^4);
hold on
loglog(h, h.^3);
grid on
xlabel('h')
ylabel('error')
title('зависимость погрешностей от шага');
legend('Локальная', 'Глобальная', 'h^4', 'h^3', 'Location', 'southeast');

sol = importdata('C:\Users\user\source\repos\NM-Lab5_sem4\NM-Lab5_sem4\pert.csv');
pert = [1, 0.1, 0.01, 10^(-3), 10^(-4), 10^(-5),  10^(-6), 10^(-7), 10^(-8), 10^(-9), 10^(-10)];
err = abs(sol' - y(b));
figure
loglog(pert, err(1:2:21));
hold on
loglog(pert, err(2:2:22));
grid on
xlabel('порядок возмущения')
ylabel('погрешность')
title('зависимость погрешности от возмущения')
legend('отрицательное возмущение', 'положительное возмущение')