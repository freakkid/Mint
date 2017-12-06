
// red dot disappear when mouse leave button
$('#button').mouseleave(function() {
    $('#control-ring li').find(".unread").hide();
});

// send get request to server and get random number
// check the response data is valid number or not
// if valid show red dot and the number
$('#control-ring li').on('click', function () {
    $(this).find(".unread").show();
    $.ajax({
        url: "/",
        type: "GET",
        dataType: "text",
        context: this,
        error: function (error) {
            alert("Connection error" + error);
        },
        success: function (data) {
            if (isValidNum(data)) {
                $(this).find('.unread').text(data);
                $(this).find(".unread").show();
            }
        },
    });
});

// send get request to server and get the sum of li
// check the response data is valid number or not
// if valid show the sum in big result circle
$('#info-bar').on('click', function () {
    var getData = [];
    $('#control-ring li').each(function () {
        if (!isValidNum($(this).find('span.unread').text())) {
            return false;
        }
        getData.push($(this).find('span.unread').text());
    });

    if (getData.length == 5) {
        $(this).find('.result').text(getSumOfArray(getData));
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