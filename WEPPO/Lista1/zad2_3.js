function isDivisible(x)
{
    var sum = 0;
    for(var i = 0; i < x.toString().length; i++)
    {
        var curr = parseInt(x.toString()[i]);
        
        if(x % curr != 0)
            return false;

        sum += parseInt(x.toString()[i]);
    }

    if(x % sum != 0)
        return false;

    return true;
}

function isPrime(x)
{
    for(var i = 2; i * i <= x; i++)
    {
        if(x % i == 0)
            return false;
    }

    return true;
}

var divisibleNumbers = [];

for(var i =0; i<= 100000; i++)
    if(isDivisible(i))
    divisibleNumbers.push(i);
        
console.log(divisibleNumbers.length);

var primeNumbers = [];

for(var i =2; i<= 100000; i++)
    if(isPrime(i))
    primeNumbers.push(i);

console.log(primeNumbers.length);

