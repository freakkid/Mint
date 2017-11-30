`use strict`;
const http = require('http');
const url = require('url');
const fs = require("fs");
const util = require('util');
const querystring = require('querystring');
const server = http.createServer();

const DATAJSONFILE = 'data.json';
const jsonObjHanler = require('./lib/json-object-handler.js');

//
// ─── CHECK IF DATA FILE EXIT ────────────────────────────────────────────────────
//
fs.stat(DATAJSONFILE, function (error, stats) {
    if (error) {
        // if data file does not exist, create one
        if (error.code == 'ENOENT') {
            fs.writeFile(DATAJSONFILE, '[]');
        } else {    // other error send 501
            console.log('[ERROR]: Conld not create data.json');
            process.exit(1)
        }
    }
});
// ────────────────────────────────────────────────────────────────────────────────

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
                    response.writeHead(501);
                    response.write('Sorry, could not get data!');
                } else {
                    // find if exist user with same info
                    returnMessage = jsonObjHanler.checkDuplicationAndAddIntoData(DATAJSONFILE, postDatas);
                    response.writeHead(200, { 'Content-Type': 'text/json' });
                    response.write(JSON.stringify(returnMessage));   
                }
            });
            response.end(); 
        });
    }
    else {
        //
        // ────────────────── GET SOME CSS JS PNG FILE AFTER HTML FILE ─────
        //
        if (request.url.indexOf('.css') != -1) {
            fs.readFile("public/css" + request.url.slice(request.url.lastIndexOf('/')), function (error, pgResp) {
                if (!error) {
                    response.writeHead(200, { 'Content-Type': 'text/css' });
                    response.write(pgResp);
                } else {
                    response.writeHead(401);
                }
                response.end();
            })
        } else if (request.url.indexOf('.js') != -1) {
            fs.readFile("public/js" + request.url.slice(request.url.lastIndexOf('/')), function (error, pgResp) {
                if (!error) {
                    response.writeHead(200, { 'Content-Type': 'text/javascript' });
                    response.write(pgResp);
                } else {
                    response.writeHead(402);
                }
                response.end();
            })
        } else if (request.url.indexOf('.png') != -1) {
            fs.readFile("public/image" + request.url.slice(request.url.lastIndexOf('/')), function (error, pgResp) {
                if (!error) {
                    response.writeHead(200, { 'Content-Type': 'image/png' });
                    response.write(pgResp);
                } else {
                    response.writeHead(403);
                }
                response.end();
            })
        }
        else {
            //
            // ───────────────────────────────────────────────────── GET USER DETAIL PAGE ─────
            //
            var params = url.parse(request.url, true).query;
            const usernameParam = params['username'];       // get parameter of username
            var userInfo;                                   // user info 
            // check paramenter 'username' and if exsits the username
            // if paramenter 'username' is not null
            if (usernameParam) {
                // read data file infomation from data file
                fs.readFile(DATAJSONFILE, function (error, data) {
                    if (error) {
                        response.writeHead(501);
                        response.write('Sorry, could not get data!');
                        response.end();
                    } else {
                        // get json array from json string
                        var jsonUserArray = JSON.parse(data),
                            i = 0;
                        // find same value
                        for (; i < jsonUserArray.length; i++) {
                            if (jsonUserArray[i]['username'] == usernameParam) {
                                userInfo = jsonUserArray[i];
                                break;
                            }
                        }
                    }
                });
            }
            if (userInfo) { // if userInfo not null
                fs.readFile('public/details.html', function (error, pgResp) {
                    if (error) {
                        response.writeHead(404);
                        response.write('Contents you are looking are Not Found');
                    } else {
                        // replace user info into html
                        pgResp.replace(/USERNAME/, userInfo['username']);
                        pgResp.replace(/STUDENTID/, userInfo['studentid']);
                        pgResp.replace(/PHONE/, userInfo['phone']);
                        pgResp.replace(/EMAIL/, userInfo['email']);
                        // send html
                        response.writeHead(200, { 'Content-Type': 'text/html' });
                        response.write(pgResp);
                    }
                    response.end();
                });
            } else {
                fs.readFile('public/register.html', function (error, pgResp) {
                    if (error) {
                        response.writeHead(405);
                        response.write('Contents you are looking are Not Found');
                    } else {
                        // send html
                        response.writeHead(200, { 'Content-Type': 'text/html' });
                        response.write(pgResp);
                    }
                    response.end();
                });
            }
        }

    }
});

server.listen(8080);
console.log('Server is running at http://127.0.0.1:8080/');