// check fotmat --------------------------------------------------------------
function isUsernameValid(username) {
    return /^[a-zA-Z][\w]{5,17}$/.test(username);
}

function isPasswordValid(password) {
    return /^[-\w]{6,12}$/.test(password);
}

function isStudentIDValid(studentid) {
    return /^(?!0)[\d]{8}$/.test(studentid);
}

function isPhoneValid(phone) {
    return /^(?!0)[\d]{11}$/.test(phone);
}

function isEmailValid(email) {
    return /^[a-zA-Z_\-]+@(([a-zA-Z_\-])+\.)+[a-zA-Z]{2,4}$/.test(email);
}

function ifPasswordMatch(password, confirm) {
    return password === confirm;
}

function isEmpty(text) {
    return text === "";
}
