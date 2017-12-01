`use strict`;
const http = require('http');
const url = require('url');
const fs = require("fs");
const util = require('util');
const querystring = require('querystring');
const server = http.createServer();

const jsonObjHanler = require('./lib/json-object-handler.js');
const sendPublicFile = require('./lib/send-public-file.js');
const sendPage = require('./lib/send-page.js');

const DATAJSONFILE = 'data.json';


// check if data file exit
if (!jsonObjHanler.isDataFileExist(DATAJSONFILE)) {
    console.log('[ERROR]: Conld not create data.json');
    process.exit(1);
}

server.on('request', (request, response) => {
    if (request.method == 'POST') {
        var postDatas = ""; // get post data
        request.on('data', function (chunk) { // add post data
            postDatas += chunk;
        });
        request.on('end', function () { // deal with post data
            postDatas = querystring.parse(postDatas);
            var returnMessage;
            // read data file infomation from data file
            fs.readFile(DATAJSONFILE, function (error, data) {
                if (error) {
                    sendPage.notGetDataAndSend501(response);
                } else {
                    // find if exist user with same info
                    // add into data if not duplicate
                    // send json result
                    jsonObjHanler.addIntoDataAndSendJsonResult(response, DATAJSONFILE, postDatas);
                }
            });
        });
    }
    else {
        // send css/js/img file
        if (request.url.indexOf('.css') != -1) {
            sendPublicFile.sendCSSFile(response, request.url.slice(request.url.lastIndexOf('/')));
        } else if (request.url.indexOf('.js') != -1) {
            sendPublicFile.sendJSFile(response, request.url.slice(request.url.lastIndexOf('/')));
        } else if (request.url.indexOf('.png') != -1) {
            sendPublicFile.sendIMGFile(response, request.url.slice(request.url.lastIndexOf('/')));
        }
        else {
            var params = url.parse(request.url, true).query;// get GET request data
            const usernameParam = params['username'];       // get parameter of username
            // check paramenter 'username' and if exsits the username
            // if paramenter 'username' is not null
            if (usernameParam) {
                // read data file infomation from data file
                fs.readFile(DATAJSONFILE, function (error, data) {
                    if (error) {
                        sendPage.notGetDataAndSend501(response);
                    } else {
                        // find user info with same username and get user info
                        var userInfo = jsonObjHanler.getUserInfoByUsername(data, usernameParam);
                        if (userInfo) { // if the user exist in data file, send details page
                            sendPublicFile.sendDefaultHtmlFile(response, userInfo);
                        } else {
                            sendPublicFile.sendRegisterHtmlFile(response);
                        }
                    }
                });
            } else {
                sendPublicFile.sendRegisterHtmlFile(response);
            }
        }
    }
});

server.listen(8080);
console.log('Server is running at http://127.0.0.1:8080/');