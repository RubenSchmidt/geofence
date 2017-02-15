var express = require('express');
var router = express.Router();
var path = require('path');

module.exports = function () {
	router.get('/', function (req, res, next) {
        if(req.originalUrl.indexOf('public') >= 0){ //abit hacky, checks if public is part of url and returns if it is in order to allow the request to access the files in the public dir
            return next();
        }
        res.sendFile(path.resolve('../webapp/public/index/index.html'));
    });
	return router;
};
