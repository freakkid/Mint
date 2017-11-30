`use strict`;
const fs = require("fs");

function checkDuplicationAndAddIntoData(DATAJSONFILE, postDatas) {
    var returnMessage = {};
    // get json string from file
    fs.readFile(DATAJSONFILE, function (error, data) {
        // get json array from json string
        var jsonUserArray = JSON.parse(data),
            i = 0;
        // if find same value, add into duplication info
        for (; i < jsonUserArray.length; i++) {
            if (jsonUserArray[i]['username'] == postDatas['username']) {
                returnMessage['DUPLICATION'] = 'USERNAME';
            } else if (jsonUserArray[i]['studentid'] == postDatas['studentid']) {
                returnMessage['DUPLICATION'] = 'STUDENTID';
            } else if (jsonUserArray[i]['phone'] == postDatas['phone']) {
                returnMessage['DUPLICATION'] = 'PHONE';
            } else if (jsonUserArray[i]['email'] == postDatas['email']) {
                returnMessage['DUPLICATION'] = 'EMAIL';
            }
        }
        // if not exist duplication, add the new one into data file
        if (!returnMessage['DUPLICATION']) {
            jsonUserArray.push(postDatas);
            fs.writeFile(DATAJSONFILE, JSON.stringify(jsonUserArray));
        }
        // add username message
        returnMessage['USERNAME'] = postDatas['username'];
    });
    return returnMessage;
}




exports.checkDuplicationAndAddIntoData = checkDuplicationAndAddIntoData;
exports.world = world;