data = importdata('C:\Users\user\source\repos\NM_Lab4_sem4\NM_Lab4_sem4\integral.csv');
integral = data(:, 1);
F = @(x) 0.5.^x / log(0.5) + x - ((x-2)^3) / 3;
a = -6; b = 6;
accurate_integral = F(b) - F(a);
error = abs(integral - accurate_integral);
splits = data(:, 2);
n = splits * 3;
h = (b-a) ./ splits;
f = @(x) log(0.5) * log(0.5) * log(0.5) * log(0.5) * 0.5.^x;
max_f = f(a);
min_f = f(b);
max_error = h.^4 / 3840 * max_f * (b-a);
min_error = h.^4 / 3840 * min_f * (b-a);
eps = [10^(-1), 10^(-2), 10^(-3), 10^(-4), 10^(-5), 10^(-6), 10^(-7), 10^(-8), 10^(-9), 10^(-10), 10^(-11), 10^(-12), 10^(-13)];
loglog(eps, error);
hold on
grid on
xlabel('accurancy')
ylabel('error')
title('зависимость погрешности от заданной точности');
loglog(eps, eps, 'k:')
hold on
loglog(eps, min_error);
hold on
loglog(eps, max_error);
legend('фактическая погрешность', 'заданная точность', 'максимальная теоретическая ошибка', 'минимальная теоретическая ошибка', 'Location', 'southeast');

figure
loglog(eps, splits);
grid on
xlabel('accurancy')
ylabel('number of splits')
title('зависимость количества разбиений от заданной точности');