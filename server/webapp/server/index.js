var express = require('express')
var app = express();
var path = require('path');
var router = require('./routes');


app.use('/public', express.static(path.join(__dirname, '../public'))); //Make public folder public accessible

app.use('/', router());

app.listen(8000, function () {
  console.log('Example app listening on port 8000!')
})
