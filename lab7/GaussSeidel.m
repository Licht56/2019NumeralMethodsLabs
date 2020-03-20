function [ans, step] = GaussSeidel(array, b, err)
    format long
    n = length(b); 
    ans = zeros(n,1);
    next = zeros(1,n);
    L = diag(diag(array));
    U = triu(array) - L;
    D = tril(array) - L;
    f = inv(D + L)*b;
    S = -inv(D + L)*U;
    step = 0;
    while true
        next = S * ans + f;
        step = step + 1;
        if max(abs(next - ans)) < err
            break;
        end
        ans = next;
    end
    ans = next;
end