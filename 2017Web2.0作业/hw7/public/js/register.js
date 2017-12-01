$(function () {
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
        // clear text
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
                        window.location.href = '?username=' + data.USERNAME;
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

