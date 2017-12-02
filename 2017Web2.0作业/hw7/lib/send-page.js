`use strict`;

// send page with status

function notGetDataAndSend501(response) {
    response.endHead(501);
    response.end('Sorry, could not get data!');
}

function notFindPageAndSend404(response) {
    response.writeHead(404);
    response.end('Contents you are looking are Not Found');
}

function sendJsonStringAnd200(response, jsonString) {
    response.writeHead(200, { 'Content-Type': 'text/json' });
    response.end(jsonString);
}

function sendHtmlPageAnd200(response, pgResp) {
    response.writeHead(200, { 'Content-Type': 'text/html' });
    response.end(pgResp);
}

function sendPublicFileAnd200(response, pgResp, contentType) {
    response.writeHead(200, { 'Content-Type': contentType });
    response.end(pgResp);
}

function sendRegisterPageAnd301(response, urlHost) {
    response.writeHead(301, {Location: '/' });
    response.end();
}

exports.notGetDataAndSend501 = notGetDataAndSend501;
exports.notFindPageAndSend404 = notFindPageAndSend404;
exports.sendJsonStringAnd200 = sendJsonStringAnd200;
exports.sendHtmlPageAnd200 = sendHtmlPageAnd200;
exports.sendPublicFileAnd200 = sendPublicFileAnd200;
exports.sendRegisterPageAnd301 = sendRegisterPageAnd301;