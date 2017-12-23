const defaultConfig = require('../config/default.js'),
    MongoClient = require('mongodb').MongoClient;

// create database
function createDatabase(callback) {
    MongoClient.connect(defaultConfig.mongodbUrl, function (err, db) {
        if (err) callback(err);
        db.close();
        callback();
    });
}

// create collections
function createTable(callback) {
    MongoClient.connect(defaultConfig.mongodbUrl, function (err, db) {
        if (err) callback(err);
        var dbase = db.db(defaultConfig.databaseName);
        dbase.createCollection(defaultConfig.tableName, function (err, res) {
            if (err) callback(err);
            db.close();
            callback();
        });
    });
}

exports.createDatabase = createDatabase;
exports.createTable = createTable;
