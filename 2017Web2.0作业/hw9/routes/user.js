const express = require('express'),
    url = require('url'),
    tools = require('../tools/tools'),
    service = require('../models/service'),
    message = require('../tools/message'),
    defaultConfig = require('../config/default.js'),
    router = express.Router();


// signup POST
// check format ---> check dupliaction and register
router.post('/', function (req, res) {
    // check post data validation
    var returnMessage = service.checkRigisterParamsValid(req.body);
    if (service.ifNoError(returnMessage)) { //  no fotmat error
        const key = tools.generateKey();
        service.checkRigisterParamsDuplicate(req.body, key, function(err, result, returnDuplicationMessage) {
            if (err) {  // as server error
                returnMessage.PASSWORDERROR = message.ServerError;
                res.status(500).json(returnMessage);
            } else if (returnDuplicationMessage) {  // if duplicate, send error
                res.status(400).json(returnDuplicationMessage);   
            } else if (result.result.ok == 1) {    // sign up successfully
                res.cookie(defaultConfig.keyName, key, { maxAge: defaultConfig.maxAge, httpOnly: false });
                res.status(201).json(returnMessage);
            } else {
                returnMessage.PASSWORDERROR = message.ServerError;
                res.status(500).json(returnMessage);
            }
        });
    } else {    // invalid post data
        res.status(400).json(returnMessage);
    }
});

module.exports = router;
