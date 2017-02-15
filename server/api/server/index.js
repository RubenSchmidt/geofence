var express = require('express')
var app = express();
var bodyParser = require('body-parser');
var path = require('path');
var router = require('./routes');
var serverConfig = require('./config/server.config');

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({extended: true, colorize: true}));

app.use('/public', express.static(path.join(__dirname, '../public'))); //Make public folder public accessible

app.use(function (req, res, next) {

    // Website you wish to allow to connect
    res.setHeader('Access-Control-Allow-Origin', 'http://localhost:8000');

    // Request methods you wish to allow
    res.setHeader('Access-Control-Allow-Methods', 'GET, POST, OPTIONS, PUT, PATCH, DELETE');

    // Request headers you wish to allow
    res.setHeader('Access-Control-Allow-Headers', 'X-Requested-With,content-type');

    // Set to true if you need the website to include cookies in the requests sent
    // to the API (e.g. in case you use sessions)
    res.setHeader('Access-Control-Allow-Credentials', true);

    // Pass to next layer of middleware
    next();
});

app.use('/api', router());

app.listen(serverConfig.PORT, function () {
  console.log('Example app listening on port ' + serverConfig.PORT + '!')
})
