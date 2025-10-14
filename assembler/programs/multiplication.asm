// Multiplication of x and y

    var iter 1
    var product 0
    var x 8
    var y 8
main:
    lda x
    sub iter
    jc loop
end:
    lda product
    out
    hlt
loop:
    sta x
    lda product
    add y
    sta product
    jmp main