function sum(a, ...args){
    for(var i = 0; i < args.length; i++)
        a += args[i];

    return a;
}

console.log(sum(1,2,3));
// 6
console.log(sum(1,2,3,4,5));
// 15
