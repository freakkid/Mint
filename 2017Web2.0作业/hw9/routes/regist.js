const express = require('express'),
    url = require('url'),
    tools = require('../tools/tools'),
    service = require('../models/service'),
    message = require('../tools/message'),
    defaultConfig = require('../config/default.js'),
    router = express.Router();

// signup GET
// valid sessionID -- redirect to details page
// invalid sessionID -- send to signup page
router.get('/', function (req, res) {
    service.checkKey(req.cookies._id, function (err, result) {
        if (err) {
            res.status(500).send(message.ServerError);
        } // valid session ID -- have signed in
        else if (result.length == 1) {
            res.status(302).location('/');
        } else { // not match, send the user's info and message tip
            res.status(200).render('register');
        }
    });
});

module.exports = router;
