$(function () {
    // check if loses focus and give error tips
    $("input[name=username]").blur(function () {
        if (!(/^[a-zA-Z][\w]{5,17}$/.test($("input[name=username]").val()))) {
            $('#username-error').text('6~18 English letters, numbers or underscores, must begin with an English letter');
        } else {
            $('#username-error').text('');
            $.get(
                "/check",
                { query: 'username', value: $("input[name=username]").val()},
                function(data) {
                    if (data.username == "true") {
                        $('#username-error').text('Username has been occupied');
                    }
                }
            );
        }
    });
    $("input[name=studentid]").blur(function () {
        if (!(/^(?!0)[\d]{8}$/.test($("input[name=studentid]").val()))) {
            $('#studentid-error').text('8 digits, cannot start with 0');
        } else {
            $('#studentid-error').text('');
            $.get(
                "/check",
                { query: 'studentid', value: $("input[name=studentid]").val()},
                function(data) {
                    if (data.studentid == "true") {
                        $('#studentid-error').text('StudentId has been occupied');
                    }
                }
            );
        }
    });
    $("input[name=phone]").blur(function () {
        if (!(/^(?!0)[\d]{11}$/.test($("input[name=phone]").val()))) {
            $('#phone-error').text('11 digits, cannot start with 0');
        } else {
            $('#phone-error').text('');
            $.get(
                "/check",
                { query: 'phone', value: $("input[name=phone]").val()},
                function(data) {
                    if (data.phone == "true") {
                        $('#phone-error').text('Phone has been occupied');
                    }
                }
            );
        }
    });
    $("input[name=email]").blur(function () {
        if (!(/^[a-zA-Z_\-]+@(([a-zA-Z_\-])+\.)+[a-zA-Z]{2,4}$/.test($("input[name=email]").val()))) {
            $('#email-error').text('Email format is illegal');
        } else {
            $('#email-error').text('');
            $.get(
                "/check",
                { query: 'email', value: $("input[name=email]").val()},
                function(data) {
                    if (data.email == "true") {
                        $('#email-error').text('Email has been occupied');
                    }
                }
            );
        }
    });
    // ────────────────────────────────────────────────────────────────────────────────

    // clear all form data
    $("input[name=RESET]").click(function () {
        // clear input box
        $("input[name=username]").val('');
        $("input[name=studentid]").val('');
        $("input[name=phone]").val('');
        $("input[name=email]").val('');

        // clear error text
        $('#username-error').text('');
        $('#studentid-error').text('');
        $('#phone-error').text('');
        $('#email-error').text('');
    });

    $("input[name=SUBMIT]").click(function () {
        // clear error text
        $('#username-error').text('');
        $('#studentid-error').text('');
        $('#phone-error').text('');
        $('#email-error').text('');

        // check if input string valid
        var isValid = true;
        if (!(/^[a-zA-Z][\w]{5,17}$/.test($("input[name=username]").val()))) {
            isValid = false;
            $('#username-error').text('6~18 English letters, numbers or underscores, must begin with an English letter');
        }
        if (!(/^(?!0)[\d]{8}$/.test($("input[name=studentid]").val()))) {
            isValid = false;
            $('#studentid-error').text('8 digits, cannot start with 0');
        }
        if (!(/^(?!0)[\d]{11}$/.test($("input[name=phone]").val()))) {
            isValid = false;
            $('#phone-error').text('11 digits, cannot start with 0');
        }
        if (!(/^[a-zA-Z_\-]+@(([a-zA-Z_\-])+\.)+[a-zA-Z]{2,4}$/.test($("input[name=email]").val()))) {
            isValid = false;
            $('#email-error').text('Email format is illegal');
        }

        if (isValid) {
            $.ajax({
                cache: true,
                url: "/",
                data: $("input[name='username'], input[name='studentid'], input[name='phone'], input[name='email']").serialize(),
                type: "POST",
                processData: false,
                contentType: "application/x-www-form-urlencoded",

                error: function (error) {
                    alert("Connection error" + error);
                },
                success: function (data) {
                    if (data.DUPLICATION == "") {
                        // if successful register jump to details page
                        window.location.href = "http://" + window.location.host + '?username=' + data.USERNAME;
                    } else {
                        // if fail to register set error info if exists duplicate info
                        if ((data.DUPLICATION).indexOf('USERNAME') != -1) {
                            $('#username-error').text('Username has been occupied');
                        }
                        if (data.DUPLICATION.indexOf('STUDENTID') != -1) {
                            $('#studentid-error').text('StudentId has been occupied');
                        }
                        if (data.DUPLICATION.indexOf('PHONE') != -1) {
                            $('#phone-error').text('Phone has been occupied');
                        }
                        if (data.DUPLICATION.indexOf('EMAIL') != -1) {
                            $('#email-error').text('Email has been occupied');
                        }
                    }
                },
            });
        }
    });
});

