$(function () {
    const allLis = $('#control-ring li'),
        infoBar = $('#info-bar');
    allLis.attr('randomID', generateRandomID());    // new attr: all lis get when new starting as a ID of a session
    // red dot disappear when mouse leave button
    $('#button').mouseleave(function () {
        allLis.removeClass("no-pointer-active").removeClass("no-pointer-active-color").addClass("pointer-active-color");
        allLis.find("span.unread").hide();
        allLis.attr('randomID', generateRandomID());
        infoBar.find('p.result').text("");
    });

    // send get request to server and get random number
    // check the response data is valid number or not
    // if valid show red dot and the number
    allLis.on('click', function () {
        allLis.addClass("no-pointer-active");   // all lis are disable click
        const thisId = $(this).attr('id'),      // get id of current li 
            randomID = $(this).attr('randomID');      // get raandom ID of current li
        const otherLis = allLis.not('#' + thisId).not("no-pointer-active"); // other non-clicked lis
        otherLis.removeClass("pointer-active-color").addClass("no-pointer-active-color");   // diable color

        $(this).find('span.unread').text('···');
        $(this).find("span.unread").show();
        $.ajax({
            url: "/",
            type: "GET",
            dataType: "text",
            context: this,
            aysnc: false,
            error: function (error) {
                alert("Connection error" + error);
            },
            success: function (data) {
                var timeID = setTimeout(function (data) {
                    $('#' + thisId + ' span.unread').text(data);    // display number
                    otherLis.removeClass("no-pointer-active").removeClass("no-pointer-active-color").addClass("pointer-active-color");
                    $(this).addClass("no-pointer-active-color");    // diable current li color
                }, 1000, data);
                if ($('#' + thisId).attr('randomID') != randomID) { // check if restart ask for new number from server
                    clearTimeout(timeID);
                }
            }
        });
    });


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
        }

    });

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

