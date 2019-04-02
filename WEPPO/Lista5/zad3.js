var fs = require('fs');
var http = require('http');
(async function () {
    var html = await fs.promises.readFile('test.txt', 'utf-8');
    var server = http.createServer(
        (req, res) => {
            res.setHeader('Content-Disposition', 'attachment; filename=test.txt');
            if(req.method == "GET"){
                res.end("test123");
            }
        });
    server.listen(3000);
    console.log('started');
})();