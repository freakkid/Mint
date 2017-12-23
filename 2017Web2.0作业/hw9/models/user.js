const defaultConfig = require('../config/default.js'),
    tools = require('../tools/tools'),
    init = require('./init');
    MongoClient = require('mongodb').MongoClient;

// insert a new user
function createOneUser(data, callback) {
    MongoClient.connect(defaultConfig.mongodbUrl, function (err, db) {
        if (err) {
            callback(err);
            return;
        }
        var dbase = db.db(defaultConfig.databaseName);
        var collection = dbase.collection(defaultConfig.tableName);
        collection.insert(data, function (err, result) {
            if (err) {
                callback(err);
                return;
            }
            db.close();
            callback(err, result);
        });
    });
}

// find user
function selectUserWhere(where, callback) {
    MongoClient.connect(defaultConfig.mongodbUrl, function (err, db) {
        if (err) {
            callback(err);
            return;
        }
        var dbase = db.db(defaultConfig.databaseName);
        var collection = dbase.collection(defaultConfig.tableName);
        collection.find(where).toArray(function (err, result) {
            if (err) {
                callback(err);
                return;
            }
            db.close();
            callback(err, result);
        });
    });
}

// set key null
function deleteKeyWhere(where, callback) {
    MongoClient.connect(defaultConfig.mongodbUrl, function (err, db) {
        if (err) {
            callback(err);
            return;
        }
        var dbase = db.db(defaultConfig.databaseName);
        var collection = dbase.collection(defaultConfig.tableName);
        collection.update(where, { $set: { "key": tools.generateKey() } }, function (err, result) {
            if (err) {
                callback(err);
                return;
            }
            db.close();
            callback(err, result);
        });
    });
}

// update key by username and password (login)
function updateKeyWhere(where, newKey, callback) {
    MongoClient.connect(defaultConfig.mongodbUrl, function (err, db) {
        if (err) {
            callback(err);
            return;
        }
        var dbase = db.db(defaultConfig.databaseName);
        var collection = dbase.collection(defaultConfig.tableName);
        collection.update(where, { $set: { "key": newKey } }, function (err, result) {
            if (err) {
                callback(err);
                return;
            }
            db.close();
            callback(err, result);
        });
    });
}


exports.createOneUser = createOneUser;
exports.selectUserWhere = selectUserWhere;
exports.deleteKeyWhere = deleteKeyWhere;
exports.updateKeyWhere = updateKeyWhere;