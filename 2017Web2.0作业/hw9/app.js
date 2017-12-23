var express = require('express');
var path = require('path');
var favicon = require('serve-favicon');
var logger = require('morgan');
var cookieParser = require('cookie-parser');
var bodyParser = require('body-parser');

var regist = require('./routes/regist');
var user = require('./routes/user');
var index = require('./routes/index');
var users = require('./routes/users');
var check = require('./routes/check');

var app = express();

// view engine setup
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'jade');

app.use(logger('dev'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/users', users);   // signin POST / signOUT DELETE
app.use('/regist', regist); // signup GET/POST
app.use('/user', user);     // signup POST
app.use('/check', check);   // check GET
app.use('/', index);       // details GET / login page GET /
app.use(function(req, res, next) {  // redirect all 404 to default entrance
    res.status(302).setHeader('Location', '/');
    res.end();
});

module.exports = app;
