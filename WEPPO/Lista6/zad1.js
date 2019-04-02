var http = require('http');
var express = require('express');
var app = express();
var multer = require('multer');

var upload = multer({ dest: './uploads' });

app.set('view engine', 'ejs');
app.set('views', './views');

app.use(express.urlencoded({ extended: true }));

app.get('/', (req, res) => {
    res.render('index');
});

app.post('/', upload.single('file'), (req, res) => {
    //console.log(req.file.filename);
    res.render('index');
});

http.createServer(app).listen(3000);