const express = require('express'),
    url = require('url'),
    tools = require('../tools/tools'),
    service = require('../models/service'),
    message = require('../tools/message'),
    defaultConfig = require('../config/default.js'),
    router = express.Router();

// signin POST / signOUT DELETE

// login in POST
// valid username and password -- give session ID and 200
// invalid -- give not-empty returnMessage
router.post('/', function (req, res) {
    // check username and password empty
    var returnMessage = service.checkUsernameAndPasswordValid(req.body);
    if (returnMessage.USERNAMEERROR === ""  && returnMessage.PASSWORDERROR === "") {
        var newKey = tools.generateKey(); // get new key
        service.loginByUsernameAndPassword(req.body, newKey, function (err, result) {
            if (err) {  // server error
                returnMessage.PASSWORDERROR = message.ServerError;
                res.status(500).json(returnMessage);
            } else if (result.result.nModified == 1) { // update key successfully
                res.cookie(defaultConfig.keyName, newKey, { maxAge: defaultConfig.maxAge, httpOnly: false });
                res.status(200).json(returnMessage);
            } else { // not find this user
                returnMessage.PASSWORDERROR = message.LoginFail;
                res.status(401).json(returnMessage);
            }
        });
    } else { // empty username or password
        res.status(400).json(returnMessage);
    }
});

// sigin out DELETE
// valid sessionID -- log out successfully
// invalid sessionID -- log out fail
router.delete('/', function (req, res) {
    service.logoutByKey(req.cookies._key, function (err, result) {
        if (err) {
            res.status(500).send(message.ServerError);
        } else if (result.result.nModified == 1) { // delete key successfully
                        res.clearCookie(defaultConfig.keyName);
            res.status(204).end();
        } else { // not find this user
            res.status(401).send(message.LoginFail);
        }
    });
});

module.exports = router;
