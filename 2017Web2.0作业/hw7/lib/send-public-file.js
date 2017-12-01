`use strict`;
// send public files included js/css/img/html
const fs = require("fs");
const sendPage = require("./send-page.js");

function sendCSSFile(response, filename) {
    sendAttachFile(response, "public/css" + filename, 'text/css');
}

function sendJSFile(response, filename) {
    sendAttachFile(response, "public/js" + filename, 'text/js');
}

function sendIMGFile(response, filename) {
    sendAttachFile(response, "public/image" + filename, 'image/png');
}

function sendAttachFile(response, filename, contentType) {
    fs.readFile(filename, function (error, pgResp) {
        if (!error) {
            sendPage.sendPublicFileAnd200(response, pgResp, contentType);
        } else {
            sendPage.notFindPageAndSend404(response);
        }
    });
}

function sendRegisterHtmlFile(response) {
    fs.readFile('public/register.html', function (error, pgResp) {
        if (error) {
            sendPage.notFindPageAndSend404(response);
        } else {
            sendPage.sendHtmlPageAnd200(response, pgResp);
        }
    });
}

function sendDefaultHtmlFile(response, userInfo) {
    fs.readFile('public/details.html', 'utf-8', function (error, pgResp) {
        if (error) {
            sendPage.notFindPageAndSend404(response);
        } else {
            // replace user info into html and send html
            sendPage.sendHtmlPageAnd200(response, pgResp.replace(/USERNAME/, userInfo['username']).
                replace(/STUDENTID/, userInfo['studentid']).
                replace(/PHONE/, userInfo['phone']).
                replace(/EMAIL/, userInfo['email']));
        }
    });
}


exports.sendCSSFile = sendCSSFile;
exports.sendJSFile = sendJSFile;
exports.sendIMGFile = sendIMGFile;
exports.sendRegisterHtmlFile = sendRegisterHtmlFile;
exports.sendDefaultHtmlFile = sendDefaultHtmlFile;