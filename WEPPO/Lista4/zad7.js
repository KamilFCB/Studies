const readline = require('readline');
const fs = require('fs');

var fileInterface = readline.createInterface({
    input: fs.createReadStream('./example.log')
});

class IpCounter{
    constructor(ip, counter){
        this.ip = ip;
        this.counter = counter;
    }
}

let counter = new Array();

fileInterface.on('line', function(line){
    var data = line.split(" ");
    var flag = false;
    counter.forEach(function(elem){
        if(elem.ip === data[1]){
            elem.counter++;
            flag = true;
        }
    });
    if(!flag){
        counter.push(new IpCounter(data[1], 1));
    }
    flag = false;
});

fileInterface.on('close', function(){

    counter.sort(function(a, b){
        return b.counter - a.counter;
    });

    for(var i = 0; i < 3; i++)
        console.log(`${counter[i].ip} ${counter[i].counter}`);
})