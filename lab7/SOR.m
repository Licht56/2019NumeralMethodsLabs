function [ans, step] = SOR(array, b, err, omega)
    format long
    n = length(b); 
    ans = zeros(n,1);
    next = zeros(1,n);
    D = diag(diag(array));
    U = triu(array) - D;
    L = tril(array) - D;
    M = inv(D + omega*L)*((1-omega)*D - omega*U);
    g = omega*inv(D + omega* L)*b;
    step = 0;
    while true
        next = M * ans + g;
        step = step + 1;
        if max(abs(next - ans)) < err
            break;
        end
        if step > 10^6
            break;
        end
        ans = next;
    end
    ans = next;
end