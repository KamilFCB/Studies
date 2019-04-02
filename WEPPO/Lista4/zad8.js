var fs = require('fs');
var util = require('util');

fs.readFile('zad1.js', 'utf-8', function (err, data) {
    if (err)
        console.log(err);
    else {
        console.log(data);
        console.log("=============================");
    }
});

function fspromise(path, enc) {
    return new Promise((res, rej) => {
        fs.readFile(path, enc, (err, data) => {
            if (err)
                rej(err);
            res(data);
        });
    });
}

fspromise('zad1.js', 'utf-8')
    .then(function (data){
        console.log(data);
        console.log("=============================");
    });

var file = util.promisify(fs.readFile);
var file2 = fs.promises.readFile;

(async function(){
    var data = await file('zad1.js', 'utf-8');
    var data2 = await file2('zad1.js', 'utf-8');
    console.log(data);
    console.log("=============================");
    console.log(data2);
})();