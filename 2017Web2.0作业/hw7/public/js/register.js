$(function () {
    // error infomation
    const USERNAME_DUPLICATEERROR = 'Username has been occupied',
        STUDENTID_DUPLICATEERROR = 'StudentId has been occupied',
        PHONE_DUPLICATEERROR = 'Phone has been occupied',
        EMAIL_DUPLICATEERROR = 'Email has been occupied',
        USERNAME_VALIDERROR = '6~18 English letters, numbers or underscores, must begin with an English letter',
        STUDENTID_VALIDERROR = '8 digits, cannot start with 0',
        PHONE_VALIDERROR = '11 digits, cannot start with 0',
        EMAIL_VALIDERROR = 'Email format is illegal';
    // -----------------------------------------------------------

    // check fotmat
    function checkUsernameValidation() {
        if (!(/^[a-zA-Z][\w]{5,17}$/.test($("input[name=username]").val()))) {
            $('#username-error').text(USERNAME_VALIDERROR);
            return false;   // error format
        }
        return true;        // correct format
    }

    function checkStudentidValidation() {
        if (!(/^(?!0)[\d]{8}$/.test($("input[name=studentid]").val()))) {
            $('#studentid-error').text(STUDENTID_VALIDERROR);
            return false;
        }
        return true;
    }

    function checkPhoneValidation() {
        if (!(/^(?!0)[\d]{11}$/.test($("input[name=phone]").val()))) {
            $('#phone-error').text(PHONE_VALIDERROR);
            return false;
        }
        return true;
    }

    function checkEmailValidation() {
        if (!(/^[a-zA-Z_\-]+@(([a-zA-Z_\-])+\.)+[a-zA-Z]{2,4}$/.test($("input[name=email]").val()))) {
            $('#email-error').text(EMAIL_VALIDERROR);
            return false;
        }
        return true;
    }
    //-------------------------------------------------------------

    // check duplication
    function checkUsernameDuplication(result) {
        if (result == "true") {
            $('#username-error').text(USERNAME_DUPLICATEERROR);
            return false;
        }
        return true;
    }

    function checkStudentidDuplication(result) {
        if (result == "true") {
            $('#studentid-error').text(STUDENTID_DUPLICATEERROR);
            return false;
        }
        return true;
    }

    function checkPhoneDuplication(result) {
        if (result == "true") {
            $('#phone-error').text(PHONE_DUPLICATEERROR);
            return false;
        }
        return true;
    }

    function checkEmailDuplication(result) {
        if (result == "true") {
            $('#email-error').text(EMAIL_DUPLICATEERROR);
            return false;
        }
        return true;
    }
    //-------------------------------------------------------------

    // clear error info
    function clearErrorInfo() {
        $('#username-error').text('');
        $('#studentid-error').text('');
        $('#phone-error').text('');
        $('#email-error').text('');
    }
    //-------------------------------------------------------------

    // check duplication by get
    function checkUsernameDuplicationByGet() {
        return $.get(
            "/check",
            { query: 'username', value: $("input[name=username]").val() },
            function (data) {
                return checkUsernameDuplication(data.username);
            }
        );
    }

    function checkStudentidDuplicationByGet() {
        return $.get(
            "/check",
            { query: 'studentid', value: $("input[name=studentid]").val() },
            function (data) {
                return checkStudentidDuplication(data.studentid);
            }
        );
    }

    function checkPhoneDuplicationByGet() {
        return $.get(
            "/check",
            { query: 'phone', value: $("input[name=phone]").val() },
            function (data) {
                return checkPhoneDuplication(data.phone);
            }
        );
    }

    function checkEmailDuplicationByGet() {
        return $.get(
            "/check",
            { query: 'email', value: $("input[name=email]").val() },
            function (data) {
                return checkEmailDuplication(data.email);
            }
        );
    }

    //-------------------------------------------------------------

    // check format of input and if be occupied when loses focus and give error tips
    $("input[name=username]").blur(function () {
        if (checkUsernameValidation()) {
            $('#username-error').text('');
            checkUsernameDuplicationByGet();
        }
    });

    $("input[name=studentid]").blur(function () {
        if (checkStudentidValidation()) {
            $('#studentid-error').text('');
            checkStudentidDuplicationByGet();
        }
    });

    $("input[name=phone]").blur(function () {
        if (checkPhoneValidation()) {
            $('#phone-error').text('');
            checkPhoneDuplicationByGet();
        }
    });

    $("input[name=email]").blur(function () {
        if (checkEmailValidation()) {
            $('#email-error').text('');
            checkEmailDuplicationByGet();
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
        clearErrorInfo();
    });

    $("input[name=SUBMIT]").click(function () {
        // clear error text
        clearErrorInfo();
        // check format is valid or not
        var isValid = true;
        // function checkUsernameValidation() must be executed
        // function checkUsernameDuplicationByGet() must be executed if format is valid
        if (!checkUsernameValidation() && isValid) {
            isValid = false;
        } else if (!checkUsernameDuplicationByGet() && isValid){
            isValid = false;
        }
        if (!checkStudentidValidation() && isValid) {
            isValid = false;
        } else if (!checkStudentidDuplicationByGet() && isValid) {
            isValid = false;
        }
        if (!checkPhoneValidation() && isValid) {
            isValid = false;
        } else if (!checkPhoneDuplicationByGet() && isValid) {
            isValid = false;
        }
        if (!checkEmailValidation() && isValid) {
            isValid = false;
        } else if (!checkEmailDuplicationByGet() && isValid) {
            isValid = false;
        }
        // --------------------------------------------------------------
        // check if input string valid
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
                    if (data.DUPLICATION != "") {
                        // if fail to register set error info if exists duplicate info
                        checkUsernameDuplication(data.DUPLICATION.indexOf('USERNAME') != -1);
                        checkStudentidDuplication(data.DUPLICATION.indexOf('STUDENTID') != -1);
                        checkPhoneDuplication(data.DUPLICATION.indexOf('PHONE') != -1);
                        checkEmailDuplication(data.DUPLICATION.indexOf('EMAIL') != -1);
                    } // if post data format is invalid
                    if (data.INVALID != "") {
                        if ((data.INVALID).indexOf('USERNAME') != -1) {
                            $('#username-error').text(USERNAME_VALIDERROR);
                        }
                        if (data.INVALID.indexOf('STUDENTID') != -1) {
                            $('#studentid-error').text(STUDENTID_VALIDERROR);
                        }
                        if (data.INVALID.indexOf('PHONE') != -1) {
                            $('#phone-error').text(PHONE_VALIDERROR);
                        }
                        if (data.INVALID.indexOf('EMAIL') != -1) {
                            $('#email-error').text(EMAIL_VALIDERROR);
                        }
                    }
                    if (data.INVALID == "" && data.DUPLICATION == "") {
                        // if successful register jump to details page
                        window.location.href = "http://" + window.location.host + '?username=' + data.USERNAME;
                    }
                },
            });
        }
    });
});

