// Fibonacci
// n_i+1 = n_i + n_i-1
// 
// a = 0
// b = 1
// c = 0
// for i in range(10):
//     c = a + b
//     a = b
//     b = c
//     print(c)

    var a 0
    var b 1
    var c 0
loop:
    lda a
    add b
    sta c
    lda b
    sta a
    lda c
    sta b
    out
    jmp loop