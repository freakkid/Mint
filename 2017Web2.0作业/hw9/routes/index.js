const express = require('express'),
    url = require('url'),
    tools = require('../tools/tools'),
    service = require('../models/service'),
    message = require('../tools/message'),
    defaultConfig = require('../config/default.js'),
    router = express.Router();

// details GET / login page GET

// valid sessionID -- send to details page and give message if parameter is others' username
// invalid sessionID -- send to login page
router.get('/', function (req, res) {
    const params = url.parse(req.url, true).query;
    service.checkKey(req.cookies._key, function (err, result) {
        if (err) {
            res.status(500).send(message.ServerError);
        } // valid session ID -- have signed in
        else if (result.length == 1) {
            if (params.username) { // if has username parameter
                if (params.username == result[0]._id) { // if username and key match the same user
                    res.status(200).render('details', { // send the user's info
                        Username: result[0]._id, StudentID: result[0].studentid,
                        Email: result[0].email, Phone: result[0].phone
                    });
                } else { // not match, send the user's info and message tip
                    res.status(401).render('details', {
                        Username: result[0]._id, StudentID: result[0].studentid,
                        Email: result[0].email, Phone: result[0].phone,
                        Message: message.AccseeOwnData
                    });
                }
            } else { // no username parameter
                res.status(302).setHeader('Location', '/?username='+result[0]._id);
                res.end();
            }
        }  // invalid session ID -- not sign in
        else {
            if (Object.keys(req.query).length === 0) {
                res.status(200).render('login');
            } else { // no username parameter
                res.status(302).setHeader('Location', '/');
                res.end();
            }
        }
    });
});


module.exports = router;
