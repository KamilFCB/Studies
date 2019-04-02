var http = require('http');
var express = require('express');
var app = express();

app.set('view engine', 'ejs');
app.set('views', './views');

app.use(express.urlencoded({ extended: true }));

app.get('/', (req, res) => {
    var imie = req.query.imie;
    var nazwisko = req.query.nazwisko;
    var zajecia = req.query.zajecia;
    var punkty = new Array();
    punkty.push(req.query.zad1);
    punkty.push(req.query.zad2);
    punkty.push(req.query.zad3);
    punkty.push(req.query.zad4);
    punkty.push(req.query.zad5);
    punkty.push(req.query.zad6);
    punkty.push(req.query.zad7);
    punkty.push(req.query.zad8);
    punkty.push(req.query.zad9);
    punkty.push(req.query.zad10);

    if(!imie || !nazwisko || !zajecia)
        res.render('index', {imie: imie, nazwisko: nazwisko, zajecia: zajecia, punkty: punkty});
    else
        res.redirect('/print'+req.url);
});

app.get('/print', (req, res) => {
    var imie = req.query.imie;
    var nazwisko = req.query.nazwisko;
    var zajecia = req.query.zajecia;
    var punkty = new Array();
    punkty.push(req.query.zad1);
    punkty.push(req.query.zad2);
    punkty.push(req.query.zad3);
    punkty.push(req.query.zad4);
    punkty.push(req.query.zad5);
    punkty.push(req.query.zad6);
    punkty.push(req.query.zad7);
    punkty.push(req.query.zad8);
    punkty.push(req.query.zad9);
    punkty.push(req.query.zad10);

    res.render('print', { imie: imie, nazwisko: nazwisko, zajecia: zajecia, punkty: punkty});
});

http.createServer(app).listen(3000);