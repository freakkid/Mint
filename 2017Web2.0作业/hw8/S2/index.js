$(function () {
    const allLis = $('#control-ring li'),
        infoBar = $('#info-bar'),
        apb = $('.apb');

    allLis.attr('randomID', generateRandomID());    // new attr: all lis get when new starting as a ID of a session

    function resetAll() {
        resetButton();
        allLis.find("span.unread").hide();
        clearBubbleResult();
    }

    function clearBubbleResult() {
        if (infoBar.find('p.result').text() !== "") {
            infoBar.find('p.result').text("");
        }
    }

    function resetButton() {
        allLis.removeClass("no-pointer-active").removeClass("no-pointer-active-color").
            addClass("pointer-active-color");
        allLis.attr('randomID', generateRandomID());
    }

    // red dot disappear when mouse leave button
    $('#button').mouseleave(resetAll);
    $('#button').hover(resetAll);

    // send get request to server and get random number
    // check the response data is valid number or not
    // if valid show red dot and the number
    function allLisClickHandle() {
        clearBubbleResult();
        var that = arguments.length <= 1 ? $(this) : arguments[0],  // check number of arguments
        callback = arguments[1];
        
        allLis.addClass("no-pointer-active");   // all lis are disable click
        const thisId = that.attr('id'),      // get id of current li 
            randomID = that.attr('randomID');      // get raandom ID of current li
        otherLis = allLis.not('#' + thisId).filter(function() {
            return $(this).hasClass("pointer-active-color") == true;
        }); // other non-clicked lis with class["pointer-active-color"]
        otherLis.removeClass("pointer-active-color").addClass("no-pointer-active-color");   // diable color

        that.find('span.unread').text('···').show();
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
                    $('#' + thisId + ' span.unread').text(data);    // display number
                    that.removeClass("pointer-active-color").addClass("no-pointer-active-color");    // diable current li color
                    otherLis.removeClass("no-pointer-active").removeClass("no-pointer-active-color").addClass("pointer-active-color");
                    if (callback) {
                        callback();
                    }
                }
            },
        });
    }

    allLis.on('click', allLisClickHandle);

    // send get request to server and get the sum of li
    // check the response data is valid number or not
    // if valid show the sum in big result circle
    infoBar.on('click', function () {
        var getData = [];
        allLis.each(function () {
            if (!isValidNum($(this).find('span.unread').text())) {
                return false;
            }
            getData.push($(this).find('span.unread').text());
        });
        if (getData.length == 5) {
            $(this).find('p.result').text(getSumOfArray(getData));
            resetButton();
        }
    });

    apb.on('click', function () {
        resetAll();
        aFingerZen();
    });

    function oneLiClick(liObject, callback) {
        allLisClickHandle(liObject, callback);
    }
    
    function aFingerZen() {
        oneLiClick($('#A'), function() {
            oneLiClick($('#B'), function() {
                oneLiClick($('#C'), function() {
                    oneLiClick($('#D'), function() {
                        oneLiClick($('#E'), function() {
                            infoBar.click();
                        })
                    })
                });
            });
        });
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
});

