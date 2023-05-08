%% Part 1
%importing data
n = importdata('lab3\num_of_matrix.csv');
Gradrang = importdata('lab3\rang.csv');
A_all = importdata('lab3\matrix.csv');
b_all = importdata('lab3\rightpart.csv');
cond_all = importdata('lab3\cond.csv');
iterations = importdata('C:\Users\user\source\repos\NumMeths-3\NumMeths-3\iterations.csv');
roots = importdata('C:\Users\user\source\repos\NumMeths-3\NumMeths-3\root.csv');
%creating temporary values
A = zeros(Gradrang);
b = zeros(Gradrang, 1);
root = zeros(Gradrang, 1);
k = 0;
for i = 1:1:n
    for j = 1:1:Gradrang
            A(j, :) = A_all(i, (j-1)*Gradrang + 1:1:j*Gradrang);
    end
    b = b_all(i, :)';
    matlab_root = A \ b;
    err = zeros(iterations(i), 1);
    for j = 1:1:iterations(i)
        root = roots(k + j, :)';
        err(j) = norm(root - matlab_root);
    end
    loglog(1:1:iterations(i), err);
    hold on
    k = k + iterations(i);
end
grid on
title({'График зависимости количества итераций'; 'от числа обусловленности'});
xlabel('количество итераций');
ylabel('норма абсолютной погрешности');
legend('cond = 10', 'cond = 10^2', 'cond = 10^3', 'cond = 10^4');
%% part 2
rang = importdata('lab3\rang2.csv')';
Gradtime = importdata('C:\Users\user\source\repos\NumMeths-3\NumMeths-3\GradientTime.csv')';
Choltime = importdata('C:\Users\user\source\repos\NumMeths-3\NumMeths-3\CholTime.csv')';
figure
hold all
title({'График зависимости времени работы';'от ранга матрицы'})
xlabel('Ранг матрицы');
ylabel('Время работы метода');
plot(rang, Choltime);
plot(rang, Gradtime);
grid on;
legend('Метод Холецкого', 'Градиентный метод', 'location', 'southeast');

% Лабораторная 4
% Задание на 7 баллов: Иследовать как отделимость собственных чисел влияет на скорость
% сходимости метода
% Задание на 10 баллов: Ислледовать устойчивость метода - Проверить
% неравенства из лекций.