var fs = require('fs');
var http = require('http');
var qs = require('querystring');

(async function () {
    var html = await fs.promises.readFile('test.html', 'utf-8');
    var server = http.createServer(
        (req, res) => {
            if (req.method == "GET") {
                res.end(html.replace("dane", req.url));
            }
            else if (req.method == "POST") {
                var postdata = "";
                req.on('data', function (data) { postdata += data });
                req.on('end', () => {

                    var body = qs.parse(postdata);                
                    res.end(html.replace("dane", body.imie + " " + body.nazwisko));
                });
            }
        });
    server.listen(3000);
    console.log('started');
})(); 
