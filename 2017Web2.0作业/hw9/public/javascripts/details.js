$(function () {
    $("input[name=SIGNOUT]").click(function () {
        $.ajax({
            url: "/users",
            type: "DELETE",
            error: function (error) {
                $('p.tip').text(error);
            },
            success: function (data, status, xhr) {
                window.location.href = "http://" + window.location.host;
            },
        });
    });
});