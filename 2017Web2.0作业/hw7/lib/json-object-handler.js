`use strict`;
const fs = require("fs");
const sendPage = require("./send-page.js");

// check if data.json exist, if not exist generate one 
// return general result -- true or false
function isDataFileExist(DATAJSONFILE) {
    fs.stat(DATAJSONFILE, function (error, stats) {
        if (error) {
            // if data file does not exist, create one
            if (error.code == 'ENOENT') {
                fs.writeFile(DATAJSONFILE, '[]');
            } else {
                return false;
            }
        }
    });
    return true;
}


// check if exists same user info and return returnMessage
// if exists same user info, add duplicate title into returnMessage['DUPLICATION']
// if not exists same user info, returnMessage['DUPLICATION'] is an empty string
// add new user into json data file
// in both cases, returnMessage['USERNAME'] save username of postDatas
function addIntoDataAndSendJsonResult(response, DATAJSONFILE, postDatas) {
    var returnMessage = { 'DUPLICATION': '', 'USERNAME': postDatas['username'] };
    // get json string from file
    fs.readFile(DATAJSONFILE, function (error, data) {
        // get json array from json string
        var jsonUserArray = JSON.parse(data),
            i = 0;
        // if find same value, add into duplication info
        for (; i < jsonUserArray.length; i++) {
            if (jsonUserArray[i]['username'] == postDatas['username']) {
                returnMessage['DUPLICATION'] += 'USERNAME';
            } 
            if (jsonUserArray[i]['studentid'] == postDatas['studentid']) {
                returnMessage['DUPLICATION'] += 'STUDENTID';
            }
            if (jsonUserArray[i]['phone'] == postDatas['phone']) {
                returnMessage['DUPLICATION'] += 'PHONE';
            }
            if (jsonUserArray[i]['email'] == postDatas['email']) {
                returnMessage['DUPLICATION'] += 'EMAIL';
            }
        }
        // if not exist duplication, add the new one into data file
        if (returnMessage['DUPLICATION'] == '') {
            jsonUserArray.push(postDatas);
            fs.writeFile(DATAJSONFILE, JSON.stringify(jsonUserArray));
        }
        sendPage.sendJsonStringAnd200(response, JSON.stringify(returnMessage));
    });
}

// find user info with same username and get user info
// to send a detail page
function getUserInfoByUsername(data, usernameParam) {
    // get json array from json string
    var jsonUserArray = JSON.parse(data),
        userInfo,
        i = 0;
    // find same value
    for (; i < jsonUserArray.length; i++) {
        if (jsonUserArray[i]['username'] == usernameParam) {
            userInfo = jsonUserArray[i];
            break;
        }
    }
    return userInfo;
}
exports.isDataFileExist = isDataFileExist;
exports.addIntoDataAndSendJsonResult = addIntoDataAndSendJsonResult;
exports.getUserInfoByUsername = getUserInfoByUsername;