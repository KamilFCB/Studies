function fib_rec(x)
{
    if(x == 0)
        return 0;
    
    if(x == 1)
        return 1;

    if(x == 2)
        return 1;

    return fib_rec(x-1) + fib_rec(x-2);
}

function fib_iter(x)
{
   var x1 = 0;
   var x2 = 1;
   var res = 0;

   if(x == 0)
        return 0;
    
    if(x == 1)
        return 1;

   for(var i = 2; i <= x; i++)
   {
       res = x1 + x2;
       x1 = x2;
       x2 = res;
   }

   return res;
}

var n = 45;

for(var i = 10; i <= n; i++)
{
    console.time("fib_iter(" + i + ")");
    fib_iter(i);
    console.timeEnd("fib_iter(" + i + ")");
    console.time("fib_rec(" + i + ")");
    fib_rec(i);
    console.timeEnd("fib_rec(" + i + ")");
    console.log("-----------------------------------");
}