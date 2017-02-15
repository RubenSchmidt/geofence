var express = require('express');
var router = express.Router();
var fs = require('fs');

module.exports = function () {
    router.post(
      '/',
      createMap
    );
    return router;
};

function createMap (req, res) {
  req.body = JSON.parse(req.body);
  var points = pointsToLatLonInts(req, res);
}

function pointsToLatLonInts(req, res){
  var points = req.body.features[0].geometry.coordinates[0];
  var intArray = new Uint32Array(points.length*2);
  console.log(points);
  var pos = 0;
  for(var i=0; i<points.length; i++){
    var latAsInt = parseInt(points[i][0] * Math.pow(10, 6));
    var lonAsInt = parseInt(points[i][1] * Math.pow(10, 6));
    intArray[pos] = latAsInt;
    intArray[pos+1] = lonAsInt;
    pos+=2;
  }

  fs.writeFile('binary.orbit', Buffer.from(intArray), 'binary', function(err){
    if(err) {
      console.log(err);
    };
  });

  fs.open('binary.orbit', 'r', function(status, fd){
    var buffer = new Buffer(intArray.length);
    fs.read(fd, buffer, 0, intArray.length, 0, function(err, num){
      console.log(buffer.toString('utf-8', 0, num));
    })
  });

  var stat = fs.statSync('binary.orbit');
  res.writeHead(200, {
        'Content-Type': 'text/utf-8',
        'Content-Length': stat.size
    });

    var readStream = fs.createReadStream('binary.orbit');
    // We replaced all the event handlers with a simple call to readStream.pipe()
    readStream.pipe(res);
}
