%% Part 1
n = 10;
rang = 10;
cond_val = [10, 10^2, 10^3, 10^4, 10^5, 10^6, 10^7, 10^8, 10^9, 10^10];
A = importdata('lab2\matrix.csv');
b = importdata('lab2\rightpart.csv');
root = importdata('C:\Users\user\source\repos\NumMeths-2\NumMeths-2\root.csv');
tmpA = zeros(rang);
tmpb = zeros(rang, 1);
tmproot = zeros(rang, 1);
err = zeros(n, 1);
err1 = zeros(n, 1);
for i = 1:1:n
    for j = 1:1:rang
            tmpA(j, :) = A(i, (j-1)*rang + 1:1:j*rang); 
    end
    tmpb = b(i, :)';
    tmproot = root(i, :)';
    matlab_root = tmpA \ tmpb;
    err1(i) = norm(tmpA * tmproot - tmpb);
    err(i) = norm(tmproot - matlab_root);
end
loglog(cond_val, err);
grid on
hold all
loglog(cond_val, err1);
title({'График зависимости норм невязки и фактической ошибки';'от числа обусловленности матрицы'});
xlabel('Cond(A)');
ylabel('$||x - x^*||$ or $||Ax - b||$', 'interpreter', 'LaTex');
legend('Фактическая ошибка', 'Невязка', 'Location', 'southeast');
%% Part 2
cond_well = 10;
cond_bad = 10^10;
num = 2;
rang = 10;
A = importdata('lab2\matrix2.csv');
b = importdata('lab2\rightpart2.csv');
root = importdata('C:\Users\user\source\repos\NumMeths-2\NumMeths-2\root2.csv');
delta = importdata('lab2\delta.csv');
tmpdelta = zeros(rang, 1);
b1 = zeros(rang, 1);
b_norm = zeros(num * 10, 1);
root_norm = zeros(num * 10, 1);
for i = 1:1:num
    for j = 1:1:rang
            tmpA(j, :) = A(i, (j-1)*rang + 1:1:j*rang); 
    end
    for k = 1:1:10
        b1 = b((i-1) * 10 + k, :)';%right part with pertubation
        tmpdelta = delta((i-1) * 10 + k, :)';%pertubation of right part
        tmpb = b1 - tmpdelta;%rightpart without pertubation
        tmproot = root((i-1) * 10 + k, :)';%root calculated with pertubation
        matlab_root = tmpA \ tmpb;%root calculated without pertubation
        b_norm((i-1) * 10 + k) = norm(tmpdelta) / norm(tmpb);
        root_norm((i-1) * 10 + k) = norm(tmproot - matlab_root) / norm(matlab_root);
    end
end
y1 = @(x) cond_well * x;
y2 = @(x) cond_bad * x;
figure
loglog(b_norm(1:1:10), root_norm(1:1:10));
grid on
hold all
loglog(b_norm(10:-1:1), y1(b_norm(10:-1:1)));
loglog(b_norm(11:1:20), root_norm(11:1:20));
loglog(b_norm(20:-1:11), y2(b_norm(20:-1:11)));
title({'График зависимости относительной погрешности решения'; 'от возмущения'});
xlabel('$\frac{\delta b}{b}$', 'interpreter', 'LaTex');
ylabel('$\frac{||x - x^*||}{||x^*||}$', 'interpreter', 'LaTex');
legend('Хорошо обусловленная матрица', '', 'Плохо обусловленная матрица', '', 'Location', 'northwest');
%% Part 3
Rang = importdata('lab2\rang3.csv')';
Time = importdata('C:\Users\user\source\repos\NumMeths-2\NumMeths-2\time.csv')';
figure
%y = @(x) 23 * x.^3;
%x = 0:0.001:0.185;
plot(Rang, Time);
hold on
grid on
ft = fittype('a * x^3');
f = fit(Rang, Time, ft, 'StartPoint', 0);
plot(f, Rang, Time);
%plot(Rang, y(x));
title({'График зависимости времени выполнения метода'; 'от ранга матрицы'});
xlabel('Ранг матрицы');
ylabel('Время выполнения');