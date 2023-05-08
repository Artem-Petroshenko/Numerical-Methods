num_solution = importdata('C:\Users\user\source\repos\NM-Lab7_sem4\NM-Lab7_sem4\y.csv');
a = 0; b = 1;
y = @(x) exp(x) - 1;
n = 5;
h = (b - a) / n;
x = a : h : b;
plot(x, num_solution);
hold on
plot(x, y(x));
grid on
xlabel('x')
ylabel('function value')
title('численное и точное решение');
legend('Численное', 'Точное', 'Location', 'northwest');

figure
err = abs(num_solution' - y(x));
plot(x, err);
grid on
xlabel('x')
ylabel('err')
title('График ошибки');

Y = importdata('C:\Users\user\source\repos\NM-Lab7_sem4\NM-Lab7_sem4\err.csv');
figure
for i = 1:491
    num_solution = Y(i, 1:501-(i-1));
    H(i) = (b - a) / (500-(i-1));
    x = a : H(i) : b;
    e = abs(num_solution - y(x));
    error(i) = norm(e, 'inf');
end
loglog(H, error);
grid on
xlabel('h')
ylabel('error')
title('Зависимость погрешности от шага');

Pertubation = importdata('C:\Users\user\source\repos\NM-Lab7_sem4\NM-Lab7_sem4\pertubation.csv');
pert = [1, 0.1, 0.01, 10^(-3), 10^(-4), 10^(-5),  10^(-6), 10^(-7), 10^(-8), 10^(-9), 10^(-10)];
n = 10;
h = (b-a)/10;
x = a : h : b;
pertA = Pertubation(1:11, :);
pertB = Pertubation(12:22, :);
pertAB = Pertubation(23:33, :);
figure
for i = 1:11
    errA(i, :) = abs(pertA(i, :) - y(x));
    errB(i, :) = abs(pertB(i, :) - y(x));
    errAB(i, :) = abs(pertAB(i, :) - y(x));
    normA(i) = norm(errA(i, :), 'inf');
    normB(i) = norm(errB(i, :), 'inf');
    normAB(i) = norm(errAB(i, :), "inf");
end
loglog(pert, normA)
hold on
loglog(pert, normB)
hold on
loglog(pert, normAB)
grid on
xlabel('порядок возмущения')
ylabel('погрешность')
title('Зависимость погрешности от возмущения');
legend('Возмущение в А', 'Возмущение в B', 'Возмущение и в А и в В')

