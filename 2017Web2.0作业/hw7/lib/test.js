`use strict`;

function hello() {
    console.log("sdf");
}

function world() {
    console.log("vbnm");
}
const fs = require("fs");

const DATAJSONFILE = 'data.json';

function test() {
    fs.readFile(DATAJSONFILE, function (error, data) {
        if (!error) {
            console.log(data);
            fs.writeFile(DATAJSONFILE, "1234");
        }
    });
}

test();
exports.hello = hello;
exports.world = world;