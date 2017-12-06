var http = require('http');
var url = require('url');
var path = require('path');
var fs = require('fs');
var port = 3000;

http.createServer(function(req,res){
  var pathname = url.parse(req.url).pathname;
  var mimeType = getMimeType(pathname);
  console.log(req.url);
  if (!!mimeType) {
    handlePage(req, res, pathname);
  } else {
    handleAjax(req, res);
  }
}).listen(port, function(){
  console.log('server listen on ', port);
});

function getMimeType(pathname) {
  var validExtensions = {
    ".html" : "text/html",
    ".js": "application/javascript",
    ".css": "text/css",
    ".jpg": "image/jpeg",
    ".gif": "image/gif",
    ".png": "image/png"
  };
  var ext = path.extname(pathname);
  var type = validExtensions[ext];
  return type;
}

function handlePage(req, res, pathname) {
  var filePath = __dirname + pathname;
  console.log(__dirname);
  var mimeType = getMimeType(pathname);
  if (fs.existsSync(filePath)) {
    fs.readFile(filePath, function(err, data){
      if (err) {
        res.writeHead(500);
        res.end();
      } else {
        res.setHeader("Content-Length", data.length);
        res.setHeader("Content-Type", mimeType);
        res.statusCode = 200;
        res.end(data);
      }
    });
  } else {
    res.writeHead(500);
    res.end();
  }
}

function handleAjax(req, res) {
  var random_time = 1000 + getRandomNumber(2000);
  var random_num  = 1 + getRandomNumber(9);
  setTimeout(function(){
    res.writeHead(200, {'Content-Type': 'text/plain'});
    res.end("" + random_num);
    console.log(random_num);
  }, random_time);
}

function getRandomNumber(limit) {
  return Math.round(Math.random() * limit);
}
// `use strict`
// const http = require('http'),
//     url = require('url'),
//     fs = require('fs'),
//     querystring = require('querystring'),
//     server = http.createServer();

// server.on('request', (req, res) => {
//     if (req.method === "GET") {
//         switch (req.url) {
//             case '/S1':
//                 sendS1(res);
//                 break;
//             case '/S2':
//                 sendS2(res);
//                 break;
//             case '/S3':
//                 sendS3(res);
//                 break;
//             case '/S4':
//                 sendS4(res);
//                 break;
//             case '/S5':
//                 sendS5(res);
//                 break;
//             default:
//                 if (req.url.endsWith("t.js")) {
//                     sendTJS(res);
//                 } else if (req.url.endsWith(".css")) {
//                     sendCSS(res);
//                 }
//                 break;
//         }
//     }
// });

// // is like isNumeric of jquery
// function isNumeric(obj) {
//     return !isNaN(parseFloat(obj)) && isFinite(obj);
// }

// // check if number valid
// function isValidNum(num) {
//     return isNumeric(num) && num % 1 === 0 && num >= 1 && num <= 10;
// }
