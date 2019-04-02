function forEach(a, f) {
    for(var i = 0; i < a.length; i++)
        f(a[i]);
}

function map(a, f) {
    var res = [];
    
    for(var i = 0; i < a.length; i++)
        res.push(f(a[i]));

    return res;
}

function filter(a, f) {
    var res = [];

    for(var i = 0; i < a.length; i++){
        if(f(a[i]))
            res.push(a[i]);
    }

    return res;
}

var a = [1,2,3,4];
forEach( a, _ => { console.log( _ ); } );

console.log(filter( a, _ => _ < 3 ));
console.log(map( a, _ => _ * 2 ));

