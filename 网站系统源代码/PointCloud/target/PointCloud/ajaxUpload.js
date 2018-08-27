//returndata 指的是从controller传回来的data，是什么格式都可以，都会变为json
function doUpload() {
    var formData = new FormData($( "#myform" )[0]);
    $.ajax({
        url: 'fileupload' ,
        type: 'POST',
        data: formData,
        async: false,
        cache: false,
        contentType: false,
        processData: false,
        success: function (returndata) {
            alert(returndata);
        },
        error: function (returndata) {
            alert(returndata);
        }
    });
}