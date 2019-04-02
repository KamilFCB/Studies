function fib() {
    var [n1, n2] = [0, 1];
    return {
        next: function () {
            [n1, n2] = [n2, n1 + n2];
            return {
                value: n1,
                done: false
            }
        }
    }
}
// function* fib() {
//     var [n1, n2] = [0, 1];
//     while (true) {
//         yield n1;
//         [n1, n2] = [n2, n1 + n2];
//     }
// }

var _it = fib();

for (var _result; _result = _it.next(), !_result.done;) {
    console.log(_result.value);
}

// for ( var i of fib() ) { //tylko *fib
//     console.log( i );
//     }