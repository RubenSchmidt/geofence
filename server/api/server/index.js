var express = require('express')
var app = express();
var bodyParser = require('body-parser');

var router = require('./routes');


//app.use(bodyParser.json());
//app.use(bodyParser.urlencoded({extended: true, colorize: true}));

app.use (function(req, res, next) {
    var data='';
    req.setEncoding('utf8');
    req.on('data', function(chunk) {
       data += chunk;
    });

    req.on('end', function() {
        req.body = data;
        next();
    });
});

app.use('/api', router());

app.listen(8080, function () {
  console.log('Example app listening on port 8080!')
})
