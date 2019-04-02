function fib(n){
    if(n===0)
        return 0;
    if(n===1)
        return 1;
    if(n===2)
        return 1;
    
    return memofib(n-1) + memofib(n-2);
}

function memoize(fn){
    var cache = {};

    return function(n){
        if(n in cache)
            return cache[n];
        else {
            var result = fn(n);
            cache[n] = result;
            return result;
        }
    }
}


var memofib = memoize(fib);

console.log(memofib(10));
console.log(memofib(40));

console.time("fib");
console.log(memofib(100));
console.timeEnd("fib");
console.time("fib");
console.log(memofib(99));
console.timeEnd("fib");