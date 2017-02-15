var express = require('express');
var router = express.Router();
var mapRouter = require('./map')

module.exports = function () {
	router.get('/', function (req, res) {
		res.send('API running');
	});
	router.use('/map', mapRouter());
	return router;
};
