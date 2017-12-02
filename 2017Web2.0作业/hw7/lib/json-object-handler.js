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
                fs.writeFileSync(DATAJSONFILE, '[]', 'utf8');
            } else {
                return false;
            }
        }
    });
    return true;
}


// check if exists same user info and return returnMessage
// first check post data format is valid or not and returnMessage['INVALID'] give info
// if exists same user info, add duplicate title into returnMessage['DUPLICATION']
// if not exists same user info, returnMessage['DUPLICATION'] is an empty string
// add new user into json data file
// in both cases, returnMessage['USERNAME'] save username of postDatas
function addIntoDataAndSendJsonResult(DATAJSONFILE, postDatas) {
    var returnMessage = { 'DUPLICATION': '', 'USERNAME': postDatas['username'], 'INVALID': '' };
    // check post data format
    if (!(/^[a-zA-Z][\w]{5,17}$/.test(postDatas['username']))) {
        returnMessage['INVALID'] += 'USERNAME';
    }
    if (!(/^(?!0)[\d]{8}$/.test(postDatas['studentid']))) {
        returnMessage['INVALID'] += 'STUDENTID';
    }
    if (!(/^(?!0)[\d]{11}$/.test(postDatas['phone']))) {
        returnMessage['INVALID'] += 'PHONE';
    }
    if (!(/^[a-zA-Z_\-]+@(([a-zA-Z_\-])+\.)+[a-zA-Z]{2,4}$/.test(postDatas['email']))) {
        returnMessage['INVALID'] += 'EMAIL';
    }
    if (returnMessage['INVALID'] != '') {
        return returnMessage;
    }
    // get json string from file and get json array from json string
    var jsonUserArray = JSON.parse(fs.readFileSync(DATAJSONFILE, 'utf8'));
    // if find same value, add into duplication info
    jsonUserArray.forEach(function (element) {
        if (element['username'] == postDatas['username']) {
            returnMessage['DUPLICATION'] += 'USERNAME';
        }
        if (element['studentid'] == postDatas['studentid']) {
            returnMessage['DUPLICATION'] += 'STUDENTID';
        }
        if (element['phone'] == postDatas['phone']) {
            returnMessage['DUPLICATION'] += 'PHONE';
        }
        if (element['email'] == postDatas['email']) {
            returnMessage['DUPLICATION'] += 'EMAIL';
        }
    });
    // if not exist duplication, add the new one into data file
    if (returnMessage['DUPLICATION'] == '') {
        jsonUserArray.push(postDatas);
        fs.writeFileSync(DATAJSONFILE, JSON.stringify(jsonUserArray));
    }
    return returnMessage;
}

function checkDuplicateData(DATAJSONFILE, params) {
    switch (params['query'].toLowerCase()) {
        case 'username':
            if (getUserInfoByUsername(DATAJSONFILE, params['value'])) {
                return { 'username': 'true' };
            } else {
                return { 'username': 'false' };
            }
            break;
        case 'studentid':
            if (getUserInfoByStudentId(DATAJSONFILE, params['value'])) {
                return { 'studentid': 'true' };
            } else {
                return { 'studentid': 'false' };
            }
            break;
        case 'phone':
            if (getUserInfoByPhone(DATAJSONFILE, params['value'])) {
                return { 'phone': 'true' };
            } else {
                return { 'phone': 'false' };
            }
            break;
        case 'email':
            if (getUserInfoByEmail(DATAJSONFILE, params['value'])) {
                return { 'email': 'true' };
            } else {
                return { 'email': 'false' };
            }
            break;
        default:
            return { '': '' };
    }
}

// find user info with same username and get user info
// to send a detail page
function getUserInfoByUsername(DATAJSONFILE, usernameParam) {
    // get json array from json string
    var jsonUserArray = JSON.parse(fs.readFileSync(DATAJSONFILE, 'utf8'));
    // find same value
    return jsonUserArray.find(function (element) {
        return element['username'] == usernameParam;
    });
}

function getUserInfoByStudentId(DATAJSONFILE, studentidParam) {
    // get json array from json string
    var jsonUserArray = JSON.parse(fs.readFileSync(DATAJSONFILE, 'utf8'));
    // find same value
    return jsonUserArray.find(function (element) {
        return element['studentid'] == studentidParam;
    });
}

function getUserInfoByPhone(DATAJSONFILE, phoneParam) {
    // get json array from json string
    var jsonUserArray = JSON.parse(fs.readFileSync(DATAJSONFILE, 'utf8'));
    // find same value
    return jsonUserArray.find(function (element) {
        return element['phone'] == phoneParam;
    });
}

function getUserInfoByEmail(DATAJSONFILE, emailParam) {
    // get json array from json string
    var jsonUserArray = JSON.parse(fs.readFileSync(DATAJSONFILE, 'utf8'));
    // find same value
    return jsonUserArray.find(function (element) {
        return element['email'] == emailParam;
    });
}

exports.isDataFileExist = isDataFileExist;
exports.addIntoDataAndSendJsonResult = addIntoDataAndSendJsonResult;
exports.checkDuplicateData = checkDuplicateData;
exports.getUserInfoByUsername = getUserInfoByUsername;