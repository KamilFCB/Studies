const readline = require('readline');

const readIterface = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

readIterface.question("Jak się nazywasz? ", function(answer){
    console.log(`Witaj ${answer}`);
    readIterface.close();
});