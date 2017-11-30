$(function () {
    // clear all form data
    $("input[name=RESET]").click(function () {
        $("input[name=username]").val('');
        $("input[name=studentid]").val('');
        $("input[name=phone]").val('');
        $("input[name=email]").val('');
    });

    $("input[name=SUBMIT]").click(function () {
        // window.location.href = '/ss';
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
            // success: function (data) {
            //     $('#result').text("@" + data.Username + ": " + data.Message);
            // }
        });
    });
});