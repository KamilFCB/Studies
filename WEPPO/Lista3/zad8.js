// function fib() {
//     var [n1, n2] = [0, 1];
//     return {
//         next: function () {
//             [n1, n2] = [n2, n1 + n2];
//             return {
//                 value: n1,
//                 done: false
//             }
//         }
//     }
// }
function* fib() {
    var [n1, n2] = [0, 1];
    while (true) {
        yield n1;
        [n1, n2] = [n2, n1 + n2];
    }
}

function* take(it, top) {
    var next = it.next();
    var counter = 0;
    while (counter < top) {
        yield next.value;
        counter++;
        next = it.next();
    }
}

for (let num of take(fib(), 10)) {
    console.log(num);
}