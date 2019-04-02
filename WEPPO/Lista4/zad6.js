const fs = require('fs');
var file = fs.readFile("zad1.js", "utf-8", function(err, data){
    if(err)
        console.log(err);
    console.log(data);
});