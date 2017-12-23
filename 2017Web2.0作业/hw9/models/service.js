
const user = require("../models/user"),
    tools = require('../tools/tools'),
    message = require('../tools/message'),
    validator = require('../tools/validator');

function checkKey(key, callback) {
    user.selectUserWhere({ 'key': key }, callback);
}

function checkUsernameAndPasswordValid(params) {
    var returnMessage = { 'USERNAMEERROR': '', 'PASSWORDERROR': '', 'USERNAME': params['username'] };
    if (!params['username'] || validator.isEmpty(params['username'])) {
        returnMessage.USERNAMEERROR = message.EmptyUsername;
    } else if (!validator.isUsernameValid(params['username'])) {
        returnMessage.USERNAMEERROR = message.InvalidUsername;
    }
    if (!params['password'] || validator.isEmpty(params['password'])) {
        returnMessage.PASSWORDERROR = message.EmptyPassword;
    }
    return returnMessage;
}

function loginByUsernameAndPassword(params, newKey, callback) {
    user.updateKeyWhere({ '_id': params['username'], 'password': tools.passwordMD5Hash(params['password']) },
        newKey, callback);
}

function logoutByKey(key, callback) {
    user.deleteKeyWhere({ 'key': key }, callback);
}

function registerByParams(params, key, callback) {
    user.createOneUser([{
        '_id': params['username'], 'studentid': params['studentid'],
        "password": tools.passwordMD5Hash(params['password']), "email": params['email'],
        "phone": params['phone'], "key": key
    }], callback);
}

// check format
function checkRigisterParamsValid(params) {
    var returnMessage = {
        'USERNAMEERROR': '', 'STUDENTIDERROR': '', 'EMAILERROR': '', 'PHONEEROR': '',
        'PASSWORDERROR': '', 'COMFIRMERROR': '', 'USERNAME': params['username']
    };
    // check format
    if (!params['username'] || !validator.isUsernameValid(params['username'])) {
        returnMessage.USERNAMEERROR = message.InvalidUsername;
    }
    if (!params['studentid'] || !validator.isStudentIDValid(params['studentid'])) {
        returnMessage.STUDENTIDERROR = message.InvalidStudentid;
    }
    if (!params['email'] || !validator.isEmailValid(params['email'])) {
        returnMessage.EMAILERROR = message.InvalidEmail;
    }
    if (!params['phone'] || !validator.isPhoneValid(params['phone'])) {
        returnMessage.PHONEEROR = message.InvalidPhone;
    }
    if (!params['password'] || !validator.isPasswordValid(params['password'])) {
        returnMessage.PASSWORDERROR = message.InvalidPassword;
    } else if (!params['confirm'] || !validator.ifPasswordMatch(params['password'], params['confirm'])) {
        returnMessage.COMFIRMERROR = message.InvalidConfirm;
    }
    return returnMessage;
}

// check duplicate and register if no duplication 
function checkRigisterParamsDuplicate(params, key, callback) {
    var returnMessage = {
        'USERNAMEERROR': '', 'STUDENTIDERROR': '', 'EMAILERROR': '', 'PHONEEROR': '',
        'PASSWORDERROR': '', 'COMFIRMERROR': '', 'USERNAME': params['username']
    };
    var completedNum = 0;
    checkUsernameExist(params['username'], function (err, result) {
        if (completedNum < 4) {
            completedNum += 1;
            if (err && completedNum <= 4) { // server error
                completedNum = 10;
                callback(err, result);
                return;
            } else if (result.length > 0) { // duplicate
                returnMessage.USERNAMEERROR = message.UsernameDuplicate;
            }
            if (completedNum === 4) {// complete all
                if (ifNoError(returnMessage)) {// no duplication
                    registerByParams(params, key, callback);
                } else {
                    callback(err, result, returnMessage);
                }
            }

        }
    });
    checkStudentIDExist(params['studentid'], function (err, result) {
        if (completedNum < 4) {
            completedNum += 1;
            if (err && completedNum <= 4) { // server error
                completedNum = 10;
                callback(err, result);
                return;
            } else if (result.length > 0) { // duplicate
                returnMessage.STUDENTIDERROR = message.StudentidDuplicate;
            }
            if (completedNum === 4) {// complete all
                if (ifNoError(returnMessage)) {// no duplication
                    registerByParams(params, key, callback);
                } else {
                    callback(err, result, returnMessage);
                }

            }
        }
    });
    checkPhoneExist(params['phone'], function (err, result) {
        if (completedNum < 4) {
            completedNum += 1;
            if (err && completedNum <= 4) { // server error
                completedNum = 10;
                callback(err, result);
                return;
            } else if (result.length > 0) { // duplicate
                returnMessage.PHONEEROR = message.PhoneDuplicate;
            }
            if (completedNum === 4) {// complete all
                if (ifNoError(returnMessage)) {// no duplication
                    registerByParams(params, key, callback);
                } else {
                    callback(err, result, returnMessage);
                }
            }

        }
    });
    checkEmailExist(params['email'], function (err, result) {
        if (completedNum < 4) {
            completedNum += 1;
            if (err && completedNum <= 4) { // server error
                completedNum = 10;
                callback(err, result);
                return;
            } else if (result.length > 0) { // duplicate
                returnMessage.EMAILERROR = message.EmailDuplicate;
            }
            if (completedNum === 4) {// complete all
                if (ifNoError(returnMessage)) {// no duplication
                    registerByParams(params, key, callback);
                } else {
                    callback(err, result, returnMessage);
                }

            }
        }
    });
}

function checkUsernameExist(username, callback) {
    user.selectUserWhere({ '_id': username }, callback);
}

function checkStudentIDExist(studentID, callback) {
    user.selectUserWhere({ 'studentid': studentID }, callback);
}

function checkPhoneExist(phone, callback) {
    user.selectUserWhere({ 'phone': phone }, callback);
}

function checkEmailExist(email, callback) {
    user.selectUserWhere({ 'email': email }, callback);
}

function ifNoError(returnMessage) {
    return returnMessage.USERNAMEERROR === "" && returnMessage.STUDENTIDERROR === "" &&
        returnMessage.EMAILERROR === "" && returnMessage.PHONEEROR === "" &&
        returnMessage.PASSWORDERROR === "" && returnMessage.COMFIRMERROR === "";
}

exports.checkKey = checkKey;
exports.checkUsernameAndPasswordValid = checkUsernameAndPasswordValid;
exports.loginByUsernameAndPassword = loginByUsernameAndPassword;
exports.logoutByKey = logoutByKey;
exports.checkRigisterParamsValid = checkRigisterParamsValid;
exports.checkRigisterParamsDuplicate = checkRigisterParamsDuplicate;
exports.checkUsernameExist = checkUsernameExist;
exports.checkStudentIDExist = checkStudentIDExist;
exports.checkPhoneExist = checkPhoneExist;
exports.checkEmailExist = checkEmailExist;
exports.ifNoError = ifNoError;