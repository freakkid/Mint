const express = require('express'),
    url = require('url'),
    tools = require('../tools/tools'),
    service = require('../models/service'),
    message = require('../tools/message'),
    defaultConfig = require('../config/default.js'),
    router = express.Router();



// check GET
router.get('/', function (req, res) {
    const params = url.parse(req.url, true).query,
        key = params['query'].toLowerCase();
    switch (key) {
        case 'username':
            service.checkUsernameExist(params['value'], function(err, result) {
                if (!err && result.length == 0) {
                    res.status(200).json({ [key]: 'false' });
                } else {
                    res.status(200).json({ [key]: 'true' });
                }
            });
            break;
        case 'studentid':
            service.checkStudentIDExist(params['value'], function(err, result) {
                if (!err && result.length == 0) {
                    res.status(200).json({ [key]: 'false' });
                } else {
                    res.status(200).json({ [key]: 'true' });
                }
            });
            break;
        case 'phone':
            service.checkPhoneExist(params['value'], function(err, result) {
                if (!err && result.length == 0) {
                    res.status(200).json({ [key]: 'false' });
                } else {
                    res.status(200).json({ [key]: 'true' });
                }
            });
            break;
        case 'email':
            service.checkEmailExist(params['value'], function(err, result) {
                if (!err && result.length == 0) {
                    res.status(200).json({ [key]: 'false' });
                } else {
                    res.status(200).json({ [key]: 'true' });
                }
            });
            break;
        default:
        res.status(400).end();
    }
});

function checkCallback(err, result) {
    if (!err && result.length == 0) {
        res.status(200).json({ [key]: 'false' });
    } else {
        res.status(200).json({ [key]: 'true' });
    }
}

module.exports = router;
