const crypto = require('crypto');

function passwordMD5Hash(password) {
    return crypto.createHash('md5').update(password).digest("hex");
}

// generate uuid key as session ID
function generateKey() {
    return crypto.createHash('sha1').update(
        (new Date()).valueOf().toString() + Math.random().toString()).digest('hex');
}

exports.passwordMD5Hash = passwordMD5Hash;
exports.generateKey = generateKey;