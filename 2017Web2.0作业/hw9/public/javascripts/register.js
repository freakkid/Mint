$(function () {
    // error infomation
    const USERNAME_DUPLICATEERROR = 'Username has been occupied',
        STUDENTID_DUPLICATEERROR = 'StudentId has been occupied',
        PHONE_DUPLICATEERROR = 'Phone has been occupied',
        EMAIL_DUPLICATEERROR = 'Email has been occupied',
        USERNAME_VALIDERROR = '6~18 English letters, numbers or underscores, must begin with an English letter',
        PASSWORD_VALIDERROR = '6~12 digits, letters, strikethrough, underline',
        CONFIRM_VALIDERROR = 'The passwords entered did not match',
        STUDENTID_VALIDERROR = '8 digits, cannot start with 0',
        PHONE_VALIDERROR = '11 digits, cannot start with 0',
        EMAIL_VALIDERROR = 'Email format is illegal';
    // -----------------------------------------------------------

    // check format ------------------------------------------------------
    function checkUsernameValidation() {
        if (isUsernameValid($("input[name=username]").val())) {
            $('#username-error').text('');
            return true;
        }
        $('#username-error').text(USERNAME_VALIDERROR);
        return false;
    }

    function checkPasswordValidation() {
        if (isPasswordValid($("input[name=password]").val())) {
            $('#password-error').text('');
            return true;
        }
        $('#password-error').text(PASSWORD_VALIDERROR);
        return false;
    }

    function checkConfirmationMatch() {
        if (ifPasswordMatch($("input[name=password]").val(), $("input[name=confirm]").val())) {
            $('#confirm-error').text('');
            return true
        }
        $('#confirm-error').text(CONFIRM_VALIDERROR);
        return false;
    }

    function checkStudentIDValidation() {
        if (isStudentIDValid($("input[name=studentid]").val())) {
            $('#studentid-error').text('');
            return true;
        }
        $('#studentid-error').text(STUDENTID_VALIDERROR);
        return false;
    }

    function checkPhoneValidation() {
        if (isPhoneValid($("input[name=phone]").val())) {
            $('#phone-error').text('');
            return true;
        }
        $('#phone-error').text(PHONE_VALIDERROR);
        return false;
    }

    function checkEmailValidation() {
        if (isEmailValid($("input[name=email]").val())) {
            $('#email-error').text('');
            return true;
        }
        $('#email-error').text(EMAIL_VALIDERROR);
        return false;
    }
    //-------------------------------------------------------------

    // check duplication by get ------------------------------------
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
                return checkStudentIDDuplication(data.studentid);
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

    // check duplication ------------------------------------------
    function checkUsernameDuplication(result) {
        if (result == "true") {
            $('#username-error').text(USERNAME_DUPLICATEERROR);
            return false;
        }
        return true;
    }

    function checkStudentIDDuplication(result) {
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

    // check format of input and if be occupied when loses focus and give error tips
    $("input[name=username]").blur(function () {
        if (checkUsernameValidation()) {
            checkUsernameDuplicationByGet();
        }
    });

    $("input[name=studentid]").blur(function () {
        if (checkStudentIDValidation()) {
            checkStudentidDuplicationByGet();
        }
    });

    $("input[name=phone]").blur(function () {
        if (checkPhoneValidation()) {
            checkPhoneDuplicationByGet();
        }
    });

    $("input[name=email]").blur(function () {
        if (checkEmailValidation()) {
            checkEmailDuplicationByGet();
        }
    });

    $("input[name=password]").blur(function () {
        checkPasswordValidation()
    });

    $("input[name=confirm]").blur(function () {
        checkConfirmationMatch()
    });
    // -----------------------------------------------------------

    // clear ------------------------------------------------------
    // clear error info
    function clearErrorInfo() {
        $('#username-error').text('');
        $('#studentid-error').text('');
        $('#phone-error').text('');
        $('#email-error').text('');
        $('#password-error').text('');
        $('#confirm-error').text('');
    }
    // clear input box
    function clearInputBox() {
        $("input[name=username]").val('');
        $("input[name=studentid]").val('');
        $("input[name=phone]").val('');
        $("input[name=email]").val('');
        $("input[name=password]").val('');
        $("input[name=confirm]").val('');
    }
    // -------------------------------------------------------------

    // clear all form data
    $("input[name=RESET]").click(function () {
        // clear input box
        clearInputBox()
        // clear error text
        clearErrorInfo();
    });
    // ------------------------------------------

    // submit data ------------------------------
    $("input[name=SUBMIT]").click(function () {
        // clear error text
        clearErrorInfo();
        // check format of all data is valid or not
        var isValid = true;
        if (!checkUsernameValidation() && isValid) {
            isValid = false;
        } 
        if (!checkStudentIDValidation() && isValid) {
            isValid = false;
        } 
        if (!checkPhoneValidation() && isValid) {
            isValid = false;
        }
        if (!checkEmailValidation() && isValid) {
            isValid = false;
        } 
        if (!checkPasswordValidation() && isValid) {
            isValid = false;
        }
        if (!checkConfirmationMatch() && isValid) {
            isValid = false;
        }
        // --------------------------------------------------------------
        // check if input string valid
        if (isValid) {
            $.ajax({
                cache: false,
                url: "/user",
                data: $("input[name='username'], input[name='studentid'], input[name='phone'], input[name='email'], input[name='password'], input[name='confirm']").serialize(),
                type: "POST",
                processData: false,
                contentType: "application/x-www-form-urlencoded",
                error: function (jqXHR, textStatus, errorThrown) {
                    if (jqXHR.status == 400 || jqXHR.status == 500) {
                        const resultJSON = JSON.parse(jqXHR.responseText);
                        $('#username-error').text(resultJSON.USERNAMEERROR);
                        $('#studentid-error').text(resultJSON.STUDENTIDERROR);
                        $('#phone-error').text(resultJSON.PHONEEROR);
                        $('#email-error').text(resultJSON.EMAILERROR);
                        $('#password-error').text(resultJSON.PASSWORDERROR);
                        $('#confirm-error').text(resultJSON.COMFIRMERROR);
                    }
                },
                success: function (data, status, xhr) {
                    // if successful register, auto login and jump to details page
                    window.location.href = "http://" + window.location.host + '?username=' + data.USERNAME;
                },
            });
        }
    });

    // jump to login page
    $("input[name=SIGNIN]").click(function () {
        window.location.href = "http://" + window.location.host;
    });
});

