$(function () {
    // error infomation
    const EMPTY_USERNAME = "Please fill out the username",
        EMPTY_PASSWORD = "Please fill out the password",
        FORMAT_USERNAME = "Username is not formatted properly";
    // ------------------------------------------

    // check if empty ---------------------------------------

    function checkIfUsernameInvalid() {
        if (isEmpty($("input[name=username]").val())) {
            $('#username-error').text(EMPTY_USERNAME);
            return true;
        } else if (!isUsernameValid($("input[name=username]").val())) {
            $('#username-error').text(FORMAT_USERNAME);
            return true;
        }
        $('#username-error').text('');
        return false;
    }

    function checkIfPasswordEmpty() {
        if (isEmpty($("input[name=password]").val())) {
            $('#password-error').text(EMPTY_PASSWORD);
            return true;
        }
        $('#password-error').text('');
        return false;
    }
    // ----------------------------------------------------------

    // click event-----------------------------------------------
    // login 
    $("input[name=LOGIN]").click(function () {
        // check if empty input --------------------
        var isValid = true;
        if (checkIfUsernameInvalid()) {
            isValid = false;
        }
        if (checkIfPasswordEmpty() && isValid) {
            isValid = false;
        }
        // request if valid
        if (isValid) {
            $.ajax({
                url: "/users",
                data: $("input[name='username'], input[name='password']").serialize(),
                type: "POST",
                processData: false,
                contentType: "application/x-www-form-urlencoded",
                error: function (jqXHR, textStatus, errorThrown) {
                    if (jqXHR.status == 400 || jqXHR.status == 401 || jqXHR.status == 500) {
                        const resultJSON = JSON.parse(jqXHR.responseText);
                        $('#username-error').text(resultJSON.USERNAMEERROR);
                        $('#password-error').text(resultJSON.PASSWORDERROR);
                    } else {
                        alert("Connection error" + error);
                    }
                },
                success: function (data, status, xhr) {
                    window.location.href = "http://" + window.location.host + '?username=' + data.USERNAME;
                },
            });
        }
    });
    // jump to register page
    $('p.to-register').click(function () {
        window.location.href = "http://" + window.location.host + '/regist';
    });

});