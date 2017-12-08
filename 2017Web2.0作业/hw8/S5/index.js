$(function () {
    const allLis = $('#control-ring li'),
        infoBar = $('#info-bar'),
        apb = $('.apb'),
        orderDisplay = $('#order-display'),
        say = $('#say');

    function resetAll() {
        resetButton();
        allLis.find("span.unread").hide();
        clearBubbleResult();
        orderDisplay.text('');
        say.text('');
    }

    function clearBubbleResult() {
        if (infoBar.find('p.result').text() !== "") {
            infoBar.find('p.result').text("");
        }
    }

    function resetButton() {
        allLis.removeClass("no-pointer-active").removeClass("no-pointer-active-color").
            addClass("pointer-active-color");
        allLis.attr('randomID', generateRandomID());// new attr: all lis get when new starting as a ID of a session
    }

    // red dot disappear when mouse leave button
    $('#button').mouseleave(resetAll);
    $('#button').hover(resetAll);

    //
    // ─── A B C D E HANDLER ──────────────────────────────────────────────────────────
    //
    // send get request to server and get random number
    // check the response data is valid number or not
    // if valid show red dot and the number
    // parament (object, callback, currentSum)
    function aHandler() {
        clearBubbleResult();
        var that = arguments.length <= 1 ? $(this) : arguments[0],  // check number of arguments
            callback = arguments[1],
            currentSum = arguments[2];

        allLis.addClass("no-pointer-active");   // all lis are disable click
        const thisId = that.attr('id'),      // get id of current li 
            randomID = that.attr('randomID'),      // get raandom ID of current li
            otherLis = allLis.not('#' + thisId).filter(function () {
                return $(this).hasClass("pointer-active-color") == true;
            }); // other non-clicked lis with class["pointer-active-color"]
        otherLis.removeClass("pointer-active-color").addClass("no-pointer-active-color");   // diable color

        that.find('span.unread').text('···').show();
        var d = new $.Deferred();
        if (currentSum !== undefined && !!Math.round(Math.random())) {
            d.reject(new RamdonError('A：这不是个天大的秘密' + currentSum, currentSum));
        } else {
            say.text('A：这是个天大的秘密');
        }
        $.ajax({
            url: "/",
            type: "GET",
            dataType: "text",
            aysnc: false,
            error: function (error) {
                alert("Connection error" + error);
            },
            success: function (data) {
                if ($('#' + thisId).attr('randomID') == randomID) { // check if restart ask for new number from server
                    that.removeClass("pointer-active-color").addClass("no-pointer-active-color");    // diable current li color
                    otherLis.removeClass("no-pointer-active").removeClass("no-pointer-active-color").
                        addClass("pointer-active-color");
                    $('#' + thisId + ' span.unread').text(data);    // display number
                    currentSum += parseInt(data);
                    if (callback) {  // if has callback 
                        callback(currentSum);
                    }
                }
            },
        });
        return d.promise();
    }

    function bHandler() {
        clearBubbleResult();
        var that = arguments.length <= 1 ? $(this) : arguments[0],  // check number of arguments
            callback = arguments[1],
            currentSum = arguments[2];

        allLis.addClass("no-pointer-active");   // all lis are disable click
        const thisId = that.attr('id'),      // get id of current li 
            randomID = that.attr('randomID'),      // get raandom ID of current li
            otherLis = allLis.not('#' + thisId).filter(function () {
                return $(this).hasClass("pointer-active-color") == true;
            }); // other non-clicked lis with class["pointer-active-color"]
        otherLis.removeClass("pointer-active-color").addClass("no-pointer-active-color");   // diable color

        that.find('span.unread').text('···').show();
        var d = new $.Deferred();
        if (currentSum !== undefined && !!Math.round(Math.random())) {
            d.reject(new RamdonError('B：我知道' + currentSum, currentSum));
        } else {
            say.text('B：我不知道');
        }
        $.ajax({
            url: "/",
            type: "GET",
            dataType: "text",
            aysnc: false,
            error: function (error) {
                alert("Connection error" + error);
            },
            success: function (data) {
                if ($('#' + thisId).attr('randomID') == randomID) { // check if restart ask for new number from server
                    that.removeClass("pointer-active-color").addClass("no-pointer-active-color");    // diable current li color
                    otherLis.removeClass("no-pointer-active").removeClass("no-pointer-active-color").
                        addClass("pointer-active-color");
                    $('#' + thisId + ' span.unread').text(data);    // display number
                    currentSum += parseInt(data);
                    if (callback) {  // if has callback funtion
                        callback(currentSum);
                    }
                }
            },
        });
        return d.promise();
    }

    function cHandler() {
        clearBubbleResult();
        var that = arguments.length <= 1 ? $(this) : arguments[0],  // check number of arguments
            callback = arguments[1],
            currentSum = arguments[2];

        allLis.addClass("no-pointer-active");   // all lis are disable click
        const thisId = that.attr('id'),      // get id of current li 
            randomID = that.attr('randomID'),      // get raandom ID of current li
            otherLis = allLis.not('#' + thisId).filter(function () {
                return $(this).hasClass("pointer-active-color") == true;
            }); // other non-clicked lis with class["pointer-active-color"]
        otherLis.removeClass("pointer-active-color").addClass("no-pointer-active-color");   // diable color

        that.find('span.unread').text('···').show();
        var d = new $.Deferred();
        if (currentSum !== undefined && !!Math.round(Math.random())) {
            d.reject(new RamdonError('C：你知道' + currentSum, currentSum));
        } else {
            say.text('C：你不知道');
        }
        $.ajax({
            url: "/",
            type: "GET",
            dataType: "text",
            aysnc: false,
            error: function (error) {
                alert("Connection error" + error);
            },
            success: function (data) {
                if ($('#' + thisId).attr('randomID') == randomID) { // check if restart ask for new number from server
                    that.removeClass("pointer-active-color").addClass("no-pointer-active-color");    // diable current li color
                    otherLis.removeClass("no-pointer-active").removeClass("no-pointer-active-color").
                        addClass("pointer-active-color");
                    $('#' + thisId + ' span.unread').text(data);    // display number
                    currentSum += parseInt(data);
                    if (callback) {  // if has callback funtion
                        callback(currentSum);
                    }
                }
            },
        });
        return d.promise();
    }

    function dHandler() {
        clearBubbleResult();
        var that = arguments.length <= 1 ? $(this) : arguments[0],  // check number of arguments
            callback = arguments[1],
            currentSum = arguments[2];

        allLis.addClass("no-pointer-active");   // all lis are disable click
        const thisId = that.attr('id'),      // get id of current li 
            randomID = that.attr('randomID'),      // get raandom ID of current li
            otherLis = allLis.not('#' + thisId).filter(function () {
                return $(this).hasClass("pointer-active-color") == true;
            }); // other non-clicked lis with class["pointer-active-color"]
        otherLis.removeClass("pointer-active-color").addClass("no-pointer-active-color");   // diable color

        that.find('span.unread').text('···').show();
        var d = new $.Deferred();
        if (currentSum !== undefined && !!Math.round(Math.random())) {
            d.reject(new RamdonError('D：他知道' + currentSum, currentSum));
        } else {
            say.text('D：他不知道');
        }
        $.ajax({
            url: "/",
            type: "GET",
            dataType: "text",
            aysnc: false,
            error: function (error) {
                alert("Connection error" + error);
            },
            success: function (data) {
                if ($('#' + thisId).attr('randomID') == randomID) { // check if restart ask for new number from server
                    that.removeClass("pointer-active-color").addClass("no-pointer-active-color");    // diable current li color
                    otherLis.removeClass("no-pointer-active").removeClass("no-pointer-active-color").
                        addClass("pointer-active-color");
                    $('#' + thisId + ' span.unread').text(data);    // display number
                    currentSum += parseInt(data);
                    if (callback) {  // if has callback funtion
                        callback(currentSum);
                    }
                }
            },
        });
        return d.promise();
    }

    function eHandler() {
        clearBubbleResult();
        var that = arguments.length <= 1 ? $(this) : arguments[0],  // check number of arguments
            callback = arguments[1],
            currentSum = arguments[2];

        allLis.addClass("no-pointer-active");   // all lis are disable click
        const thisId = that.attr('id'),      // get id of current li 
            randomID = that.attr('randomID'),      // get raandom ID of current li
            otherLis = allLis.not('#' + thisId).filter(function () {
                return $(this).hasClass("pointer-active-color") == true;
            }); // other non-clicked lis with class["pointer-active-color"]
        otherLis.removeClass("pointer-active-color").addClass("no-pointer-active-color");   // diable color

        that.find('span.unread').text('···').show();
        var d = new $.Deferred();
        if (currentSum !== undefined && !!Math.round(Math.random())) {
            d.reject(new RamdonError('E：才不怪' + currentSum, currentSum));
        } else {
            say.text('E：才怪');
        }
        $.ajax({
            url: "/",
            type: "GET",
            dataType: "text",
            aysnc: false,
            error: function (error) {
                alert("Connection error" + error);
            },
            success: function (data) {
                if ($('#' + thisId).attr('randomID') == randomID) { // check if restart ask for new number from server
                    that.removeClass("pointer-active-color").addClass("no-pointer-active-color");    // diable current li color
                    otherLis.removeClass("no-pointer-active").removeClass("no-pointer-active-color").
                        addClass("pointer-active-color");
                    $('#' + thisId + ' span.unread').text(data);    // display number
                    currentSum += parseInt(data);
                    if (callback) {  // if has callback funtion
                        callback(currentSum);
                    }
                }
            },
        });
        return d.promise();
    }

    $('#A').click(aHandler);
    $('#B').click(bHandler);
    $('#C').click(cHandler);
    $('#D').click(dHandler);
    $('#E').click(eHandler);
    // ────────────────────────────────────────────────────────────────────────────────


    // send get request to server and get the sum of li
    // check the response data is valid number or not
    // if valid show the sum in big result circle
    function bubbleHandler() {
        var that,
            currentSum,
            getData = [];
        if (arguments.length <= 1) {    // check number of arguments
            that = $(this);             // called by click
        } else {                        // has paramenter is callback
            that = arguments[0];
            currentSum = arguments[1];
        }

        // no pass currentSum
        if (currentSum == undefined) {
            allLis.each(function () {
                if (!isValidNum($(this).find('span.unread').text())) {
                    return false;
                }
                getData.push($(this).find('span.unread').text());
            });
            if (getData.length == 5) {
                currentSum = getSumOfArray(getData);
                resetButton();
            }
        }

        // display currentSum if not undefined
        if (currentSum !== undefined) {
            that.find('p.result').text(currentSum);
            var d = new $.Deferred();
            // random fail
            if (!!arguments[1] && !!Math.round(Math.random())) {
                d.reject(new RamdonError('大气泡：楼主异步调用战斗力不感人，目测不超过' + currentSum, currentSum));
            } else {
                say.text('大气泡：楼主异步调用战斗力感人，目测不超过' + currentSum);
            }
            resetButton();
        }
        return d.promise();
    }

    infoBar.on('click', bubbleHandler);
    // ────────────────────────────────────────────────────────────────────────────────

    apb.on('click', function () {
        resetAll();
        ultimateSecret(getRandomOrderArray());
    });

    function oneLiClick(objectID, callback, currentSum) {
        var objectHandler;
        switch (objectID) {
            case '#A':
                objectHandler = aHandler;
                break;
            case '#B':
                objectHandler = bHandler;
                break;
            case '#C':
                objectHandler = cHandler;
                break;
            case '#D':
                objectHandler = dHandler;
                break;
            case '#E':
                objectHandler = eHandler;
                break;
        }
        return objectHandler($(objectID), callback, currentSum).fail(function (err) {
            say.text(err.message);
        });
    }

    function ultimateSecret(order) {
        var currentSum = 0;
        oneLiClick(order[0], function (currentSum) {
            oneLiClick(order[1], function (currentSum) {
                oneLiClick(order[2], function (currentSum) {
                    oneLiClick(order[3], function (currentSum) {
                        oneLiClick(order[4], function (currentSum) {
                            bubbleHandler(infoBar, currentSum).fail(function (err) {
                                say.text(err.message);
                            });
                        }, currentSum);
                    }, currentSum);
                }, currentSum);
            }, currentSum);
        }, currentSum);
    }
    // ────────────────────────────────────────────────────────────────────────────────

    // get random order and display
    function getRandomOrderArray() {
        var order = ['#A', '#B', '#C', '#D', '#E'],
            i = 1,
            displayOrder = [];
        swap(Math.floor(Math.random() * 5), 0, order);// 0-4
        for (; i < 4; i++) {
            swap(Math.floor(Math.random() * (4 - i) + i + 1), i, order);
        }
        order.forEach(function (element) {
            displayOrder.push(element.slice(-1));
        })
        // display order
        orderDisplay.text(displayOrder.join(' '));
        return order;
    }

    // check if number valid
    function isValidNum(num) {
        return $.isNumeric(num) && num % 1 === 0 && num >= 1 && num <= 10;
    }

    // add all item of array    
    function getSumOfArray(valueArray) {
        return valueArray.reduce((a, b) => (parseInt(a) + parseInt(b)), 0);
    }

    function generateRandomID() {
        return Math.random();
    }

    // swap two item in array by index
    function swap(t, i, array) {
        array[t] = [array[i], array[i] = array[t]][0];
    }

    // customed error
    function RamdonError(message, currentSum) {
        this.message = message || "RamdonError";
        this.name = "RamdonError";
        this.currentSum = currentSum;
    }
    RamdonError.prototype = new Error();
    RamdonError.prototype.constructor = RamdonError;
});

