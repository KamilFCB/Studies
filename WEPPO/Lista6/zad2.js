var http = require('http');
var express = require('express');
var app = express();

app.set('view engine', 'ejs');
app.set('views', './views');

app.use(express.urlencoded({ extended: true }));

app.get('/', (req, res) => {
    res.render('zad2');
});



http.createServer(app).listen(3000);