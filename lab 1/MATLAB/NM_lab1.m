%input values
polynom = @(x) x^5 + x^2 - 5;
complex_func = @(x) 5^x + 3*x;
polynom_root = fzero(polynom, [1, 2]);
complex_func_root = fzero(complex_func, [-1, 0]);

%importing data
polynom_newton = importdata('C:\Users\user\source\repos\NumMeths-1\NumMeths-1\Polynom_Newton_method.csv');
polynom_half_division = importdata('C:\Users\user\source\repos\NumMeths-1\NumMeths-1\Polynom_half_division.csv');
polynom_approximation_n = importdata('C:\Users\user\source\repos\NumMeths-1\NumMeths-1\Influence_of_first_approximation_Polynom.csv');
polynom_approximation_hd = importdata('C:\Users\user\source\repos\NumMeths-1\NumMeths-1\Influence_of_first_approximation_Polynom_hd.csv');
complex_func_half_division = importdata('C:\Users\user\source\repos\NumMeths-1\NumMeths-1\Complex_Func_half_division.csv');
complex_func_newton = importdata('C:\Users\user\source\repos\NumMeths-1\NumMeths-1\Complex_Func_Newton_method.csv');
complex_func_approximation_n = importdata('C:\Users\user\source\repos\NumMeths-1\NumMeths-1\Influence_of_first_approximation_Complex_Func.csv');
complex_func_approximation_hd = importdata('C:\Users\user\source\repos\NumMeths-1\NumMeths-1\Influence_of_first_approximation_Complex_Func_hd.csv');

%plotting for accurancy = 10^(-15)
polynom_error_hd = abs(polynom_root - polynom_half_division(1, 4:1:52));
polynom_error_n = abs(polynom_root - polynom_newton(1, 4:1:12));
complex_func_error_hd = abs(complex_func_root - complex_func_half_division(1, 4:1:53));
complex_func_error_n = abs(complex_func_root - complex_func_newton(1, 4:1:10));
semilogy(1:1:49, polynom_error_hd)
grid on
hold all
semilogy(1:1:9, polynom_error_n)
semilogy(1:1:50, complex_func_error_hd)
semilogy(1:1:7, complex_func_error_n)
title('График сходимости методов');
xlabel('Номер итерации');
ylabel('Погрешность');
legend('Половинное деление полинома', 'Ньютон для полинома', 'Половинное деление функции', 'Ньютон для функции');

%plotting amount of calculations
accurancy = polynom_half_division(:, 1);
polynom_amount_hd = polynom_half_division(:, 2);
polynom_amount_n = polynom_newton(:, 2);
complex_func_amount_hd = complex_func_half_division(:, 2);
complex_func_amount_n = complex_func_newton(:, 2);
figure
semilogx(accurancy, polynom_amount_hd);
grid on
hold all
semilogx(accurancy, polynom_amount_n);
semilogx(accurancy, complex_func_amount_hd);
semilogx(accurancy, complex_func_amount_n);
title('График обьема вычислений в зависимости от точности');
xlabel('Точность');
ylabel('Количество итераций');
legend('Половинное деление полинома', 'Ньютон для полинома', 'Половинное деление функции', 'Ньютон для функции');

%plotting error to accurancy
polynom_final_hd_error = abs(polynom_root - polynom_half_division(:, 3));
polynom_final_n_error = abs(polynom_root - polynom_newton(:, 3));
complex_func_final_hd_error = abs(complex_func_root - complex_func_half_division(:, 3));
complex_func_final_n_error = abs(complex_func_root - complex_func_newton(:, 3));
figure
loglog(accurancy, polynom_final_hd_error);
grid on
hold all
loglog(accurancy, polynom_final_n_error);
loglog(accurancy, complex_func_final_hd_error);
loglog(accurancy, complex_func_final_n_error);
y = @(x) x;
loglog(accurancy, y(accurancy), '--k');
title('Сравнения полученной точности и введеной');
xlabel('Точность');
ylabel('Полученная погрешность');
legend('Половинное деление полинома', 'Ньютон для полинома', 'Половинное деление функции', 'Ньютон для функции', 'Location', 'southeast');

%plotting influence of first approximation on amount of calculations
approximation_p_n = polynom_approximation_n(:, 1);
approximation_c_n = complex_func_approximation_n(:, 1);
amount_p_n = polynom_approximation_n(:, 2);
amount_c_n = complex_func_approximation_n(:, 2);
approximation_p_hd = polynom_approximation_hd(:, 1);
approximation_c_hd = complex_func_approximation_hd(:, 1);
amount_p_hd = polynom_approximation_hd(:, 2);
amount_c_hd = complex_func_approximation_hd(:, 2);
figure
subplot(1, 2, 1);
plot(approximation_p_n, amount_p_n);
title('Зависимость для полинома');
xlabel('Приближение');
ylabel('Количество итераций');
grid on
subplot(1, 2, 2);
plot(approximation_c_n, amount_c_n);
title('Зависимость для трансцендентной функции');
xlabel('Приближение');
ylabel('Количество итераций');
grid on

figure
subplot(1, 2, 1);
plot(approximation_p_hd, amount_p_hd);
title('Зависимость для полинома');
xlabel('Приближение');
ylabel('Количество итераций');
grid on
subplot(1, 2, 2);
plot(approximation_c_hd, amount_c_hd);
title('Зависимость для трансцендентной функции');
xlabel('Приближение');
ylabel('Количество итераций');
grid on