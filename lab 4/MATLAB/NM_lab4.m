%% Исследование сдвигов
data = importdata('C:\Users\user\source\repos\NumMeths-4\NumMeths-4\eigenvector_+_value.csv');
first = importdata('lab4\firsteig.csv');
second = importdata('lab4\secondeig.csv');
last = importdata('lab4\lasteig.csv');
iterations_num = data(:, 1);
mu = zeros(900, 1);
begin = last;
delta = ((first + last) / 2 - last) / 1000;
ending = (first + last) / 2;
mu(1) = begin;
for i = 2:1:900
    mu(i) = mu(i-1) + delta;
end
figure
hold all
grid on
plot(mu, iterations_num);
xline((second + last) / 2, '--b');
text((second + last) / 2, 100, '$\mu = \frac{\lambda_2 + \lambda_n}{2}$', 'interpreter', 'LaTex', 'fontsize', 14);
title('Исследование сдвига для лучшей сходимости');
xlabel('Сдвиг');
ylabel('Количество итераций');

%% Исследование сходимости
epsilon = [10^(-5), 10^(-6), 10^(-7), 10^(-8), 10^(-9), 10^(-10), 10^(-11), 10^(-12), 10^(-13), 10^(-14)]';
data = importdata('C:\Users\user\source\repos\NumMeths-4\NumMeths-4\eigenvector_+_value1.csv');
iterations_well = data(1:1:10, 1);
iterations_bad = data(11:1:20, 1);
figure
semilogx(epsilon, iterations_well);
grid on
hold all
semilogx(epsilon, iterations_bad);
title('Исследование влияния отделимости на скорость сходимости');
xlabel('Погрешность');
ylabel('Количество итераций');
legend('хорошая отделимость', 'плохая отделимость');

%% Устойчивость АПСЗ
n = 10;
data = importdata('C:\Users\user\source\repos\NumMeths-4\NumMeths-4\eigenvector_+_value2.csv');
originA = importdata('lab4\origin_matrix2.csv');
Vectors = data(:, 2:1:n+1);
Values = data(:, n+2);
A = zeros(n);
val_err = zeros(40, 1);
vec_err = zeros(40, 1);
for i = 1:1:20
    for j = 1:1:n
            A(j, :) = originA(i, (j-1)*n + 1:1:j*n); 
    end
    [Vec, Val] = eig(A);
    maximum = Vec(1, 1);
    for k = 1:1:10
        if (abs(maximum) < abs(Vec(k, 1)))
            maximum = Vec(k, 1);
        end
    end
    NewVec = Vec(:, 1) ./ maximum;
    val_err(i) = abs(Val(1, 1) - Values(i));
    vec_err(i) = norm(NewVec - Vectors(i, :)');
end
% random matrix
for i = 1:1:20
    for j = 1:1:n
            A(j, :) = originA(i, (j-1)*n + 1:1:j*n); 
    end
    [Vec, Val] = eig(A);
    maximum = Vec(1, 1);
    for k = 1:1:10
        if (abs(maximum) < abs(Vec(k, 1)))
            maximum = Vec(k, 1);
        end
    end
    NewVec = Vec(:, 1) ./ maximum;
    val_err(20 + i) = abs(Val(1, 1) - Values(20 + i));
    vec_err(20 + i) = norm(NewVec - Vectors(20 + i, :)');
end
dA_norm = [10, 1, 0.1, 0.01, 0.001, 0.0001, 10^(-5), 10^(-6), 10^(-7), 10^(-8)];

figure
loglog(dA_norm, val_err(1:1:10));
hold all
grid on
loglog(dA_norm, val_err(11:1:20));
loglog(dA_norm, val_err(21:1:30));
loglog(dA_norm, val_err(31:1:40));
title('Исследование устойчивости АПСЗ для собсвтенных чисел');
xlabel('Порядок возмущения');
ylabel('Фактическая ошибка');
legend('хорошая отделимость', 'плохая отделимость');

figure
loglog(dA_norm, vec_err(1:1:10));
hold all
grid on
loglog(dA_norm, vec_err(11:1:20));
loglog(dA_norm, vec_err(21:1:30));
loglog(dA_norm, vec_err(31:1:40));
title('Исследование устойчивости АПСЗ для собсвтенных векторов');
xlabel('Порядок возмущения');
ylabel('Фактическая ошибка');
legend('хорошая отделимость', 'плохая отделимость');